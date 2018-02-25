//Don't edit this file
//See readme.md for details on what to edit

#include "tclap/CmdLine.h"
#include "attr_wrapper.hpp"
#include "register.hpp"
#include "sgr.hpp"
#include "connection.hpp"
#include "base_game.hpp"
#include "base_ai.hpp"

#include <exception>
#include <iostream>
#include <csignal>

int main(int argc, const char* argv[])
{
   using namespace cpp_client;
   try
   {
      TCLAP::CmdLine cmd("Runs the C++ client.  Game name must be provided.");
      TCLAP::ValueArg<std::string> string_args[] =
      {
         {
            "s",
            "server",
            "The url to the server you want to connect to (e.g., localhost)",
            false,
            "localhost",
            "server URL"
         },
         {
            "n",
            "name",
            "The name you want to use as your AI's player name. "
               "This overrides the name you set in your code.",
            false,
            "",
            "string"
         },
         {
            "w",
            "password",
            "The password required for authentication on official servers.",
            false,
            "",
            "string"
         },
         {
            "",
            "gameSettings",
            "Any settings for the game server to force. "
               "Must be url params formatted (key=value&otherKey=otherValue)",
            false,
            "",
            "string"
         },
         {
            "r",
            "session",
            "The requested game session you want to play on the server",
            false,
            "*",
            "string"
         },
         {
            "",
            "aiSettings",
            "Any settings for the AI.  Delimit pairs by an ampersand (key=value&otherKey=otherValue)",
            false,
            "",
            "string"
         }
      };
      //enum for accessing string options
      enum
      {
         server,
         player_name,
         password,
         settings,
         session,
         ai_settings
      };
      TCLAP::ValueArg<int> int_args[] =
      {
         {
            "p",
            "port",
            "The port to connect to on the server.",
            false,
            3000,
            "port number"
         },
         {
            "i",
            "index",
            "The player number you want to be, with 0 being the first player.",
            false,
            -1,
            "player index"
         }
      };
      enum
      {
         port,
         player_index,
      };
      //game argument
      TCLAP::UnlabeledValueArg<std::string>
         game_arg("game", "The name of the game you want to play on the server.", true, "", "Game");
      cmd.add(game_arg);
      //debug flag
      TCLAP::SwitchArg
         print_io("", "printIO", "(debugging) Print IO through the TCP socket to stdout.", false);
      cmd.add(print_io);
      //add each option
      for(auto i = 0u; i < sizeof(string_args) / sizeof(string_args[0]); ++i)
      {
         cmd.add(string_args[i]);
      }
      for(auto i = 0u; i < sizeof(int_args) / sizeof(int_args[0]); ++i)
      {
         cmd.add(int_args[i]);
      }
      cmd.parse(argc, argv);
      //check for port nonsense
      auto server_str = string_args[server].getValue();
      auto port_num = int_args[port].getValue();
      //if there is a ':' in the server override the port number
      const auto colon_loc = server_str.find(':');
      if(colon_loc != server_str.npos)
      {
         port_num = std::stoi(server_str.substr(colon_loc + 1));
         server_str = server_str.substr(0, colon_loc);
      }
      //retrieve the game (use server aliases)
      const auto game_name = Base_game::get_alias(game_arg.getValue().c_str(),
                                                  server_str.c_str(),
                                                  port_num);
      auto& game = Game_registry::get_game(game_name);
      //set up some stuff for the game
      game.set_print_communication(print_io.getValue());
      game.connect(server_str.c_str(), port_num);
      game.set_player_index(int_args[player_index].getValue());
      game.set_password(string_args[password].getValue());
      game.set_session(string_args[session].getValue());
      game.set_name(string_args[player_name].getValue());
      game.set_settings(string_args[settings].getValue());
      game.set_ai_parameters(string_args[ai_settings].getValue());
      game.go();
   }
   // yuck, a macro - best option here though...
   #define CATCHER(x)                                                 \
      catch(const x& e)                                               \
      {                                                               \
         std::cerr << sgr::text_red << "[" #x "] An error occured:\n" \
                   << e.what() << sgr::reset << std::endl;            \
      }
   CATCHER(Game_not_found)
   CATCHER(Communication_error)
   CATCHER(Unknown_type)
   CATCHER(Parse_error)
   CATCHER(Bad_response)
   CATCHER(Bad_manipulation)
   CATCHER(Server_error)
   CATCHER(Input_error)
   CATCHER(Unknown_error)
   catch(const std::exception& e)
   {
      std::cerr << sgr::text_red << "Some error occurred:\n" << e.what() << sgr::reset << std::endl;
      return 1;
   }
   catch(...)
   {
      std::cerr << sgr::text_red << "An unknown error occurred." << sgr::reset << std::endl;
      return 2;
   }
   #undef CATCHER
}
