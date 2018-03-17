using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net.Sockets;
using System.Reflection;
using Newtonsoft.Json;
using Newtonsoft.Json.Linq;
using System.IO;

namespace Joueur.cs
{
    public sealed class Client // Client is a singleton
    {
        #region Singleton pattern setup

        private static readonly Client _Instance = new Client();

        private Client()
        {
            this.EventsStack = new Stack<ServerMessages.ReceivedEvent<object>>();
            this.ReceivedBuffer = String.Empty;
        }

        public static Client Instance
        {
            get
            {
                return _Instance;
            }
        }

        #endregion

        public string Hostname { get; private set; }
        public int Port { get; private set; }
        public bool PrintIO { get; private set; }
        private const char EOT_CHAR = (char) 4;
        #pragma warning disable 0414 // disable warnings. competitors don't need to see our errors
        private BaseGame Game;
        #pragma warning restore 0414
        private BaseAI AI;
        private BaseGameObject AIsPlayer;
        public GameManager GameManager;
        private TcpClient TCPClient;
        private Stack<ServerMessages.ReceivedEvent<Object>> EventsStack;
        private string ReceivedBuffer;
        private bool Connected = false;
        private NetworkStream Stream;
        private byte[] TempData = new byte[1024];

        public void Connect(string hostname = "127.0.0.1", int port = 3000, bool printIO = false)
        {
            this.Hostname = hostname;
            this.Port = port;
            this.PrintIO = printIO;

            try
            {
                this.TCPClient = new TcpClient(hostname, port);
                this.TCPClient.ReceiveTimeout = 0;
                this.TCPClient.SendTimeout = 0;

                this.Stream = this.TCPClient.GetStream();
            }
            catch(Exception exception)
            {
                ErrorHandler.HandleError(ErrorHandler.ErrorCode.COULD_NOT_CONNECT, exception, "Could not connect to " + hostname + ":" + port);
            }

            this.Connected = true;
        }

        public void Setup(BaseGame game, BaseAI ai)
        {
            this.Game = game;
            this.AI = ai;
            this.GameManager = new GameManager(game, ai);
        }

        public void Send(string eventName, Object data)
        {
            ServerMessages.SendMessage message = new ServerMessages.SendMessage(eventName, data);

            string serialized = null;
            try
            {
                serialized = JsonConvert.SerializeObject(message) + EOT_CHAR;
            }
            catch(Exception exception)
            {
                ErrorHandler.HandleError(ErrorHandler.ErrorCode.MALFORMED_JSON, exception, "Could not serialize object: " + data.ToString());
            }

            if(this.PrintIO)
            {
                Console.ForegroundColor = ConsoleColor.Magenta;
                Console.WriteLine("TO SERVER <-- " + serialized);
                Console.ResetColor();
            }

            try
            {
                // Translate the passed message into ASCII and store it as a Byte array.
                byte[] bytes = System.Text.Encoding.ASCII.GetBytes(serialized);

                // Send the message to the connected TcpServer.
                this.Stream.Write(bytes, 0, bytes.Length);
            }
            catch(Exception exception)
            {
                ErrorHandler.HandleError(ErrorHandler.ErrorCode.CANNOT_READ_SOCKET, exception, "Could not send data through socket.");
            }
        }

        public void Disconnect()
        {
            if (this.Connected)
            {
                try
                {
                    this.Stream.Close();
                    this.TCPClient.Close();
                }
                catch
                {
                    // ignore, disconnect should only happen at the end when we don't care, or already during error handling when other errors liek this could bubble up.
                }
            }
        }



        public void Play()
        {
            this.WaitForEvent(null); // waits indefinitely. Should eventually be terminated by the 'over' event from the server.
        }

        public Object WaitForEvent(string eventName)
        {
            while (true)
            {
                this.WaitForEvents();

                while (this.EventsStack.Count > 0)
                {
                    ServerMessages.ReceivedEvent<Object> receivedEvent = this.EventsStack.Pop();
                    if (eventName != null && receivedEvent.@event == eventName)
                    {
                        return receivedEvent.data;
                    }
                    else
                    {
                        this.AutoHandle(receivedEvent.@event, receivedEvent.data);
                    }
                }
            }
        }

