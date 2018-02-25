// DO NOT MODIFY THIS FILE
// Never try to directly create an instance of this class, or modify its member variables.
// This contains implementation details, written by code, and only useful to code

#ifndef GAMES_${underscore(game_name).upper()}_FWD_H
#define GAMES_${underscore(game_name).upper()}_FWD_H

//include declarations for all of the internal classes in the game's namespace
#include <memory>

namespace cpp_client
{

namespace ${underscore(game_name)}
{

% for game_obj_key in sort_dict_keys(game_objs):
<% obj_name = underscore(game_obj_key).capitalize() %>
class ${obj_name}_;
using ${obj_name} = std::shared_ptr<${obj_name}_>;
% endfor

class Game_;
using Game = Game_*;

}

}

#endif // GAMES_${underscore(game_name).upper()}_H
