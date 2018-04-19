#pragma warning disable 0649 // this is an interopt class and it will never be directly assigned to, Json.Net will instead dynamically use these properties
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Joueur.cs.ServerMessages
{
    class LobbiedData : ReceivedData
    {        
        public string gameName;
        public string gameSession;
        public Dictionary<string, string> constants; // TODO: could be more dynamic than this, just so happens all keys and values are strings at the moment.
    }
}
