#ifndef GAMES_${underscore(game_name).upper()}_AI_HPP
#define GAMES_${underscore(game_name).upper()}_AI_HPP
<%include file="impl/functions.noCreer" />
#include "impl/${underscore(game_name)}.hpp"
#include "game.hpp"
% for game_obj_key in sort_dict_keys(game_objs):
#include "${underscore(game_obj_key)}.hpp"
% endfor

#include "../../joueur/src/base_ai.hpp"
#include "../../joueur/src/attr_wrapper.hpp"

${merge("// ", "includes", "// You can add additional #includes here")}

namespace cpp_client
{

namespace ${underscore(game_name)}
{

/// <summary>
/// This is the header file for building your ${game_name} AI
/// </summary>
class AI : public Base_ai
{
public:
    /// <summary>
    /// This is a reference to the Game object itself, it contains all the information about the current game
    /// </summary>
    Game game;

    /// <summary>
    /// This is a pointer to your AI's player. This AI class is not a player, but it should command this Player.
    /// </summary>
    Player player;

${merge("    //", "class variables", "    // You can add additional class variables here.")}

    /// <summary>
    /// This returns your AI's name to the game server.
    /// Replace the string name.
    /// </summary>
    /// <returns>The name of your AI.</returns>
    virtual std::string get_name() const override;

    /// <summary>
    /// This is automatically called when the game first starts, once the game objects are created
    /// </summary>
    virtual void start() override;

    /// <summary>
    /// This is automatically called when the game ends.
    /// </summary>
    /// <param name="won">true if you won, false otherwise</param>
    /// <param name="reason">An explanation for why you either won or lost</param>
    virtual void ended(bool won, const std::string& reason) override;

    /// <summary>
    /// This is automatically called the game (or anything in it) updates
    /// </summary>
    virtual void game_updated() override;

% for function_name in ai['function_names']:
<%
function_params = ai['functions'][function_name]
if function_params['returns'] and 'type' in function_params['returns']:
    return_type = shared['gen_base_type'](function_params['returns']['type'])
else:
    return_type = 'void'
args = shared['make_args'](function_params, True)
%>    /// <summary>
    /// ${function_params['description']}
    /// </summary>
% for arg_params in function_params['arguments']:
    /// <param name="${underscore(arg_params['name'])}">${arg_params['description']}</param>
% endfor
% if function_params['returns']:
    /// <returns>${function_params['returns']['description']}</returns>
% endif
    ${return_type} ${underscore(function_name)}(${args});
% endfor

${merge("    // ", "methods", "    // You can add additional methods here.")}
% if 'TiledGame' in game['serverParentClasses']: #// then we need to add some client side utility functions

/// A very basic path finding algorithm (Breadth First Search) that when given a starting Tile, will return a valid path to the goal Tile.
/// <param name="start">the starting Tile</param>
/// <param name="goal">the goal Tile</param>
/// <return>A List of Tiles representing the path, the the first element being a valid adjacent Tile to the start, and the last element being the goal. Or an empty list if no path found.</return>
std::vector<Tile> find_path(const Tile& start, const Tile& goal);
% endif



    // ####################
    // Don't edit these!
    // ####################
    /// \cond FALSE
    virtual std::string invoke_by_name(const std::string& name,
                                       const std::unordered_map<std::string, Any>& args) override;
    virtual void set_game(Base_game* ptr) override;
    virtual void set_player(std::shared_ptr<Base_object> obj) override;
    virtual void print_win_loss_info() override;
    /// \endcond
    // ####################
    // Don't edit these!
    // ####################

};

} // ${underscore(game_name).upper()}

} // cpp_client

#endif // GAMES_${underscore(game_name).upper()}_AI_HPP
