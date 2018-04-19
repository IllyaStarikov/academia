using Newtonsoft.Json.Linq;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;

namespace Joueur.cs
{
    public class GameManager
    {
        private BaseGame Game;
        #pragma warning disable 0414 // disable warnings. competitors don't need to see our errors
        private BaseAI AI;
        private IDictionary<string, string> ServerConstants;
        #pragma warning restore 0414
        private IDictionary<string, BaseGameObject> GameObjects;
        private string DELTA_LIST_LENGTH = null;
        private string DELTA_REMOVED = null;

        public GameManager(BaseGame game, BaseAI ai)
        {
            this.Game = game;
            this.AI = ai;
            this.GameObjects = this.Game.GameObjects;
        }

        public void SetConstants(IDictionary<string, string> constants)
        {
            this.ServerConstants = constants;
            this.DELTA_LIST_LENGTH = constants["DELTA_LIST_LENGTH"];
            this.DELTA_REMOVED = constants["DELTA_REMOVED"];
        }

        public string CSharpCase(string str)
        {
            return char.ToUpper(str[0]) + str.Substring(1);
        }

        public void DeltaUpdate(JObject delta)
        {
            this.InitGameObjects(delta);

            this.DeltaMerge(delta, this.Game);
        }

        private void InitGameObjects(JObject delta)
        {
            if (delta["gameObjects"] != null)
            {
                foreach (var item in delta["gameObjects"].ToObject<JObject>())
                {
                    var id = item.Key;
                    var objectDelta = item.Value.ToObject<JObject>();

                    if(!this.GameObjects.ContainsKey(id))
                    {
                        this.GameObjects.Add(id, this.CreateGameObject(objectDelta["gameObjectName"].ToObject<string>()));
                    }
                }
            }
        }

        private BaseGameObject CreateGameObject(string className)
        {
            var gameObjectType = Type.GetType("Joueur.cs.Games." + this.Game.Name + "." + className);
            var baseGameObject = Activator.CreateInstance(gameObjectType, true) as BaseGameObject;

            return baseGameObject;
        }

        private object DeltaMerge(JToken jtoken, object state = null)
        {
            switch(jtoken.Type)
            {
                case JTokenType.Object: // figure out if it is a List, Dictionary, GameObject, or GameObject reference
                    var jobject = jtoken as JObject;
                    if (this.IsGameObjectReference(jobject)) // then it is just a reference to a game object, so get the current instance of it
                    {
                        return this.GameObjects[jobject["id"].ToObject<string>()];
                    }

                    if (this.IsDeltaList(jobject))
                    {
                        return this.DeltaMergeList(state as IList, jobject);
                    }

                    if (state != null && (state.GetType().IsSubclassOf(typeof(BaseGameObject)) || state.GetType().IsSubclassOf(typeof(BaseGame))))
                    {
                        return this.DeltaMergeClass(state, jobject);
                    }

                    // else it should be a dictionary (which the delta looks identical to a game object, hence why we needed to check for that first).
                    return this.DeltaMergeDictionary((IDictionary)state, jobject);
                case JTokenType.Boolean:
                    return jtoken.ToObject<bool>();
                case JTokenType.Float:
                    return jtoken.ToObject<double>();
                case JTokenType.Integer:
                    var floatNum = jtoken.ToObject<float>();
                    var intNum = (int)floatNum;

                    if (intNum == floatNum) // then no overflow occurred when parsing the integer, so just return the normal int. This can happen with very large floats that are whole numbers so appear as integers to json.net
                    {
                        return intNum;
                    }
                    else
                    {
                        return floatNum;
                    }
                case JTokenType.String:
                    return jtoken.ToObject<string>();
                default:
                    return null;
            }
        }

