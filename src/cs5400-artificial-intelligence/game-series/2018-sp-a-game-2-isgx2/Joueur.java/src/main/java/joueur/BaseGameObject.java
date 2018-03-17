package joueur;

import org.json.JSONObject;

public class BaseGameObject {
    /**
     * A unique id for each instance of a GameObject or a sub class. Used for client and server communication. Should never change value after being set.
     */
    public String id;

    /**
     * String representing the top level Class that this game object is an instance of. Used for reflection to create new instances on clients, but exposed for convenience should AIs want this data.
     */
    public String gameObjectName;



    protected BaseGameObject() {}

    protected Object runOnServer(String functionName, JSONObject args) {
        return Client.getInstance().runOnServer(this, functionName, args);
    }

    /**
     * toString override, useful for debugging
     *
     * @return a human readable string representation of the game object
     */
    public String toString() {
        return this.gameObjectName + " #" + this.id;
    }
}
