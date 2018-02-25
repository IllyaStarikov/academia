// AI
// This is where you build your AI

#include "ai.hpp"

${merge("// ", "includes", "// You can add #includes here for your AI.")}
<%include file="impl/functions.noCreer" />
namespace cpp_client
{

namespace ${underscore(game_name)}
{

/// <summary>
/// This returns your AI's name to the game server.
/// Replace the string name.
/// </summary>
/// <returns>The name of your AI.</returns>
std::string AI::get_name() const
{
${merge("    // ", "get-name", '    // REPLACE WITH YOUR TEAM NAME!\n    return "' + game_name + ' C++ Player";')}
}

/// <summary>
/// This is automatically called when the game first starts, once the game objects are created
/// </summary>
void AI::start()
{
${merge("    // ", "start", "    // This is a good place to initialize any variables")}
}

/// <summary>
/// This is automatically called the game (or anything in it) updates
/// </summary>
void AI::game_updated()
{
${merge("    // ", "game-updated", "    // If a function you call triggers an update this will be called before it returns.")}
}

/// <summary>
/// This is automatically called when the game ends.
/// </summary>
/// <param name="won">true if you won, false otherwise</param>
/// <param name="reason">An explanation for why you either won or lost</param>
void AI::ended(bool won, const std::string& reason)
{
${merge("    //", "ended", "    // You can do any cleanup of your AI here.  The program ends when this function returns.")}
}

% for function_name in ai['function_names']:
<%
function_params = ai['functions'][function_name]
if function_params['returns'] and 'type' in function_params['returns']:
    return_type = shared['gen_base_type'](function_params['returns']['type'])
else:
    return_type = 'void'
args = shared['make_args'](function_params, True)
%>/// <summary>
/// ${function_params['description']}
/// </summary>
% for arg_params in function_params['arguments']:
/// <param name="${underscore(arg_params['name'])}">${arg_params['description']}</param>
% endfor
% if function_params['returns']:
/// <returns>${function_params['returns']['description']}</returns>
% endif
${return_type} AI::${underscore(function_name)}(${args})
{
${merge("    // ", function_name, "    // Put your game logic here for {} here".format(underscore(function_name)))}
% if return_type in shared['defaults']:
    return${shared['defaults'][return_type]};
% else:
    return ${return_type}{};
% endif
}
% endfor
% if 'TiledGame' in game['serverParentClasses']: #// then we need to add some client side utility functions

/// A very basic path finding algorithm (Breadth First Search) that when given a starting Tile, will return a valid path to the goal Tile.
/// <param name="start">the starting Tile</param>
/// <param name="goal">the goal Tile</param>
/// <return>A List of Tiles representing the path, the the first element being a valid adjacent Tile to the start, and the last element being the goal. Or an empty list if no path found.</return>
std::vector<Tile> AI::find_path(const Tile& start, const Tile& goal)
{
    // no need to make a path to here...
    if(start == goal)
    {
        return {};
    }

    // the tiles that will have their neighbors searched for 'goal'
    std::queue<Tile> fringe;

    // How we got to each tile that went into the fringe.
    std::unordered_map<Tile,Tile> came_from;

    // Enqueue start as the first tile to have its neighbors searched.
    fringe.push(start);

    // keep exploring neighbors of neighbors... until there are no more.
    while(fringe.size() > 0)
    {
        // the tile we are currently exploring.
        Tile inspect = fringe.front();
        fringe.pop();

        // Note, we are using the `auto` keyword here
        //   The compiler can discern that this is a `std::vector<Tile>` based on the return type of `getNeighbors()`
        auto neighbors = inspect->get_neighbors();

        // cycle through the tile's neighbors.
        for(unsigned i = 0; i < neighbors.size(); i++)
        {
            Tile neighbor = neighbors[i];

            // If we found the goal we've found the path!
            if(neighbor == goal)
            {
                // Follow the path backward starting at the goal and return it.
                std::deque<Tile> path;
                path.push_front(goal);

                // Starting at the tile we are currently at, insert them retracing our steps till we get to the starting tile
                for(Tile step = inspect; step != start; step = came_from[step])
                {
                    path.push_front(step);
                }

                // we want to return a vector as that's what we use for all containers in C++
                // (and they don't have push_front like we need)
                // So construct the vector-ized path here
                std::vector<Tile> vector_path;
                for(auto& tile : path)
                {
                    vector_path.push_back(tile);
                }
                return vector_path;
            }

            // if the tile exists, has not been explored or added to the fringe yet, and it is pathable
            if(neighbor && came_from.count(neighbor) == 0 && neighbor->is_pathable())
            {
                // add it to the tiles to be explored and add where it came from.
                fringe.push(neighbor);
                came_from[neighbor] = inspect;
            }

        } // for each neighbor

    } // while fringe not empty

    // if you're here, that means that there was not a path to get to where you want to go.
    //   in that case, we'll just return an empty path.
    return {};
}
% endif

${merge("//", "methods", "// You can add additional methods here for your AI to call")}

} // ${underscore(game_name)}

} // cpp_client
