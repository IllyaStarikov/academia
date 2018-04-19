#ifndef GAMES_CHESS_MOVE_H
#define GAMES_CHESS_MOVE_H

// Move
// Contains all details about a Piece's move in the game.

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
/// Contains all details about a Piece's move in the game.
/// </summary>
class Move_ : public Game_object_
{
public:

    /// <summary>
    /// The Piece captured by this Move, null if no capture.
    /// </summary>
    const Piece& captured;

    /// <summary>
    /// The file the Piece moved from.
    /// </summary>
    const std::string& from_file;

    /// <summary>
    /// The rank the Piece moved from.
    /// </summary>
    const int& from_rank;

    /// <summary>
    /// The Piece that was moved.
    /// </summary>
    const Piece& piece;

    /// <summary>
    /// The Piece type this Move's Piece was promoted to from a Pawn, empty string if no promotion occurred.
    /// </summary>
    const std::string& promotion;

    /// <summary>
    /// The standard algebraic notation (SAN) representation of the move.
    /// </summary>
    const std::string& san;

    /// <summary>
    /// The file the Piece moved to.
    /// </summary>
    const std::string& to_file;

    /// <summary>
    /// The rank the Piece moved to.
    /// </summary>
    const int& to_rank;

    // You can add additional member variables here. None of them will be tracked or updated by the server.



   // <<-- Creer-Merge: methods -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
   // You can add additional methods here.

   ~Move_();

   // ####################
   // Don't edit these!
   // ####################
   /// \cond FALSE
   Move_(std::initializer_list<std::pair<std::string, Any&&>> init);
   Move_() : Move_({}){}
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

#endif // GAMES_CHESS_MOVE_H
