// DO NOT MODIFY THIS FILE
// Never try to directly create an instance of this class, or modify its member variables.
// This contains implementation details, written by code, and only useful to code

#include "../move.hpp"
#include "../../../joueur/src/base_ai.hpp"
#include "../../../joueur/src/any.hpp"
#include "../../../joueur/src/exceptions.hpp"
#include "../../../joueur/src/delta.hpp"
#include "../game_object.hpp"
#include "../move.hpp"
#include "../piece.hpp"
#include "../player.hpp"
#include "chess.hpp"

#include <type_traits>

namespace cpp_client
{

namespace chess
{


Move_::Move_(std::initializer_list<std::pair<std::string, Any&&>> init) :
    Game_object_{
        {"captured", Any{std::decay<decltype(captured)>::type{}}},
        {"fromFile", Any{std::decay<decltype(from_file)>::type{}}},
        {"fromRank", Any{std::decay<decltype(from_rank)>::type{}}},
        {"piece", Any{std::decay<decltype(piece)>::type{}}},
        {"promotion", Any{std::decay<decltype(promotion)>::type{}}},
        {"san", Any{std::decay<decltype(san)>::type{}}},
        {"toFile", Any{std::decay<decltype(to_file)>::type{}}},
        {"toRank", Any{std::decay<decltype(to_rank)>::type{}}},
    },
    captured(variables_["captured"].as<std::decay<decltype(captured)>::type>()),
    from_file(variables_["fromFile"].as<std::decay<decltype(from_file)>::type>()),
    from_rank(variables_["fromRank"].as<std::decay<decltype(from_rank)>::type>()),
    piece(variables_["piece"].as<std::decay<decltype(piece)>::type>()),
    promotion(variables_["promotion"].as<std::decay<decltype(promotion)>::type>()),
    san(variables_["san"].as<std::decay<decltype(san)>::type>()),
    to_file(variables_["toFile"].as<std::decay<decltype(to_file)>::type>()),
    to_rank(variables_["toRank"].as<std::decay<decltype(to_rank)>::type>())
{
    for(auto&& obj : init)
    {
      variables_.emplace(std::make_pair(std::move(obj.first), std::move(obj.second)));
    }
}

Move_::~Move_() = default;

void Move_::resize(const std::string& name, std::size_t size)
{
    try
    {
        Game_object_::resize(name, size);
        return;
    }
    catch(...){}
    throw Bad_manipulation(name + " in Move treated as a vector, but it is not a vector.");
}

void Move_::change_vec_values(const std::string& name, std::vector<std::pair<std::size_t, Any>>& values)
{
    try
    {
        Game_object_::change_vec_values(name, values);
        return;
    }
    catch(...){}
    throw Bad_manipulation(name + " in Move treated as a vector, but it is not a vector.");
}

void Move_::remove_key(const std::string& name, Any& key)
{
    try
    {
        Game_object_::remove_key(name, key);
        return;
    }
    catch(...){}
    throw Bad_manipulation(name + " in Move treated as a map, but it is not a map.");
}

std::unique_ptr<Any> Move_::add_key_value(const std::string& name, Any& key, Any& value)
{
    try
    {
        return Game_object_::add_key_value(name, key, value);
    }
    catch(...){}
    throw Bad_manipulation(name + " in Move treated as a map, but it is not a map.");
}

bool Move_::is_map(const std::string& name)
{
    try
    {
        return Game_object_::is_map(name);
    }
    catch(...){}
    return false;
}

void Move_::rebind_by_name(Any* to_change, const std::string& member, std::shared_ptr<Base_object> ref)
{
   if(member == "captured")
   { 
      to_change->as<Piece>() = std::static_pointer_cast<Piece_>(ref);
      return;
   }
   if(member == "piece")
   { 
      to_change->as<Piece>() = std::static_pointer_cast<Piece_>(ref);
      return;
   }
   try
   {
      Game_object_::rebind_by_name(to_change, member, ref);
      return;
   }
   catch(...){}
   throw Bad_manipulation(member + " in Move treated as a reference, but it is not a reference.");
}


} // chess

} // cpp_client
