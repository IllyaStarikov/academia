// DO NOT MODIFY THIS FILE
// Never try to directly create an instance of this class, or modify its member variables.
// This contains implementation details, written by code, and only useful to code

#include "chess.hpp"
#include "../../../joueur/src/register.hpp"

#include "../../../joueur/src/exceptions.hpp"

namespace cpp_client
{

namespace chess
{

//register the game
Game_registry registration("Chess",
                           std::unique_ptr<Chess>(new Chess));

std::unique_ptr<Base_ai> Chess::generate_ai()
{
    return std::unique_ptr<Base_ai>(new AI);
}

std::shared_ptr<Base_object> Chess::generate_object(const std::string& type)
{
    if(type == "GameObject")
    {
        return std::make_shared<Game_object_>();
    }
    else if(type == "Move")
    {
        return std::make_shared<Move_>();
    }
    else if(type == "Piece")
    {
        return std::make_shared<Piece_>();
    }
    else if(type == "Player")
    {
        return std::make_shared<Player_>();
    }
    throw Unknown_type("Unknown type " + type + " encountered.");
}

} // chess

} // cpp_client
