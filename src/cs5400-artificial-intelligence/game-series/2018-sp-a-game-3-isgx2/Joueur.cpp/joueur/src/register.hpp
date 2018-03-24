#ifndef REGISTER_HPP
#define REGISTER_HPP

#include <memory>
#include <unordered_map>
#include <string>
#include <algorithm>
#include <functional>
#include <cctype>

namespace cpp_client
{

class Base_game;

//Class for registering games and AI's
//More like a functor than anything else though
class Game_registry
{
public:
   //connect a game name to a game object
   //if the game name already exists then it is re-associated with the new game
   Game_registry(const std::string& name,
                 std::unique_ptr<Base_game> game);

   //get a non-owning pointer to a game object
   //throws a range_error exception if the game does not exist
   static Base_game& get_game(const std::string& name);

private:
   struct Hasher
   {
      std::size_t operator()(const std::string& to_hash) const noexcept
      {
         //kind of need to just throw all the character hashes together
         auto shift_amount = 0u;
         std::size_t to_return = 0u;
         for(auto it = to_hash.begin(); it != to_hash.end(); ++it)
         {
            shift_amount ^= (std::hash<char>{}(std::tolower(*it)) << shift_amount);
            ++shift_amount;
            if(shift_amount >= (sizeof(std::size_t) - 1) * 8)
            {
               shift_amount = 0;
            }
         }
         return to_return;
      }
   };

   struct Comper
   {
      bool operator()(const std::string& a, const std::string& b) const noexcept
      {
         if(a.size() != b.size())
         {
            return false;
         }
         return std::equal(a.begin(),
                           a.end(),
                           b.begin(),
                           [](char first, char second)
                           {
                              return std::tolower(first) == std::tolower(second);
                           });
      }
   };
   //the actual data set
   static std::unordered_map<std::string,
                             std::unique_ptr<Base_game>,
                             Hasher,
                             Comper>& name_map()
   {
      static std::unordered_map<std::string,
                                std::unique_ptr<Base_game>,
                                Hasher,
                                Comper> data;
      return data;
   }
};


} // cpp_client

#endif // REGISTER_HPP
