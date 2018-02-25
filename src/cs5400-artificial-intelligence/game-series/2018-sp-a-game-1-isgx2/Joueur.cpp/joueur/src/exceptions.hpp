#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include <stdexcept>

namespace cpp_client
{

class Game_not_found : public std::range_error
{
   using std::range_error::range_error;
};

class Communication_error : public std::runtime_error
{
   using std::runtime_error::runtime_error;
};

class Unknown_type : public std::runtime_error
{
   using std::runtime_error::runtime_error;
};

class Parse_error : public std::runtime_error
{
   using std::runtime_error::runtime_error;
};

class Bad_response : public std::runtime_error
{
   using std::runtime_error::runtime_error;
};

class Bad_manipulation : public std::runtime_error
{
   using std::runtime_error::runtime_error;
};

class Server_error : public std::runtime_error
{
   using std::runtime_error::runtime_error;
};

class Input_error : public std::runtime_error
{
   using std::runtime_error::runtime_error;
};

class Unknown_error : public std::runtime_error
{
   using std::runtime_error::runtime_error;
};

} // cpp_client


#endif // EXCEPTIONS_HPP
