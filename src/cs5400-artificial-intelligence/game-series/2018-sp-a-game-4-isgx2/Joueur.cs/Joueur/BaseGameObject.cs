using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Joueur.cs
{
    public abstract class BaseGameObject
    {
        /// <summary>
        /// A unique identifier for each game object. During any game IDs will never be re-used.
        /// </summary>
        public string Id { get; protected set; }

        /// <summary>
        /// String representing the top level Class that this game object is an instance of. Used for reflection to create new instances on clients, but exposed for convenience should AIs want this data.
        /// </summary>
        public string GameObjectName { get; protected set; }



        /// <summary>
        /// ToString override, useful for debugging
        /// </summary>
        public override string ToString()
        {
            return this.Id + " #" + this.GameObjectName;
        }

        protected T RunOnServer<T>(string functionName, IDictionary<string, object> args = null)
        {
            return Client.Instance.RunOnServer<T>(this, functionName, args);
        }
    }
}
