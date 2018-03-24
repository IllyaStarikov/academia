using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Joueur.cs.ServerMessages
{
    class SendFinished
    {
        public int orderIndex;
        public Object returned;
    }
}
