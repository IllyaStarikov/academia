// Please do not modify this file.
// Instead have a look at `README.md` for how to start writing you AI.

using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Sockets;
using Newtonsoft.Json;
using System.Text;
using Newtonsoft.Json.Linq;
using System.Collections;
using System.Diagnostics;
using System.Reflection;

namespace Joueur.cs
{
    internal class Program
    {
        private static void Main(string[] args)
        {

            ArgParser argParser = new ArgParser(args, "Runs the C# client with options. Must a provide a game name to play on the server.", new[] {
                new ArgParser.Argument(new[] {"game"}, "game", "the name of the game you want to play on the server", true),
                new ArgParser.Argument(new[] {"-s", "--server"}, "server", "the url to the server you want to connect to e.g. locahost:3000", false, "127.0.0.1"),
                new ArgParser.Argument(new[] {"-p", "--port"}, "port", "the port to connect to on the server. Can be defined on the server arg via server:port", false, 3000),
                new ArgParser.Argument(new[] {"-n", "--name"}, "name", "the name you want to use as your AI\'s player name. This over-rides the name you set in your code"),
                new ArgParser.Argument(new[] {"-i", "--index"}, "index", "the player number you want to be, with 0 being the first player", false, -1),
                new ArgParser.Argument(new[] {"-r", "--session"}, "requestedSession", "the requested game session you want to play on the server", false, "*"),
                new ArgParser.Argument(new[] {"-w", "--password"}, "password", "the password required for authentication on official servers"),
                new ArgParser.Argument(new[] {"--gameSettings"}, "gameSettings", "Any settings for the game server to force. Must be url parms formatted (key=value&otherKey=otherValue)"),
                new ArgParser.Argument(new[] {"--aiSettings"}, "aiSettings", "Any settings for the AI. Delimit pairs by an ampersand (key=value&otherKey=otherValue)"),
                new ArgParser.Argument(new[] {"--printIO"}, "printIO", "(debugging) print IO through the TCP socket to the terminal", false, null, ArgParser.Argument.Store.True),
            }, (int)ErrorHandler.ErrorCode.INVALID_ARGS);

            string gameAlias = argParser.GetValue<string>("game");
            string server = argParser.GetValue<string>("server");
            string playerName = argParser.GetValue<string>("name");
            int playerIndex = argParser.GetValue<int>("index");
            string requestedSession = argParser.GetValue<string>("requestedSession");
            string password = argParser.GetValue<string>("password");
            string aiSettings = argParser.GetValue<string>("aiSettings");
            string gameSettings = argParser.GetValue<string>("gameSettings");
            int port = argParser.GetValue<int>("port");
            bool printIO = argParser.GetValue<bool>("printIO");

            if (server.Contains(":"))
            {
                var split = server.Split(':');
                server = split[0];
                port = Int32.Parse(split[1]);
            }

            Client client = Client.Instance;
            client.Connect(server, port, printIO);

            client.Send("alias", gameAlias);
            string gameName = client.WaitForEvent("named").ToString();

            BaseGame game;
            try
            {
                Type gameType = Type.GetType("Joueur.cs.Games." + gameName + ".Game");
                game = (BaseGame)Activator.CreateInstance(gameType, true);
            }
            catch (Exception exception)
            {
                ErrorHandler.HandleError(ErrorHandler.ErrorCode.GAME_NOT_FOUND, exception, "Could not create Game for game name '" + gameName + "'");
                return;
            }

            BaseAI ai;
            try
            {
                Type aiType = Type.GetType("Joueur.cs.Games." + gameName + ".AI");
                ai = (BaseAI)Activator.CreateInstance(aiType, true);
            }
            catch (Exception exception)
            {
                ErrorHandler.HandleError(ErrorHandler.ErrorCode.AI_ERRORED, exception, "Could create AI for game name '" + gameName + "'");
                return;
            }

            Console.ForegroundColor = ConsoleColor.Cyan;
            Console.WriteLine("Connecting to: " + server + ":" + port);
            Console.ResetColor();

            client.Setup(game, ai);

            typeof(BaseAI).GetMethod("SetSettings", BindingFlags.NonPublic | BindingFlags.Instance).Invoke(ai, new object[] { aiSettings });

            if (string.IsNullOrWhiteSpace(playerName))
            {
                playerName = ai.GetName();
            }

            client.Send("play", new ServerMessages.SendPlay
            {
                playerName = playerName,
                playerIndex = playerIndex,
                gameName = gameName,
                password = password,
                gameSettings = gameSettings,
                requestedSession = requestedSession
            }
            );

            var lobbiedData = (ServerMessages.LobbiedData)client.WaitForEvent("lobbied");

            Console.ForegroundColor = ConsoleColor.Cyan;
            Console.WriteLine("In lobby for game '" + lobbiedData.gameName + "' in session '" + lobbiedData.gameSession + "'.");
            Console.ResetColor();

            // hackish way to set the client in the game. we don't want to expose public methods that competitors may see via intellisense and try to use
            client.GameManager.SetConstants(lobbiedData.constants);

            var startData = (ServerMessages.StartData)client.WaitForEvent("start");

            Console.ForegroundColor = ConsoleColor.Green;
            Console.WriteLine("Game is starting.");
            Console.ResetColor();

            // set the AI's game and player via reflection
            try
            {
                ai.GetType().GetField("Game").SetValue(ai, game);
                ai.GetType().GetField("Player").SetValue(ai, game.GameObjects[startData.playerID]);
            }
            catch (Exception exception)
            {
                ErrorHandler.HandleError(ErrorHandler.ErrorCode.REFLECTION_FAILED, exception, "Could not set the Game and Player for the AI during game startup.");
            }

            try
            {
                ai.Start();
                ai.GameUpdated();
            }
            catch (Exception exception)
            {
                ErrorHandler.HandleError(ErrorHandler.ErrorCode.AI_ERRORED, exception, "AI errored during initial game start.");
            }

            client.Play();
        }
    }
}
