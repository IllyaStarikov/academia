// DO NOT MODIFY THIS FILE
// Never try to directly create an instance of this class, or modify its member variables.
// This contains implementation details, written by code, and only useful to code

#include "../game_object.hpp"
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

void Game_object_::log(const std::string& message)
{
    std::string order = R"({"event": "run", "data": {"functionName": "log", "caller": {"id": ")";
    order += this->id + R"("}, "args": {)";

    order += std::string("\"message\":") + std::string("\"") + message + "\"";

    order += "}}}";
    Chess::instance()->send(order);
    //Go until not a delta
    std::unique_ptr<Any> info;
    //until a not bool is seen (i.e., the delta has been processed)
    do
    {
        info = Chess::instance()->handle_response();
    } while(info->type() == typeid(bool));
    return;
}


Game_object_::Game_object_(std::initializer_list<std::pair<std::string, Any&&>> init) :
    Base_object{
        {"gameObjectName", Any{std::decay<decltype(game_object_name)>::type{}}},
        {"id", Any{std::decay<decltype(id)>::type{}}},
        {"logs", Any{std::decay<decltype(logs)>::type{}}},
    },
    game_object_name(variables_["gameObjectName"].as<std::decay<decltype(game_object_name)>::type>()),
    id(variables_["id"].as<std::decay<decltype(id)>::type>()),
    logs(variables_["logs"].as<std::decay<decltype(logs)>::type>())
{
    for(auto&& obj : init)
    {
      variables_.emplace(std::make_pair(std::move(obj.first), std::move(obj.second)));
    }
}

Game_object_::~Game_object_() = default;

void Game_object_::resize(const std::string& name, std::size_t size)
{
    if(name == "logs")
    {
        auto& vec = variables_["logs"].as<std::decay<decltype(logs)>::type>();
        vec.resize(size);
        return;
    }
    throw Bad_manipulation(name + " in Game_object treated as a vector, but it is not a vector.");
}

void Game_object_::change_vec_values(const std::string& name, std::vector<std::pair<std::size_t, Any>>& values)
{
    if(name == "logs")
    {
        using type = std::decay<decltype(logs)>::type;
        auto& vec = variables_["logs"].as<type>();
        for(auto&& val : values)
        { 
            vec[val.first] = std::move(val.second.as<type::value_type>());
        }
        return;
    } 
    throw Bad_manipulation(name + " in Game_object treated as a vector, but it is not a vector.");
}

void Game_object_::remove_key(const std::string& name, Any& key)
{
    throw Bad_manipulation(name + " in Game_object treated as a map, but it is not a map.");
}

std::unique_ptr<Any> Game_object_::add_key_value(const std::string& name, Any& key, Any& value)
{
    throw Bad_manipulation(name + " in Game_object treated as a map, but it is not a map.");
}

bool Game_object_::is_map(const std::string& name)
{
    return false;
}

void Game_object_::rebind_by_name(Any* to_change, const std::string& member, std::shared_ptr<Base_object> ref)
{
   throw Bad_manipulation(member + " in Game_object treated as a reference, but it is not a reference.");
}

    Base_game* Game_object_::get_game() { return Chess::instance(); }

} // chess

} // cpp_client
