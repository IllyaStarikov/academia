#ifndef GAMES_CHESS_PLAYER_H
#define GAMES_CHESS_PLAYER_H

// Player
// A player in this game. Every AI controls one player.

// DO NOT MODIFY THIS FILE
// Never try to directly create an instance of this class, or modify its member variables.
// Instead, you should only be reading its variables and calling its functions.

#include <vector>
#include <queue>
#include <deque>
#include <unordered_map>
#include <string>
#include <initializer_list>

#include "../../joueur/src/any.hpp"

#include "game_object.hpp"

#include "impl/chess_fwd.hpp"

// you can add additional #includes here

namespace cpp_client
{

namespace chess
{

/// <summary>
/// A player in this game. Every AI controls one player.
/// </summary>
class Player_ : public Game_object_
{
public:

    /// <summary>
    /// What type of client this is, e.g. 'Python', 'JavaScript', or some other language. For potential data mining purposes.
    /// </summary>
    const std::string& client_type;

    /// <summary>
    /// The color (side) of this player. Either 'White' or 'Black', with the 'White' player having the first move.
    /// </summary>
    const std::string& color;

    /// <summary>
    /// True if this player is currently in check, and must move out of check, false otherwise.
    /// </summary>
    const bool& in_check;

    /// <summary>
    /// If the player lost the game or not.
    /// </summary>
    const bool& lost;

    /// <summary>
    /// If the Player has made their move for the turn. true means they can no longer move a Piece this turn.
    /// </summary>
    const bool& made_move;

    /// <summary>
    /// The name of the player.
    /// </summary>
    const std::string& name;

    /// <summary>
    /// This player's opponent in the game.
    /// </summary>
    const Player& opponent;

    /// <summary>
    /// All the uncaptured chess Pieces owned by this player.
    /// </summary>
    const std::vector<Piece>& pieces;

    /// <summary>
    /// The direction your Pieces must go along the rank axis until they reach the other side. Will be +1 if the Player is 'White', or -1 if the Player is 'Black'.
    /// </summary>
    const int& rank_direction;

    /// <summary>
    /// The reason why the player lost the game.
    /// </summary>
    const std::string& reason_lost;

    /// <summary>
    /// The reason why the player won the game.
    /// </summary>
    const std::string& reason_won;

    /// <summary>
    /// The amount of time (in ns) remaining for this AI to send commands.
    /// </summary>
    const double& time_remaining;

    /// <summary>
    /// If the player won the game or not.
    /// </summary>
    const bool& won;

    // You can add additional member variables here. None of them will be tracked or updated by the server.


   // <<-- Creer-Merge: methods -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
   // You can add additional methods here.

   ~Player_();

   // ####################
   // Don't edit these!
   // ####################
   /// \cond FALSE
   Player_(std::initializer_list<std::pair<std::string, Any&&>> init);
   Player_() : Player_({}){}
   virtual void resize(const std::string& name, std::size_t size) override;
   virtual void change_vec_values(const std::string& name, std::vector<std::pair<std::size_t, Any>>& values) override;
   virtual void remove_key(const std::string& name, Any& key) override;
   virtual std::unique_ptr<Any> add_key_value(const std::string& name, Any& key, Any& value) override;
   virtual bool is_map(const std::string& name) override;
   virtual void rebind_by_name(Any* to_change, const std::string& member, std::shared_ptr<Base_object> ref) override;
    /// \endcond
    // ####################
    // Don't edit these!
    // ####################
};

} // chess

} // cpp_client

#endif // GAMES_CHESS_PLAYER_H
