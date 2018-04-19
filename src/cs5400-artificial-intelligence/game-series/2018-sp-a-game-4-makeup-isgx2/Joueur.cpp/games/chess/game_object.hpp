#ifndef GAMES_CHESS_GAME_OBJECT_H
#define GAMES_CHESS_GAME_OBJECT_H

// GameObject
// An object in the game. The most basic class that all game classes should inherit from automatically.

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


#include "../../joueur/src/base_object.hpp"
#include "impl/chess_fwd.hpp"

// you can add additional #includes here

namespace cpp_client
{

namespace chess
{

/// <summary>
/// An object in the game. The most basic class that all game classes should inherit from automatically.
/// </summary>
class Game_object_ : public Base_object
{
public:

    /// <summary>
    /// String representing the top level Class that this game object is an instance of. Used for reflection to create new instances on clients, but exposed for convenience should AIs want this data.
    /// </summary>
    const std::string& game_object_name;

    /// <summary>
    /// A unique id for each instance of a GameObject or a sub class. Used for client and server communication. Should never change value after being set.
    /// </summary>
    const std::string& id;

    /// <summary>
    /// Any strings logged will be stored here. Intended for debugging.
    /// </summary>
    const std::vector<std::string>& logs;

    // You can add additional member variables here. None of them will be tracked or updated by the server.


    /// <summary>
    /// adds a message to this _game_object's logs. _intended for your own debugging purposes, as strings stored here are saved in the gamelog.
    /// </summary>
    /// <param name="message"> A string to add to this GameObject's log. Intended for debugging. </param>
    void log(const std::string& message);


   // <<-- Creer-Merge: methods -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
   // You can add additional methods here.

   ~Game_object_();

   // ####################
   // Don't edit these!
   // ####################
   /// \cond FALSE
   Game_object_(std::initializer_list<std::pair<std::string, Any&&>> init);
   Game_object_() : Game_object_({}){}
   virtual void resize(const std::string& name, std::size_t size) override;
   virtual void change_vec_values(const std::string& name, std::vector<std::pair<std::size_t, Any>>& values) override;
   virtual void remove_key(const std::string& name, Any& key) override;
   virtual std::unique_ptr<Any> add_key_value(const std::string& name, Any& key, Any& value) override;
   virtual bool is_map(const std::string& name) override;
   virtual void rebind_by_name(Any* to_change, const std::string& member, std::shared_ptr<Base_object> ref) override;
    virtual Base_game* get_game() override;
    /// \endcond
    // ####################
    // Don't edit these!
    // ####################
};

} // chess

} // cpp_client

#endif // GAMES_CHESS_GAME_OBJECT_H
