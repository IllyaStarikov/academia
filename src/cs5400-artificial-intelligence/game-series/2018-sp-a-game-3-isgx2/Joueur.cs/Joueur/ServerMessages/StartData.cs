#pragma warning disable 0649 // this is an interopt class and it will never be directly assigned to, Json.Net will instead dynamically use these properties
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Joueur.cs.ServerMessages
{
    class StartData : ReceivedData
    {
        public string playerID;
    }
}
