using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Joueur.cs
{
    public class ArgParser
    {
        public class Argument
        {
            public enum Store { Value, True, False }

            public Store HowToStore;
            public string Destination;
            public object Default;
            public string Help;
            public string[] Aliases;
            public bool Required;

            public Argument(string[] aliases, string destination, string help, bool required = false, object defaultValue = null, Store? howToStore = null)
            {
                this.Aliases = aliases;
                this.Destination = destination;
                this.Help = help;
                this.Required = required;
                if (howToStore == null)
                {
                    this.HowToStore = Store.Value;
                }
                else
                {
                    this.HowToStore = (Store)howToStore;
                }
                this.Default = defaultValue;

                switch (this.HowToStore)
                {
                    case Store.True:
                        this.Default = false;
                        break;
                    case Store.False:
                        this.Default = true;
                        break;
                }
            }
        }

        private string Help;
        private Argument[] Arguments;
        private Dictionary<string, object> ParsedValues;
        private Dictionary<string, Argument> AliasToArgument;
        private Queue<Argument> ExpectedOrderedArgs;
        private int ErrorCode;

        public ArgParser(string[] args, string help, Argument[] arguments, int errorCode = 1)
        {
            this.Help = help;
            this.ErrorCode = errorCode;
            this.ParsedValues = new Dictionary<string, object>();
            this.AliasToArgument = new Dictionary<string, Argument>();
            this.ExpectedOrderedArgs = new Queue<Argument>();

            this.BuildValidArguments(arguments);

            this.ParseConsoleArgs(args);

            this.CheckRequired();
        }

        private void BuildValidArguments(Argument[] arguments)
        {
            this.Arguments = new Argument[arguments.Length + 1];
            this.Arguments[0] = new Argument(new string[] { "-h", "--help" }, "help", "Shows this help message and exits");
            int i = 1;

            foreach (var argument in arguments)
            {
                this.Arguments[i++] = argument;
                if (!this.ParsedValues.ContainsKey(argument.Destination))
                {
                    this.ParsedValues.Add(argument.Destination, argument.Default);
                }

                foreach (var alias in argument.Aliases)
                {
                    if (alias.StartsWith("-"))
                    {
                        this.AliasToArgument.Add(alias, argument);
                    }
                    else  // it is not an option, but an expected arg
                    {
                        this.ExpectedOrderedArgs.Enqueue(argument);
                        break;
                    }
                }
            }
        }

        private void ParseConsoleArgs(string[] args)
        {
            Argument currentArgument = null;

            for (int i = 0; i < args.Length; i++)
            {
                string arg = args[i];

                if (arg == "-h" || arg == "--help")
                {
                    this.GetHelp();
                }

                if (this.AliasToArgument.ContainsKey(arg))
                {
                    currentArgument = this.AliasToArgument[arg];
                }
                else if (this.ExpectedOrderedArgs.Count() > 0)
                {
                    currentArgument = this.ExpectedOrderedArgs.Dequeue();
                    this.ParsedValues[currentArgument.Destination] = arg;
                    continue;
                }
                else
                {
                    Console.Error.WriteLine("Unexpected arg alias '" + arg + "'");
                    this.GetHelp();
                }

                // check for flags (value that don't have leading values)
                object value = null;
                if (currentArgument.HowToStore == Argument.Store.False)
                {
                    value = false;
                }
                else if (currentArgument.HowToStore == Argument.Store.True)
                {
                    value = true;
                }

                if (value != null)
                {
                    this.ParsedValues[currentArgument.Destination] = value;
                }
                else if (i < args.Length - 1)
                {
                    this.ParsedValues[currentArgument.Destination] = args[++i];
                }
                else
                {
                    Console.Error.WriteLine("Error: Missing value for '" + arg + "'");
                    this.GetHelp();
                }
            }
        }

        public bool HasValue(string key)
        {
            return this.ParsedValues.GetValueOrDefault(key, null) != null;
        }

        public T GetValue<T>(string key)
        {
            if (this.HasValue(key))
            {
                var value = this.ParsedValues[key];

                if (typeof(T) == typeof(int) && value.GetType() == typeof(string))
                {
                    value = Int32.Parse((string)value);
                }

                return (T)value;
            }
            else
            {
                return default(T);
            }
        }

        public string GetHelpString()
        {
            var s = new StringBuilder();
            int maxStringLength = 0;
            var requiredArgs = new List<Tuple<string, string>>();
            var optionalArgs = new List<Tuple<string, string>>();

            s.Append("\nUsage: ");
            foreach (var argument in this.Arguments)
            {
                string all = String.Join(", ", argument.Aliases);
                maxStringLength = Math.Max(maxStringLength, all.Length);

                if (!argument.Required)
                {
                    optionalArgs.Add(new Tuple<string, string>(all, argument.Help));
                    s.Append("[");

                    for (int i = 0; i < argument.Aliases.Length; i++)
                    {
                        s.Append(argument.Aliases[i]);
                        if (i < argument.Aliases.Length - 1)
                        {
                            s.Append(", ");
                        }
                    }

                    s.Append("] ");
                }
            }

            s.Append(" ");

            foreach (var argument in this.Arguments)
            {
                if (argument.Required)
                {
                    string all = String.Join(", ", argument.Aliases);
                    requiredArgs.Add(new Tuple<string, string>(all, argument.Help));
                    s.Append("<" + argument.Aliases[0] + "> ");
                }
            }

            s.Append("\n\n");
            s.Append(this.Help);

            s.Append("\n\nPositional Arguments:\n");
            foreach (var tuple in requiredArgs)
            {
                s.Append("  ");
                s.Append(tuple.Item1.PadRight(maxStringLength, ' '));
                s.Append("  ");
                s.Append(tuple.Item2);
                s.Append("\n");
            }

            s.Append("\n\nOptional Arguments:\n");
            foreach (var tuple in optionalArgs)
            {
                s.Append("  ");
                s.Append(tuple.Item1.PadRight(maxStringLength, ' '));
                s.Append("  ");
                s.Append(tuple.Item2);
                s.Append("\n");
            }

            return s.ToString();
        }

        public void GetHelp()
        {
            Console.Write(this.GetHelpString());
            System.Environment.Exit(this.ErrorCode);
        }

        public void CheckRequired()
        {
            foreach (var argument in this.Arguments)
            {
                if (argument.Required && !this.HasValue(argument.Destination))
                {
                    Console.Error.WriteLine("Error: missing value for '" + argument.Destination + "'.");
                    this.GetHelp();
                }
            }
        }
    }
}
