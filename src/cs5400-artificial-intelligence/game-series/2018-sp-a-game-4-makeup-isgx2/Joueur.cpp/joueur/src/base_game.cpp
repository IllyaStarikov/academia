#include "base_game.hpp"
#include "base_ai.hpp"

#include "delta.hpp"
#include "attr_wrapper.hpp"
#include "base_object.hpp"
#include "any.hpp"

namespace cpp_client
{

Base_game::~Base_game() = default;

std::string Base_game::get_alias(const char* name, const char* server, int port)
{
   Connection conn;
   conn.connect(server, port, false);
   std::string alias = R"({"event": "alias", "data": ")" + std::string(name) + "\"}";
   conn.send(alias);
   const auto resp = conn.recieve();
   rapidjson::Document doc;
   doc.Parse(resp.c_str());
   if(attr_wrapper::get_attribute<std::string>(doc, "event") == "fatal")
   {
      std::cout << sgr::text_red << "Fatal: "
                << attr_wrapper::get_attribute<std::string>(doc["data"], "message") << '\n'
                << sgr::reset;
      exit(1);
   }
   return attr_wrapper::get_attribute<std::string>(doc, "data");
}

void Base_game::go()
{
   //grab the name first (do this again to ensure proper server-side name)
   std::string alias = R"({"event": "alias", "data": ")" + get_game_name() + "\"}";
   conn_.send(alias);
   const auto game_name = handle_response("named")->as<std::string>();
   //start with the same thing each time
   std::string to_send = R"({"event": "play", "data": {"clientType": "c++", "playerIndex": )";
   //now fill in the details
   if(player_index_ == -1)
   {
      to_send += "null,";
   }
   else
   {
      to_send += std::to_string(player_index_) + ",";
   }
   const auto add_standard_str = [&to_send](const std::string& name, const std::string& to_add)
      {
         to_send += "\"" + name + "\":";
         if(to_add == "")
         {
            to_send += "null,";
         }
         else
         {
            to_send += "\"" + to_add + "\",";
         }
      };
   add_standard_str("password", password_);
   add_standard_str("requestedSession", session_);
   add_standard_str("gameSettings", game_settings_);
   to_send += R"("playerName":")";
   if(name_ == "")
   {
      to_send += ai_->get_name();
   }
   else
   {
      to_send += name_;
   }
   to_send += R"(","gameName":")" + game_name + R"("}})";
   conn_.send(to_send);
   //Expecting the "lobbied" message
   handle_response("lobbied");
   //Next the delta message will be received
   handle_response("delta");
   //Start should be next
   handle_response("start");
   //now just do normal handling of events
   while(*handle_response())
   {
      //Intentionally empty
   }
}

