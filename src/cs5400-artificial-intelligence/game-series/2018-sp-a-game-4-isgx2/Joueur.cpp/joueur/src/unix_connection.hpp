#ifndef UNIX_CONNECTION_HPP
#define UNIX_CONNECTION_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>

#include <string>
#include <array>
#include <cstring>

namespace cpp_client
{

class Connection_internal
{
public:
   Connection_internal() :
      sock_(-1),
      buffer_() {}

   void connect(const char* host, unsigned port)
   {
      struct Free_addr
      {
         addrinfo* info;
         ~Free_addr()
         {
            freeaddrinfo(info);
         }
      };
      // can have temporary name resolution failure so specify a number of tries
      constexpr auto num_tries = 3;
      // set up structures needed
      addrinfo* result;
      addrinfo hints;
      memset(&hints, 0, sizeof(hints));
      hints.ai_family = AF_UNSPEC;
      hints.ai_socktype = SOCK_STREAM;
      hints.ai_protocol = IPPROTO_IP;
      const auto port_str = std::to_string(port);
      // now try to connect
      for(auto i = 0; i < num_tries; ++i)
      {
         const auto resaddr = getaddrinfo(host, port_str.c_str(), &hints, &result);
         // free the memory allocated if going out of scope
         Free_addr dummy{result};
         if(resaddr != 0)
         {
            using ce = Communication_error;
            switch(resaddr)
            {
            case EAI_AGAIN:  continue;
            case EAI_FAIL:   throw ce("Could not resolve host name - Unrecoverable error.");
            case EAI_MEMORY: throw ce("Could not resolve host name - Out of memory.");
            case EAI_NONAME: throw ce("Could not resolve host name - Host not found.");
            default:         throw ce("Could not resolve host name - Unknown error.");
            }
         }
         // now create the socket by trying to connect to all possible addresses
         for(auto ptr = result; ptr; ptr = ptr->ai_next)
         {
            sock_ = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
            if(sock_ == -1)
            {
               continue;
            }
            const auto res = ::connect(sock_, ptr->ai_addr, static_cast<int>(ptr->ai_addrlen));
            if(res == -1)
            {
               close(sock_);
               sock_ = -1;
            }
         }
      }
      // if sock_ is invalid some sort of error occured
      if(sock_ == -1)
      {
         throw Communication_error("Could not connect to server.");
      }
   }

   void send(const std::string& msg)
   {
      // sending too large of a message will fail, but there doesn't
      // seem to be a way to query it at runtime in Linux
      // TCP normal max is 65535 (0xFFFF) but to be safe information is
      // send in 1024 byte chunks [TODO: is this too small?]
      // Most messages should be small anyways so this shouldn't be an issue
      constexpr auto max_size = static_cast<decltype(msg.size())>(1024);
      const char* loc = msg.c_str();
      auto left = msg.size();
      // send the message in max_size chunks
      while(left > 0)
      {
         const auto to_send = std::min(max_size, left);
         if(::send(sock_, loc, to_send, 0) == -1)
         {
            throw Communication_error{"Error sending data to server."};
         }
         left -= to_send;
         loc += to_send;
      }
   }

   std::string recieve()
   {
      std::array<char, 2048> read_buffer;
      std::string to_return;
      to_return.reserve(read_buffer.size());
      //put anything left over into the message to start
      to_return += buffer_;
      auto split_point = to_return.find('\x04');
      while(split_point == std::string::npos)
      {
         const auto received = recv(sock_, read_buffer.data(), read_buffer.size(), 0);
         if(received == -1)
         {
            throw Communication_error("Receiving data failed.");
         }
         to_return.append(read_buffer.data(), received);
         split_point = to_return.find('\x04');
      }
      //now split by the 0x04
      buffer_ = to_return.substr(split_point + 1);
      to_return = to_return.substr(0, split_point);
      return to_return;
   }

   ~Connection_internal()
   {
      if(sock_ != -1)
      {
         close(sock_);
      }
   }

private:
   int sock_;
   std::string buffer_;
};

} // cpp_client

#endif // UNIX_CONNECTION_HPP
