using System;

namespace Joueur.cs
{
    public static class ErrorHandler
    {
        public enum ErrorCode
        {
            NONE = 0,
            INVALID_ARGS = 20,
            COULD_NOT_CONNECT = 21,
            DISCONNECTED_UNEXPECTEDLY = 22,
            CANNOT_READ_SOCKET = 23,
            DELTA_MERGE_FAILURE = 24,
            REFLECTION_FAILED = 25,
            UNKNOWN_EVENT_FROM_SERVER = 26,
            SERVER_TIMEOUT = 27,
            FATAL_EVENT = 28,
            GAME_NOT_FOUND = 29,
            MALFORMED_JSON = 30,
            UNAUTHENTICATED = 31,
            AI_ERRORED = 42
        };

        public static void HandleError(ErrorCode code, string message = null)
        {
            HandleError(code, null, message);
        }

        public static void HandleError(ErrorCode code, Exception exception = null, string message = null)
        {
            Console.ForegroundColor = ConsoleColor.Red;
            Console.Error.WriteLine("---\nError: " + Enum.GetName(typeof(ErrorCode), code));
            Console.Error.WriteLine("---");

            if (message != null)
            {
                Console.Error.WriteLine(message);
                Console.Error.WriteLine("---");
            }

            if (exception != null)
            {
                Console.Error.WriteLine(exception.ToString());
                Console.Error.WriteLine("---");
            }

            Console.ResetColor();
            Client.Instance.Disconnect();

            Environment.Exit((int)code);
        }
    }
}
