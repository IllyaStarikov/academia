/**
 * The traditional 8x8 chess board with pieces.
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
 * The traditional 8x8 chess board with pieces.
 */
public class Game extends BaseGame {
    /**
     * The player whose turn it is currently. That player can send commands. Other players cannot.
     */
    public Player currentPlayer;

    /**
     * The current turn number, starting at 0 for the first player's turn.
     */
    public int currentTurn;

    /**
     * Forsyth–Edwards Notation, a notation that describes the game board.
     */
    public String fen;

    /**
     * The maximum number of turns before the game will automatically end.
     */
    public int maxTurns;

    /**
     * The list of Moves that have occurred, in order.
     */
    public List<Move> moves;

    /**
     * All the uncaptured Pieces in the game.
     */
    public List<Piece> pieces;

    /**
     * List of all the players in the game.
     */
    public List<Player> players;

    /**
     * A unique identifier for the game instance that is being played.
     */
    public String session;

    /**
     * How many turns until the game ends because no pawn has moved and no Piece has been taken.
     */
    public int turnsToDraw;



    /**
     * Creates a new instance of a Game. Used during game initialization, do not call directly.
     */
    protected Game() {
        super();
        this.name = "Chess";

        this.moves = new ArrayList<Move>();
        this.pieces = new ArrayList<Piece>();
        this.players = new ArrayList<Player>();
    }
}