        private void WaitForEvents()
        {
            if (this.EventsStack.Count > 0)
            {
                return; // as we already have events to handle, no need to wait for more
            }

            while (true)
            {
                String responseData = String.Empty;

                // Try to read the TcpServer response bytes.
                int bytes = -2;
                if (this.Stream.DataAvailable)
                {
                    try
                    {
                        bytes = Stream.Read(this.TempData, 0, this.TempData.Length);
                    }
                    catch (Exception exception)
                    {
                        ErrorHandler.HandleError(ErrorHandler.ErrorCode.CANNOT_READ_SOCKET, exception, "Cannot read socket while waiting for events.");
                    }
                }

                if (bytes == -2)
                {
                    continue; // as no bytes were read
                }

                responseData = System.Text.Encoding.ASCII.GetString(this.TempData, 0, bytes);

                if (this.PrintIO)
                {
                    Console.ForegroundColor = ConsoleColor.Magenta;
                    Console.WriteLine("FROM SERVER --> " + responseData);
                    Console.ResetColor();
                }

                string total = this.ReceivedBuffer + responseData;
                string[] split = total.Split(EOT_CHAR);

                this.ReceivedBuffer = split.Last(); // this is either an empty string because of the EOT_CHAR split, or an incomplete json string so store it in the buffer

                for (int i = split.Length - 2; i >= 0; i--) // iterate through in reverse, skipping the over the very last item because we stored it in the receivedBuffer
                {
                    JObject deserialized = null;
                    string jsonStr = split[i];
                    try
                    {
                        deserialized = JObject.Parse(jsonStr);
                    }
                    catch(Exception exception)
                    {
                        ErrorHandler.HandleError(ErrorHandler.ErrorCode.MALFORMED_JSON, exception, "Could not parse json '" + jsonStr + "'");
                    }

                    var receivedEvent = new ServerMessages.ReceivedEvent<Object>();
                    receivedEvent.@event = deserialized.GetValue("event").ToString();

                    switch (receivedEvent.@event)
                    {
                        case "lobbied":
                            receivedEvent.data = deserialized["data"].ToObject<ServerMessages.LobbiedData>();
                            break;
                        case "start":
                            receivedEvent.data = deserialized["data"].ToObject<ServerMessages.StartData>();
                            break;
                        case "order":
                            receivedEvent.data = deserialized["data"].ToObject<ServerMessages.OrderData>();
                            break;
                        case "over":
                            receivedEvent.data = deserialized["data"].ToObject<ServerMessages.OverData>();
                            break;
                        case "invalid":
                        case "fatal":
                            receivedEvent.data = deserialized["data"].ToObject<ServerMessages.InvalidData>();
                            break;
                        default:
                            if (deserialized["data"] != null)
                            {
                                receivedEvent.data = deserialized["data"].ToObject<JToken>();
                            }
                            break;
                    }

                    this.EventsStack.Push(receivedEvent);
                }

                if (this.EventsStack.Count > 0)
                {
                    return;
                }
            }
        }



        private void AutoHandle(string eventName, Object data)
        {
            string capitalizedEventName = eventName.First().ToString().ToUpper() + eventName.Substring(1);
            MethodInfo theMethod = this.GetType().GetMethod("AutoHandle" + capitalizedEventName, BindingFlags.NonPublic | BindingFlags.Instance);

            if(theMethod == null || eventName == String.Empty)
            {
                ErrorHandler.HandleError(ErrorHandler.ErrorCode.UNKNOWN_EVENT_FROM_SERVER, "Could not auto handle '" + eventName + "'");
            }
            else
            {
                theMethod.Invoke(this, new Object[] {data});
            }
        }

