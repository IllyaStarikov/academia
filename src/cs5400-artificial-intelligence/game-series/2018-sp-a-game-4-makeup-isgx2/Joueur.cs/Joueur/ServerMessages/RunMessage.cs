using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Joueur.cs.ServerMessages
{
    class RunMessage
    {
        public Dictionary<string, string> caller;
        public string functionName;
        public IDictionary<string, object> args;
    }
}
