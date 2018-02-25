// DO NOT MODIFY THIS FILE
// Never try to directly create an instance of this class, or modify its member variables.
// This contains implementation details, written by code, and only useful to code

#include "${underscore(game_name)}.hpp"
#include "../../../joueur/src/register.hpp"

#include "../../../joueur/src/exceptions.hpp"

namespace cpp_client
{

namespace ${underscore(game_name)}
{

//register the game
Game_registry registration("${underscore(game_name).capitalize()}",
                           std::unique_ptr<${underscore(game_name).capitalize()}>(new ${underscore(game_name).capitalize()}));

std::unique_ptr<Base_ai> ${underscore(game_name).capitalize()}::generate_ai()
{
    return std::unique_ptr<Base_ai>(new AI);
}

std::shared_ptr<Base_object> ${underscore(game_name).capitalize()}::generate_object(const std::string& type)
{<% if_state = 'if' %>
% for game_obj_key in sort_dict_keys(game_objs):
    ${if_state}(type == "${game_obj_key}")
    {
        return std::make_shared<${underscore(game_obj_key).capitalize()}_>();
    }<% if_state = 'else if' %>
% endfor
    throw Unknown_type("Unknown type " + type + " encountered.");
}

} // ${underscore(game_name)}

} // cpp_client
