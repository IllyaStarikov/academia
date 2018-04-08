using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;

namespace Joueur.cs
{
    public abstract class BaseAI
    {
        protected BaseAI()
        {
        }

        public virtual string GetName()
        {
            return "C# Player";
        }

        public virtual void Start()
        {
            // the inheriting AI can add code to this inherited function
        }

        public virtual void Ended(bool won, string reason)
        {
            // the inheriting AI can add code to this inherited function
        }

        public virtual void Invalid(string message)
        {
            // the inheriting AI can add code to this inherited function
            Console.ForegroundColor = ConsoleColor.Yellow;
            Console.WriteLine("Invalid: " + message);
            Console.ResetColor();
        }

        public virtual void GameUpdated()
        {
            // the inheriting AI can add code to this inherited function
        }

        private Object DoOrder(string order, List<JToken> args)
        {
            var gameManager = Client.Instance.GameManager;
            var method = this.GetType().GetMethod(gameManager.CSharpCase(order));

            if (method != null)
            {
                var unserializedArgs = new object[args.Count];
                int i = 0;
                foreach (var arg in args)
                {
                    unserializedArgs[i++] = gameManager.Unserialize(arg);
                }

                try
                {
                    var returned = method.Invoke(this, unserializedArgs);

                    return returned;
                }
                catch(Exception exception)
                {
                    ErrorHandler.HandleError(ErrorHandler.ErrorCode.AI_ERRORED, exception, "AI errored while executing order '" + order + "'.");
                }
            }
            else
            {
                ErrorHandler.HandleError(ErrorHandler.ErrorCode.REFLECTION_FAILED, "Could not find a method for the AI to execute order '" + order + "'.");
            }

            return null; // should not reach here
        }

        private Dictionary<string, string> _AISettings = new Dictionary<string, string>(); // underscore to not interfere with competitors AI's variables

        private void SetSettings(string aiSettings)
        {
            if (aiSettings == null || aiSettings == "")
            {
                return; // no need to set settings, as there are none
            }

            var settings = aiSettings.Split('&');
            foreach (var pair in settings)
            {
                var kv = pair.Split('=');
                var value = "";
                // if they have a value set it, otherwise the value will be empty string as above
                if (kv.Length == 2)
                {
                    value = kv[1];
                }

                this._AISettings.Add(kv[0], value);
            }
        }

        /// <summary>
        /// Gets an AI setting passed to the program via the `--aiSettings` flag.If the flag was set it will be returned as a string value, null otherwise.
        /// </summary>
        /// <param name="key">The key of the setting you wish to get the value for</param>
        /// <returns>A string representing the value set via command line, or nil if the key was not set</returns>
        public string GetSetting(string key)
        {
            if (this._AISettings.ContainsKey(key))
            {
                return this._AISettings[key];
            }

            return null;
        }
    }
}
