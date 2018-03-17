/**
 * A player in this game. Every AI controls one player.
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
 * A player in this game. Every AI controls one player.
 */
public class Player extends GameObject {
    /**
     * What type of client this is, e.g. 'Python', 'JavaScript', or some other language. For potential data mining purposes.
     */
    public String clientType;

    /**
     * The color (side) of this player. Either 'White' or 'Black', with the 'White' player having the first move.
     */
    public String color;

    /**
     * True if this player is currently in check, and must move out of check, false otherwise.
     */
    public boolean inCheck;

    /**
     * If the player lost the game or not.
     */
    public boolean lost;

    /**
     * If the Player has made their move for the turn. true means they can no longer move a Piece this turn.
     */
    public boolean madeMove;

    /**
     * The name of the player.
     */
    public String name;

    /**
     * This player's opponent in the game.
     */
    public Player opponent;

    /**
     * All the uncaptured chess Pieces owned by this player.
     */
    public List<Piece> pieces;

    /**
     * The direction your Pieces must go along the rank axis until they reach the other side. Will be +1 if the Player is 'White', or -1 if the Player is 'Black'.
     */
    public int rankDirection;

    /**
     * The reason why the player lost the game.
     */
    public String reasonLost;

    /**
     * The reason why the player won the game.
     */
    public String reasonWon;

    /**
     * The amount of time (in ns) remaining for this AI to send commands.
     */
    public double timeRemaining;

    /**
     * If the player won the game or not.
     */
    public boolean won;



    /**
     * Creates a new instance of a Player. Used during game initialization, do not call directly.
     */
    protected Player() {
        super();
        this.pieces = new ArrayList<Piece>();
    }
}
