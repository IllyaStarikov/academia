/**
 * An object in the game. The most basic class that all game classes should inherit from automatically.
 */

// DO NOT MODIFY THIS FILE
// Never try to directly create an instance of this class, or modify its member variables.
// Instead, you should only be reading its variables and calling its functions.

package games.chess;

import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import org.json.JSONObject;
import joueur.Client;
import joueur.BaseGame;
import joueur.BaseGameObject;


/**
 * An object in the game. The most basic class that all game classes should inherit from automatically.
 */
public class GameObject extends BaseGameObject {
    /**
     * Any strings logged will be stored here. Intended for debugging.
     */
    public List<String> logs;



    /**
     * Creates a new instance of a GameObject. Used during game initialization, do not call directly.
     */
    protected GameObject() {
        super();
        this.logs = new ArrayList<String>();
    }

    /**
     * Adds a message to this GameObject's logs. Intended for your own debugging purposes, as strings stored here are saved in the gamelog.
     *
     * @param   message  A string to add to this GameObject's log. Intended for debugging.
     */
    public void log(String message) {
        JSONObject args = new JSONObject();
        args.put("message", Client.getInstance().gameManager.serializeSafe(message));
        this.runOnServer("log", args);
    }
}