        private object DeltaMergeClass(object state, JObject delta)
        {
            foreach (var item in delta)
            {
                var classPropertyKey = this.CSharpCase(item.Key);

                var itemProperty = state.GetType().GetProperty(classPropertyKey);
                if (itemProperty != null)
                {
                    try
                    {
                        var itemValue = this.DeltaMerge(item.Value, itemProperty.GetValue(state, null));
                        itemProperty.SetValue(state, itemValue, null);
                    }
                    catch(Exception exception)
                    {
                        ErrorHandler.HandleError(ErrorHandler.ErrorCode.REFLECTION_FAILED, exception, "Could not merge property '" + classPropertyKey + "' on '" + state.ToString() + "'.");
                    }
                }
            }

            return state;
        }

        private IList DeltaMergeList(IList list, JObject delta)
        {
            int listLength = delta[this.DELTA_LIST_LENGTH].ToObject<int>();

            // resize the list
            while (list.Count < listLength)
            {
                list.Add(null);
            }

            while (list.Count > listLength)
            {
                list.RemoveAt(list.Count - 1); // pop off the end
            }

            foreach (var item in delta)
            {
                if (item.Key == this.DELTA_LIST_LENGTH)
                {
                    continue; // because we don't care about the length anymore
                }

                int index = Convert.ToInt32(item.Key);

                if (index >= listLength) // continue as it's out of bounds (and should be a delta remove command) and resizing the list above should have handled these entries anyways
                {
                    continue;
                }

                // if we got here then we need to update list[index]
                list[index] = this.DeltaMerge(item.Value, list[index]);
            }

            return list;
        }

        private IDictionary DeltaMergeDictionary(IDictionary dictionary, JObject delta)
        {
            foreach(var item in delta)
            {
                var key = ((JToken)item.Key).ToObject<object>();

                if (!dictionary.Contains(key))
                {
                    dictionary.Add(key, null);
                }

                if (this.IsDeltaRemoved(item.Value.ToObject<object>()))
                {
                    dictionary.Remove(key);
                }
                else
                {
                    dictionary[key] = this.DeltaMerge(item.Value, dictionary[key]);
                }
            }

            return dictionary;
        }

        private bool IsGameObjectReference(JToken jtoken)
        {
            if (jtoken != null && jtoken.Type == JTokenType.Object)
            {
                return this.IsGameObjectReference(jtoken.ToObject<JObject>());
            }

            return false;
        }

        private bool IsGameObjectReference(JObject jobject)
        {
            IList<string> keys = jobject.Properties().Select(p => p.Name).ToList();
            return (keys.Count == 1 && jobject["id"] != null);
        }

        private bool IsDeltaList(JObject jobject)
        {
            var jtoken = jobject[this.DELTA_LIST_LENGTH];
            return (jtoken != null && jtoken.Type == JTokenType.Integer);
        }

        private bool IsDeltaRemoved(object obj)
        {
            if (obj != null && (obj.GetType() == typeof(JValue) || obj.GetType() == typeof(JToken) || obj.GetType() == typeof(JObject)))
            {
                var jtoken = obj as JToken;
                if (jtoken.Type != JTokenType.String)
                {
                    return false;
                }
            }

            var str = (string)obj;
            return (str == this.DELTA_REMOVED);
        }

        public T GetValueFromJToken<T>(JToken jtoken)
        {
            if (this.IsDeltaRemoved(jtoken))
            {
                return default(T); // default for Objects is null, which is removed
            }
            else if (this.IsGameObjectReference(jtoken))
            {
                var gameObject = this.GameObjects[jtoken["id"].ToString()];
                var justObject = gameObject as object;
                return (T)justObject; // stupid casting :P
            }

            if (jtoken != null)
            {
                return jtoken.ToObject<T>();
            }
            else
            {
                return default(T);
            }
        }

        public Dictionary<string, string> SerializeGameObject(BaseGameObject baseGameObject)
        {
            return new Dictionary<string, string>() { { "id", baseGameObject.Id } };
        }

        public Object SerializeSafe(Object obj)
        {
            if (obj.GetType().IsSubclassOf(typeof(BaseGameObject)))
            {
                return this.SerializeGameObject((BaseGameObject)obj);
            }

            return obj;
        }

        public object Unserialize(JToken jtoken)
        {
            return this.DeltaMerge(jtoken);
        }
    }
}