        private void AutoHandleDelta(JObject data)
        {
            try
            {
                this.GameManager.DeltaUpdate(data);
            }
            catch(Exception exception)
            {
                ErrorHandler.HandleError(ErrorHandler.ErrorCode.DELTA_MERGE_FAILURE, exception, "Could not delta update");
            }

            if (this.AIsPlayer == null)
            {
                try
                {
                    this.AIsPlayer = (BaseGameObject)this.AI.GetType().GetField("Player").GetValue(this.AI);
                }
                catch(Exception exception)
                {
                    ErrorHandler.HandleError(ErrorHandler.ErrorCode.REFLECTION_FAILED, exception, "Could not get ai's player via reflection.");
                }
            }

            if (this.AIsPlayer != null)
            {
                try
                {
                    this.AI.GameUpdated();
                }
                catch(Exception exception)
                {
                    ErrorHandler.HandleError(ErrorHandler.ErrorCode.AI_ERRORED, exception, "AI threw unhandled exception during GameUpdated()");
                }
            }
        }

        private void AutoHandleInvalid(ServerMessages.InvalidData data)
        {
            try
            {
                this.AI.Invalid(data.message);
            }
            catch (Exception exception)
            {
                ErrorHandler.HandleError(ErrorHandler.ErrorCode.AI_ERRORED, exception, "AI threw unhandled exception during GameUpdated()");
            }
        }

        private void AutoHandleFatal(ServerMessages.InvalidData data)
        {
            ErrorHandler.HandleError(ErrorHandler.ErrorCode.FATAL_EVENT, "Got fatal error: " + data.message);
        }

        private void AutoHandleOver(ServerMessages.OverData data)
        {
            var won = true;
            var reason = "unknown reason";

            if (this.AIsPlayer != null) // try to figure out if we won or lost
            {
                try
                {
                    won = (bool)this.AIsPlayer.GetType().GetProperty("Won").GetValue(this.AIsPlayer, null);
                    var reasonProperty = (won ? "ReasonWon" : "ReasonLost");
                    reason = (string)this.AIsPlayer.GetType().GetProperty(reasonProperty).GetValue(this.AIsPlayer, null);
                }
                catch(Exception exception)
                {
                    ErrorHandler.HandleError(ErrorHandler.ErrorCode.REFLECTION_FAILED, exception, "Could not get win reason via reflection");
                }
            }

            Console.ForegroundColor = ConsoleColor.Green;
            Console.WriteLine("Game is over. " + (won ? "I won!" : "I Lost :(") + " because " + reason);
            Console.ResetColor();

            try
            {
                this.AI.Ended(won, reason);
            }
            catch(Exception exception)
            {
                ErrorHandler.HandleError(ErrorHandler.ErrorCode.AI_ERRORED, exception, "AI errored during Ended(won, reason)");
            }

            if (data.message != String.Empty)
            {
                Console.ForegroundColor = ConsoleColor.Cyan;
                Console.WriteLine(data.message.Replace("__HOSTNAME__", this.Hostname));
                Console.ResetColor();
            }

            this.Disconnect();
            System.Environment.Exit(0);
        }

        private void AutoHandleOrder(ServerMessages.OrderData data)
        {
            Object returned = typeof(BaseAI).GetMethod("DoOrder", BindingFlags.NonPublic | BindingFlags.Instance).Invoke(this.AI, new object[] { data.name, data.args });

            this.Send("finished", new ServerMessages.SendFinished() {
                orderIndex = data.index,
                returned = returned
            });
        }



        public T RunOnServer<T>(BaseGameObject caller, string functionName, IDictionary<string, object> args = null)
        {
            IDictionary<string, object> serialized = null;
            if (args != null)
            {
                serialized = new Dictionary<string, object>();
                foreach (string key in args.Keys)
                {
                    serialized.Add(key, Client.Instance.GameManager.SerializeSafe(args[key]));
                }
            }

            this.Send("run", new ServerMessages.RunMessage()
                {
                    caller = this.GameManager.SerializeGameObject(caller),
                    functionName = functionName,
                    args = serialized
                }
            );

            var runData = (JToken)this.WaitForEvent("ran");

            return this.GameManager.GetValueFromJToken<T>(runData);
        }
    }
}
