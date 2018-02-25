using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Joueur.cs
{
    public abstract class BaseGame
    {
        /// <summary>
        /// A mapping of every game object's ID to the actual game object. Primarily used by the server and client to easily refer to the game objects via ID.
        /// </summary>
        public IDictionary<string, BaseGameObject> GameObjects { get; set; } // mapping of the game object ID (which is a string) to the actual game object. IDs are never re-used so this helps us grab and check what game objects have been created

        /// <summary>
        /// The name of the game.
        /// </summary>
        public string Name { get; protected set; }

        public BaseGame()
        {
            this.Name = "NO_NAME";
            this.GameObjects = new Dictionary<string, BaseGameObject>();
        }
    }
}
