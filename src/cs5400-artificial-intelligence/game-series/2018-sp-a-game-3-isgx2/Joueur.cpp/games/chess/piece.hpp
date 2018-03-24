#ifndef GAMES_CHESS_PIECE_H
#define GAMES_CHESS_PIECE_H

// Piece
// A chess piece.

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
/// A chess piece.
/// </summary>
class Piece_ : public Game_object_
{
public:

    /// <summary>
    /// When the Piece has been captured (removed from the board) this is true. Otherwise false.
    /// </summary>
    const bool& captured;

    /// <summary>
    /// The file (column) coordinate of the Piece represented as a letter [a-h], with 'a' starting at the left of the board.
    /// </summary>
    const std::string& file;

    /// <summary>
    /// If the Piece has moved from its starting position.
    /// </summary>
    const bool& has_moved;

    /// <summary>
    /// The player that controls this chess Piece.
    /// </summary>
    const Player& owner;

    /// <summary>
    /// The rank (row) coordinate of the Piece represented as a number [1-8], with 1 starting at the bottom of the board.
    /// </summary>
    const int& rank;

    /// <summary>
    /// The type of chess Piece this is, either 'King, 'Queen', 'Knight', 'Rook', 'Bishop', or 'Pawn'.
    /// </summary>
    const std::string& type;

    // You can add additional member variables here. None of them will be tracked or updated by the server.


    /// <summary>
    /// moves the _piece from its current location to the given rank and file.
    /// </summary>
    /// <param name="file"> The file coordinate to move to. Must be [a-h]. </param>
    /// <param name="rank"> The rank coordinate to move to. Must be [1-8]. </param>
    /// <param name="promotion_type"> If this is a Pawn moving to the end of the board then this parameter is what to promote it to. When used must be 'Queen', 'Knight', 'Rook', or 'Bishop'. </param>
    Move move(const std::string& file, int rank, const std::string& promotion_type = "");

  
   // <<-- Creer-Merge: methods -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
   // You can add additional methods here.

   ~Piece_();

   // ####################
   // Don't edit these!
   // ####################
   /// \cond FALSE
   Piece_(std::initializer_list<std::pair<std::string, Any&&>> init);
   Piece_() : Piece_({}){}
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

#endif // GAMES_CHESS_PIECE_H
