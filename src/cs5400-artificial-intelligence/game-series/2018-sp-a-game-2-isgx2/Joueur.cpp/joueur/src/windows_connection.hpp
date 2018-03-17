#ifndef WINDOWS_CONNECTION_HPP
#define WINDOWS_CONNECTION_HPP

// adapted from https://msdn.microsoft.com/en-us/library/ms738545(v=vs.85).aspx

#include <string>
#include <array>
#include <winsock2.h>
#include <ws2tcpip.h>

namespace cpp_client
{

class Connection_internal
{
public:
   Connection_internal() :
      sock_(INVALID_SOCKET),
      buffer_()
   {
      WSADATA wsa_data;
      const auto res = WSAStartup(MAKEWORD(2, 2), &wsa_data);
      if(res != 0)
      {
         throw Communication_error{"Initialization error - could not connect to server."};
      }
   }

   // translates and throws a communication error on send or recieve
   [[noreturn]] void throw_comm_error()
   {
      using ce = Communication_error;
      switch(WSAGetLastError())
      {
      case WSANOTINITIALISED: throw ce{"WSA wasn't initalized??"};
      case WSAENETDOWN:       throw ce{"Network subsystem failed."};
      case WSAEACCES:         throw ce{"Address is a broadcast address."};
      case WSAEFAULT:         throw ce{"Buffer out of user address space??"};
      case WSAENOBUFS:        throw ce{"No buffers available."};
      case WSAENOTCONN:       throw ce{"Socket not connected??"};
      case WSAENOTSOCK:       throw ce{"Socket isn't a socket??"};
      case WSAEMSGSIZE:       throw ce{"Message size too big."};
      case WSAEHOSTUNREACH:   throw ce{"Host could not be reached."};
      case WSAETIMEDOUT:      throw ce{"Connection timed out."};
      default:                throw ce{"Uknown error."};
      }
   }

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
      ZeroMemory(&hints, sizeof(hints));
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
         using ce = Communication_error;
         if(resaddr != 0)
         {
            switch(resaddr)
            {
            case WSATRY_AGAIN:          continue;
            case WSANO_RECOVERY:        throw ce{"Could not resolve host name - Unrecoverable error."};
            case WSA_NOT_ENOUGH_MEMORY: throw ce{"Could not resolve host name - Out of memory."};
            case WSAHOST_NOT_FOUND:     throw ce{"Could not resolve host name - Host not found."};
            default:                    throw ce{"Could not resolve host name - Unknown error."};
            }
         }
         // now create the socket by trying to connect to all possible addresses
         for(auto ptr = result; ptr; ptr = ptr->ai_next)
         {
            sock_ = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
            if(sock_ == INVALID_SOCKET)
            {
               continue;
            }
            const auto res = ::connect(sock_, ptr->ai_addr, static_cast<int>(ptr->ai_addrlen));
            if(res == SOCKET_ERROR)
            {
               closesocket(sock_);
               sock_ = INVALID_SOCKET;
            }
         }
      }
      // if sock_ is invalid some sort of error occured
      if(sock_ == INVALID_SOCKET)
      {
         throw Communication_error("Could not connect to server.");
      }
   }

   void send(const std::string& msg)
   {
      // need to fragment messages if it gets too large
      static const auto max_size = [this](){
         unsigned size;
         auto size_val = static_cast<int>(sizeof(size));
         getsockopt(sock_,
                    SOL_SOCKET,
                    SO_MAX_MSG_SIZE,
                    reinterpret_cast<char*>(&size),
                    &size_val);
         return static_cast<decltype(msg.size())>(size);
      }();
      const char* loc = msg.c_str();
      auto left = msg.size();
      // send the message in max_size chunks
      while(left > 0)
      {
         // std::min in parentheses because min is a Windows macro
         const auto to_send = (std::min)(max_size, left);
         if(::send(sock_, loc, to_send, 0) == SOCKET_ERROR)
         {
            throw_comm_error();
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
         if(received == SOCKET_ERROR)
         {
            throw_comm_error();
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
      if(sock_ != INVALID_SOCKET)
      {
         closesocket(sock_);
      }
      WSACleanup();
   }

private:
   SOCKET sock_;
   std::string buffer_;
};

} // cpp_client

#endif // WINDOWS_CONNECTION_HPP
