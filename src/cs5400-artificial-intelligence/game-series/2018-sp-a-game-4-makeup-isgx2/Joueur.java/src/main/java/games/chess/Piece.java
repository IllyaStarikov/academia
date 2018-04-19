/**
 * A chess piece.
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
 * A chess piece.
 */
public class Piece extends GameObject {
    /**
     * When the Piece has been captured (removed from the board) this is true. Otherwise false.
     */
    public boolean captured;

    /**
     * The file (column) coordinate of the Piece represented as a letter [a-h], with 'a' starting at the left of the board.
     */
    public String file;

    /**
     * If the Piece has moved from its starting position.
     */
    public boolean hasMoved;

    /**
     * The player that controls this chess Piece.
     */
    public Player owner;

    /**
     * The rank (row) coordinate of the Piece represented as a number [1-8], with 1 starting at the bottom of the board.
     */
    public int rank;

    /**
     * The type of chess Piece this is, either 'King, 'Queen', 'Knight', 'Rook', 'Bishop', or 'Pawn'.
     */
    public String type;



    /**
     * Creates a new instance of a Piece. Used during game initialization, do not call directly.
     */
    protected Piece() {
        super();
    }

    /**
     * Defaults the value for the optional arg 'promotionType' to '""'
     *
     * @see Piece#move(String, int, String)
     */
    public Move move(String file, int rank) {
        return this.move(file, rank, "");
    }

    /**
     * Moves the Piece from its current location to the given rank and file.
     *
     * @param   file  The file coordinate to move to. Must be [a-h].
     * @param   rank  The rank coordinate to move to. Must be [1-8].
     * @param   promotionType  If this is a Pawn moving to the end of the board then this parameter is what to promote it to. When used must be 'Queen', 'Knight', 'Rook', or 'Bishop'.
     * @return The Move you did if successful, otherwise null if invalid. In addition if your move was invalid you will lose.
     */
    public Move move(String file, int rank, String promotionType) {
        JSONObject args = new JSONObject();
        args.put("file", Client.getInstance().gameManager.serializeSafe(file));
        args.put("rank", Client.getInstance().gameManager.serializeSafe(rank));
        args.put("promotionType", Client.getInstance().gameManager.serializeSafe(promotionType));
        return (Move)this.runOnServer("move", args);
    }
}
