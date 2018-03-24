/**
 * This is where you build your AI for the ${game_name} game.
 */
package games.${lowercase_first(game_name)};
<%include file="functions.noCreer" />
import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Random;
import joueur.BaseAI;

${merge("// ", "imports", "// you can add additional import(s) here", optional=True)}

/**
 * This is where you build your AI for the ${game_name} game.
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

${merge("    // ", "fields", '    // you can add additional fields here for your AI to use')}


    /**
     * This returns your AI's name to the game server. Just replace the string.
     * @return string of you AI's name
     */
    public String getName() {
${merge("        // ", "get-name", '        return "' + game_name + ' Java Player"; // REPLACE THIS WITH YOUR TEAM NAME!')}
    }

    /**
     * This is automatically called when the game first starts, once the Game object and all GameObjects have been initialized, but before any players do anything.
     * This is a good place to initialize any variables you add to your AI, or start tracking game objects.
     */
    public void start() {
${merge("        // ", "start", '        super.start();')}
    }

    /**
     * This is automatically called every time the game (or anything in it) updates.
     * If a function you call triggers an update this will be called before that function returns.
     */
    public void gameUpdated() {
${merge("        // ", "game-updated", '        super.gameUpdated();')}
    }

    /**
     * This is automatically called when the game ends.
     * You can do any cleanup of you AI here, or do custom logging. After this function returns the application will close.
     * @param  won  true if your player won, false otherwise
     * @param  name  reason">a string explaining why you won or lost
     */
    public void ended(boolean won, String reason) {
${merge("        // ", "ended", '        super.ended(won, reason);')}
    }

% for function_name in ai['function_names']:
<% function_parms = ai["functions"][function_name];
arg_strings = []
%>
    /**
     * ${function_parms['description']}<% a = "*/ this is to appease the syntax highlighter\"" %>
% if 'arguments' in function_parms:
     *
% for arg_parms in function_parms['arguments']:
<% arg_strings.append(shared['java']['type'](arg_parms['type']) + " " + arg_parms['name']) # syntax highlighter freaking out, needs ;
%>     * @param  ${arg_parms['name']}  ${arg_parms['description']}
% endfor
% endif
% if function_parms['returns'] != None:
% if 'arguments' not in function_parms:
     *
% endif
     * @return ${function_parms['returns']['description']}
% endif
     */
    public ${shared['java']['type'](function_parms['returns']['type']) if function_parms['returns'] else "void"} ${function_name}(${", ".join(arg_strings)}) {
${merge("        // ", function_name,
"""        // Put your game logic here for {0}
        return {1};
""".format(function_name, shared['java']['default'](function_parms['returns']['type'], function_parms['returns']['default']) if function_parms['returns'] else "")
)}
    }
% endfor


% if 'TiledGame' in game['serverParentClasses']: #// then we need to add some client side utility functions
    /**
     * A very basic path finding algorithm (Breadth First Search) that when given a starting Tile, will return a valid path to the goal Tile.
     * @param  start  the starting Tile
     * @param  goal  the goal Tile
     * @return A List of Tiles representing the path, the the first element being a valid adjacent Tile to the start, and the last element being the goal. Or an empty list if no path found.
     */
    List<Tile> findPath(Tile start, Tile goal) {
        // no need to make a path to here...
        if (start == goal) {
            return new ArrayList<Tile>();
        }

        // the tiles that will have their neighbors searched for 'goal'
        Queue<Tile> fringe = new LinkedList<Tile>();

        // How we got to each tile that went into the fringe.
        HashMap<Tile, Tile> cameFrom = new HashMap<Tile, Tile>();

        // Enqueue start as the first tile to have its neighbors searched.
        fringe.add(start);

        // keep exploring neighbors of neighbors... until there are no more.
        while (!fringe.isEmpty()) {
            // the tile we are currently exploring.
            Tile inspect = fringe.remove();

            // cycle through the tile's neighbors.
            List<Tile> neighbors = inspect.getNeighbors();
            for (int i = 0; i < neighbors.size(); i++) {
                Tile neighbor = neighbors.get(i);

                // If we found the goal we've found the path!
                if (neighbor == goal) {
                    // Follow the path backward starting at the goal and return it.
                    List<Tile> path = new ArrayList<Tile>();
                    path.add(goal);

                    // Starting at the tile we are currently at, insert them retracing our steps till we get to the starting tile
                    for (Tile step = inspect; step != start; step = cameFrom.get(step)) {
                        path.add(0, step);
                    }

                    return path;
                }

                // if the tile exists, has not been explored or added to the fringe yet, and it is pathable
                if (neighbor != null && !cameFrom.containsKey(neighbor) && neighbor.isPathable()) {
                    // add it to the tiles to be explored and add where it came from.
                    fringe.add(neighbor);
                    cameFrom.put(neighbor, inspect);
                }

            } // for each neighbor

        } // while fringe not empty

        // if you're here, that means that there was not a path to get to where you want to go.
        //   in that case, we'll just return an empty path.
        return new ArrayList<Tile>();
    }

% endif
${merge("    // ", "methods", '    // you can add additional methods here for your AI to call', optional=True)}
}
