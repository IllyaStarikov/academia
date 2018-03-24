using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Joueur.cs.ServerMessages
{
    class SendMessage
    {
        public string @event = "";
        public int sentTime;
        public Object data;

        public SendMessage(string e, Object d)
        {
            TimeSpan t = DateTime.UtcNow - new DateTime(1970, 1, 1);
            this.@event = e;
            this.sentTime = (int)t.TotalSeconds;
            this.data = d;
        }
    }
}
