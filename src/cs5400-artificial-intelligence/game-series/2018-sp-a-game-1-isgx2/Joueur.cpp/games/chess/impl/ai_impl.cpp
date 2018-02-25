/////////////////////////////////////////////////////
// Implementation detail!!
// Do not edit anything past here!!
/////////////////////////////////////////////////////


/// \cond FALSE

#include "../ai.hpp"

namespace cpp_client
{

namespace chess
{


std::string AI::invoke_by_name(const std::string& name,
                               const std::unordered_map<std::string, Any>& args)
{

    if(name == "runTurn")
    {
        auto ret = run_turn(

        );
        return attr_wrapper::json_val(ret);
    }
    throw Bad_response("AI told to run unknown action " + name);
}

void AI::set_game(Base_game* ptr)
{
    game = static_cast<Game>(ptr);
}

void AI::set_player(std::shared_ptr<Base_object> obj)
{
    player = std::static_pointer_cast<Player_>(obj);
}

void AI::print_win_loss_info()
{
    if(player->lost)
    {
        ended(false, player->reason_lost);
        std::cout << sgr::text_green
                     << "Game is over. I lost :( because: " << player->reason_lost << '\n';
    }
    else
    {
        ended(true, player->reason_won);
        std::cout << sgr::text_green
                     << "Game is over. I won! because: " << player->reason_won << '\n';
    }
    std::cout << sgr::reset;
}

} // end namespace chess

} // end namespace cpp_client

/// \endcond
