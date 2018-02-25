/**
 * This is where you build your AI for the Chess game.
 */
package games.chess;

import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Random;
import joueur.BaseAI;

// <<-- Creer-Merge: imports -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
// you can add additional import(s) here
// <<-- /Creer-Merge: imports -->>

/**
 * This is where you build your AI for the Chess game.
 */
public class AI extends BaseAI {
    /**
     * This is the Game object itself, it contains all the information about the current game
     */
    public Game game;

    /**
     * This is your AI's player. This AI class is not a player, but it should command this Player.
     */
    public Player player;

    // <<-- Creer-Merge: fields -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    // you can add additional fields here for your AI to use
    // <<-- /Creer-Merge: fields -->>


    /**
     * This returns your AI's name to the game server. Just replace the string.
     * @return string of you AI's name
     */
    public String getName() {
        // <<-- Creer-Merge: get-name -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
        return "Chess Java Player"; // REPLACE THIS WITH YOUR TEAM NAME!
        // <<-- /Creer-Merge: get-name -->>
    }

    /**
     * This is automatically called when the game first starts, once the Game object and all GameObjects have been initialized, but before any players do anything.
     * This is a good place to initialize any variables you add to your AI, or start tracking game objects.
     */
    public void start() {
        // <<-- Creer-Merge: start -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
        super.start();
        // <<-- /Creer-Merge: start -->>
    }

    /**
     * This is automatically called every time the game (or anything in it) updates.
     * If a function you call triggers an update this will be called before that function returns.
     */
    public void gameUpdated() {
        // <<-- Creer-Merge: game-updated -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
        super.gameUpdated();
        // <<-- /Creer-Merge: game-updated -->>
    }

    /**
     * This is automatically called when the game ends.
     * You can do any cleanup of you AI here, or do custom logging. After this function returns the application will close.
     * @param  won  true if your player won, false otherwise
     * @param  name  reason">a string explaining why you won or lost
     */
    public void ended(boolean won, String reason) {
        // <<-- Creer-Merge: ended -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
        super.ended(won, reason);
        // <<-- /Creer-Merge: ended -->>
    }


    /**
     * This is called every time it is this AI.player's turn.
     *
     * @return Represents if you want to end your turn. True means end your turn, False means to keep your turn going and re-call this function.
     */
    public boolean runTurn() {
        // <<-- Creer-Merge: runTurn -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
        // Put your game logic here for runTurn
        return true;
        // <<-- /Creer-Merge: runTurn -->>
    }


    // <<-- Creer-Merge: methods -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    // you can add additional methods here for your AI to call
    // <<-- /Creer-Merge: methods -->>
}
