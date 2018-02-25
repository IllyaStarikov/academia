#include "base_ai.hpp"
#include "sgr.hpp"

#include <iostream>

namespace cpp_client
{

Base_ai::~Base_ai() = default;

void Base_ai::invalid(const std::string& message)
{
   std::cerr << sgr::text_yellow << "Invalid: " << message << sgr::reset << '\n';
}

const std::string& Base_ai::get_setting(const char* key) const noexcept
{
   // Have a dummy string for return null if needed
   static const std::string dummy{""};
   if(passed_params_.count(key))
   {
      return passed_params_.at(key);
   }
   else
   {
      return dummy;
   }
}

const std::string& Base_ai::get_setting(const std::string& key) const noexcept
{
   return get_setting(key.c_str());
}

} // cpp_client
