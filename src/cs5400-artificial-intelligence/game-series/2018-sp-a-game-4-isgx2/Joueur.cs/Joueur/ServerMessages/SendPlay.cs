using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Joueur.cs.ServerMessages
{
    class SendPlay
    {
        public string gameName;
        public string requestedSession = "*";
        public string clientType = "C#";
        public string playerName = "C# Player";
        public int playerIndex = -1;
        public string password;
        public string gameSettings;
    }
}
