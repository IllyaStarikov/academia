#include "connection.hpp"
#include "exceptions.hpp"
#include "sgr.hpp"

#ifdef WIN32
   #include "windows_connection.hpp"
#else
   #include "unix_connection.hpp"
#endif

#include <array>
#include <iostream>
#include <chrono>
#include <thread>

namespace cpp_client
{

std::string Connection::recieve()
{
   auto msg = conn_->recieve();
   if(print_communication_)
   {
      std::cout << sgr::text_magenta << "FROM SERVER <-- " << msg << sgr::reset << '\n';
   }
   return msg;
}

void Connection::send(const std::string& msg)
{
   using namespace std::chrono;
   const auto time = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
   if(print_communication_)
   {
      std::cout << sgr::text_magenta
                << "TO SERVER --> "
                << msg.substr(0, msg.size() - 1)
                << ", \"sentTime\": "
                << time << "}"
                << sgr::reset
                << '\n';
   }
   //cut out the last } and append the time sent
   conn_->send(msg.substr(0, msg.size() - 1));
   conn_->send(R"(, "sentTime": )" + std::to_string(time) + "}\x04");
}

void Connection::connect(const char* host, unsigned port, bool print)
{
   if(print)
   {
      std::cout << sgr::text_cyan << "Connecting to: " << host << ":" << port << '\n' << sgr::reset;
   }
   conn_->connect(host, port);
}

Connection::Connection(bool print_communication) :
   conn_(new Connection_internal),
   print_communication_(print_communication) {}


Connection::Connection(Connection&&) = default;
Connection& Connection::operator=(Connection&&) = default;
Connection::~Connection() = default;

} // cpp_client
