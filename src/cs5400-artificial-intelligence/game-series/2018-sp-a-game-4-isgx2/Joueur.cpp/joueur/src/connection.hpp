#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <memory>
#include <string>

namespace cpp_client
{

//customization point (in the .cpp)
class Connection_internal;

class Connection
{
public:
   Connection(bool print_communication = false);
   ~Connection();

   //disable copying
   Connection(const Connection&) = delete;
   Connection& operator=(const Connection&) = delete;

   //default moves
   Connection(Connection&&);
   Connection& operator=(Connection&&);

   //connect to a specified host/port over TCP
   //throws a Communication_error if it fails
   void connect(const char* host, unsigned port, bool print = true);

   //send a message to the connected host
   //the required termination byte will also be sent
   //throws a Communication_error if it fails
   void send(const std::string& msg);

   //recieve a message from the connected host
   //throws a Communication_error if it fails
   std::string recieve();

   //changes if communication should be printed or not
   void set_print_communication(bool should_print) noexcept
   {
      print_communication_ = should_print;
   }

private:
   std::unique_ptr<Connection_internal> conn_;
   bool print_communication_;
};

} // cpp_client

#endif // CONNECTION_HPP
