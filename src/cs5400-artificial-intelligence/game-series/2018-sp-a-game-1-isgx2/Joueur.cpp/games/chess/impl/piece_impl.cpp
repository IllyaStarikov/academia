// DO NOT MODIFY THIS FILE
// Never try to directly create an instance of this class, or modify its member variables.
// This contains implementation details, written by code, and only useful to code

#include "../piece.hpp"
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

Move Piece_::move(const std::string& file, int rank, const std::string& promotion_type)
{
    std::string order = R"({"event": "run", "data": {"functionName": "move", "caller": {"id": ")";
    order += this->id + R"("}, "args": {)";

    order += std::string("\"file\":") + std::string("\"") + file + "\"";

    order += std::string(",\"rank\":") + std::to_string(rank);

    order += std::string(",\"promotionType\":") + std::string("\"") + promotion_type + "\"";

    order += "}}}";
    Chess::instance()->send(order);
    //Go until not a delta
    std::unique_ptr<Any> info;
    //until a not bool is seen (i.e., the delta has been processed)
    do
    {
        info = Chess::instance()->handle_response();
    } while(info->type() == typeid(bool));
    //reference - just pull the id
    auto doc = info->as<rapidjson::Document*>();
    auto loc = doc->FindMember("data");
    if(loc == doc->MemberEnd())
    {
        return nullptr;
    }
    auto& val = loc->value;
    if(val.IsNull())
    {
        return nullptr;
    }
    else
    {
        auto target = attr_wrapper::get_attribute<std::string>(val, "id");
        return std::dynamic_pointer_cast<Move_>(Chess::instance()->get_objects()[target]);
    }
}


Piece_::Piece_(std::initializer_list<std::pair<std::string, Any&&>> init) :
    Game_object_{
        {"captured", Any{std::decay<decltype(captured)>::type{}}},
        {"file", Any{std::decay<decltype(file)>::type{}}},
        {"hasMoved", Any{std::decay<decltype(has_moved)>::type{}}},
        {"owner", Any{std::decay<decltype(owner)>::type{}}},
        {"rank", Any{std::decay<decltype(rank)>::type{}}},
        {"type", Any{std::decay<decltype(type)>::type{}}},
    },
    captured(variables_["captured"].as<std::decay<decltype(captured)>::type>()),
    file(variables_["file"].as<std::decay<decltype(file)>::type>()),
    has_moved(variables_["hasMoved"].as<std::decay<decltype(has_moved)>::type>()),
    owner(variables_["owner"].as<std::decay<decltype(owner)>::type>()),
    rank(variables_["rank"].as<std::decay<decltype(rank)>::type>()),
    type(variables_["type"].as<std::decay<decltype(type)>::type>())
{
    for(auto&& obj : init)
    {
      variables_.emplace(std::make_pair(std::move(obj.first), std::move(obj.second)));
    }
}

Piece_::~Piece_() = default;

void Piece_::resize(const std::string& name, std::size_t size)
{
    try
    {
        Game_object_::resize(name, size);
        return;
    }
    catch(...){}
    throw Bad_manipulation(name + " in Piece treated as a vector, but it is not a vector.");
}

void Piece_::change_vec_values(const std::string& name, std::vector<std::pair<std::size_t, Any>>& values)
{
    try
    {
        Game_object_::change_vec_values(name, values);
        return;
    }
    catch(...){}
    throw Bad_manipulation(name + " in Piece treated as a vector, but it is not a vector.");
}

void Piece_::remove_key(const std::string& name, Any& key)
{
    try
    {
        Game_object_::remove_key(name, key);
        return;
    }
    catch(...){}
    throw Bad_manipulation(name + " in Piece treated as a map, but it is not a map.");
}

std::unique_ptr<Any> Piece_::add_key_value(const std::string& name, Any& key, Any& value)
{
    try
    {
        return Game_object_::add_key_value(name, key, value);
    }
    catch(...){}
    throw Bad_manipulation(name + " in Piece treated as a map, but it is not a map.");
}

bool Piece_::is_map(const std::string& name)
{
    try
    {
        return Game_object_::is_map(name);
    }
    catch(...){}
    return false;
}

void Piece_::rebind_by_name(Any* to_change, const std::string& member, std::shared_ptr<Base_object> ref)
{
   if(member == "owner")
   { 
      to_change->as<Player>() = std::static_pointer_cast<Player_>(ref);
      return;
   }
   try
   {
      Game_object_::rebind_by_name(to_change, member, ref);
      return;
   }
   catch(...){}
   throw Bad_manipulation(member + " in Piece treated as a reference, but it is not a reference.");
}


} // chess

} // cpp_client