std::unique_ptr<Any> Base_game::handle_response(const std::string& expected)
{
   doc_raw_.reset(new rapidjson::Document);
   //first get the response
   resp_ = conn_.recieve();
   //now parse it
   auto& doc = *doc_raw_;
   doc.Parse(resp_.c_str());
   const auto event = attr_wrapper::get_attribute<std::string>(doc, "event");
   //check if it matches the expected (if needed)
   if(event != "fatal" && expected != "" && event != expected)
   {
      throw Bad_response("Expected " + expected + " event; got " + event);
   }
   //now just handle the different possible events
   if(event == "lobbied")
   {
      const auto& data = attr_wrapper::get_loc(doc, "data")->value;
      const auto& constants = attr_wrapper::get_loc(data, "constants")->value;
      //extract game constants
      len_string_ = attr_wrapper::get_attribute<std::string>(constants, "DELTA_LIST_LENGTH");
      remove_string_ = attr_wrapper::get_attribute<std::string>(constants, "DELTA_REMOVED");
      //output the session information
      std::cout << sgr::text_cyan << "In lobby for game '"
                << attr_wrapper::get_attribute<std::string>(data, "gameName")
                << "' in session '"
                << attr_wrapper::get_attribute<std::string>(data, "gameSession") << "'."
                << sgr::reset << std::endl;
   }
   else if(event == "delta")
   {
      apply_delta(doc, *this);
   }
   else if(event == "start")
   {
      //set the AI's fields properly
      const auto& data = attr_wrapper::get_loc(doc, "data")->value;
      const auto id = attr_wrapper::get_attribute<std::string>(data, "playerID");
      ai_->set_game(this);
      ai_->set_player(get_objects()[id]);
      std::cout << sgr::text_green << "Game is starting." << sgr::reset << '\n';
      ai_->start();
   }
   else if(event == "over")
   {
      ai_->print_win_loss_info();
      //output URL info
      const auto& data = attr_wrapper::get_loc(doc, "data")->value;
      const auto mes = data.FindMember("message");
      if(mes != data.MemberEnd())
      {
         std::string final_message = attr_wrapper::as<std::string>(mes->value);
         const auto replace_loc = final_message.find("__HOSTNAME__");
         if(replace_loc != std::string::npos)
         {
            final_message.replace(replace_loc,
                                  std::strlen("__HOSTNAME__"),
                                  hostname_);
         }
         std::cout << sgr::text_cyan
                   << final_message
                   << sgr::reset
                   << '\n'
                   ;
      }
      //exit!
      exit(0);
   }
   else if(event == "fatal")
   {
      const auto data = attr_wrapper::get_loc(doc, "data");
      std::cout << sgr::text_red << "Fatal: "
                << attr_wrapper::get_attribute<std::string>(data->value, "message") << '\n'
                << sgr::reset;
      exit(1);
   }
   else if(event == "order")
   {
      const auto& data = attr_wrapper::get_loc(doc, "data")->value;
      const auto name = attr_wrapper::get_attribute<std::string>(data, "name");
      const auto index = attr_wrapper::get_attribute<unsigned>(data, "index");
      //loop through all parameters and make a map out of them
      const auto& args = attr_wrapper::get_loc(data, "args");
      std::unordered_map<std::string, Any> params;
      //TODO: arguments for orders (apparently they are positional)
      //send finished event with data:
      const std::string order_done =
         R"({"event":"finished","data":{"orderIndex":)" + std::to_string(index)
         + R"(,"returned":)" + ai_->invoke_by_name(name, params) + "}}";
      conn_.send(order_done);
   }
   else if(event == "ran")
   {
      return std::unique_ptr<Any>(new Any{static_cast<rapidjson::Document*>(&doc)});
   }
   else if(event == "invalid")
   {
      //just print out an error message
      const auto data = attr_wrapper::get_loc(doc, "data");
      std::cout << sgr::text_yellow << "Invalid: "
                << attr_wrapper::get_attribute<std::string>(data->value, "message") << '\n'
                << sgr::reset;
   }
   else if(event == "named")
   {
      const auto data = attr_wrapper::get_attribute<std::string>(doc, "data");
      return std::unique_ptr<Any>(new Any{std::string{data}});
   }
   //just some dummy value to indicate that this isn't done yet
   return std::unique_ptr<Any>(new Any{true});
}

void Base_game::set_ai_parameters(const std::string& params)
{
   ai_ = generate_ai();
   // this simplifies code a lot
   if(params.empty())
   {
      return;
   }
   // error on leading ampersands
   if(params[0] == '&')
   {
      throw Input_error("Can not begin AI settings string with &, string was:\n" +
                        params);
   }
   auto split = 0;
   while(true)
   {
      const auto new_split = params.find('&', split + 1);
      const auto to_parse = params.substr(split, new_split - split);
      const auto eq_loc = to_parse.find('=');
      if(eq_loc == params.npos)
      {
         throw Input_error("Could not parse the AI settings string:\n" +
                           params + "\n"
                           "In particular, could not find '=' in \"" + to_parse + "\"");
      }
      const auto key = to_parse.substr(0, eq_loc);
      const auto value = to_parse.substr(eq_loc + 1, std::string::npos);
      ai_->passed_params_[key] = value;
      if(new_split == std::string::npos)
      {
         break;
      }
      split = new_split + 1;
   }
}

} // cpp_client
