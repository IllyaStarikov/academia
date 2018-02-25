#ifndef BASE_AI_HPP
#define BASE_AI_HPP

#include "any.hpp"

#include <string>
#include <vector>
#include <unordered_map>

namespace cpp_client
{

class Base_game;
class Base_object;

class Base_ai
{
public:
   /// <summary>
   /// Gets an AI setting passed to the program via the '--aiSettings' flag.
   /// Returns the empty string if the key was not set
   /// </summary>
   /// <param name="key">The key of the setting to retrieve the value for.</param>
   /// <returns>The string value set, or the empty string if none.</returns>
   const std::string& get_setting(const char* key) const noexcept;
   const std::string& get_setting(const std::string& key) const noexcept;

   /// \cond FALSE
   virtual std::string get_name() const = 0;
   virtual void start() = 0;
   virtual void ended(bool won, const std::string& reason) = 0;
   virtual void invalid(const std::string& message);
   virtual void game_updated() = 0;
   virtual std::string invoke_by_name(const std::string& name,
                                      const std::unordered_map<std::string, Any>& args) = 0;
   virtual ~Base_ai();
   virtual void set_game(Base_game* ptr) = 0;
   virtual void set_player(std::shared_ptr<Base_object> obj) = 0;
   virtual void print_win_loss_info() = 0;
   /// \endcond

private:
   std::unordered_map<std::string, std::string> passed_params_;

   friend void Base_game::set_ai_parameters(const std::string& params);
};

} // cpp_client

#endif // BASE_AI_HPP
