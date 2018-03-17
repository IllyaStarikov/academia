#include "base_object.hpp"
#include "any.hpp"
#include "base_ai.hpp"

namespace cpp_client
{

Base_object::~Base_object() = default;
Base_object::Base_object() noexcept : Delta_mergable({}) {}
Base_object::Base_object(std::initializer_list<std::pair<std::string, Any&&>> init) :
   Delta_mergable(init)
{
   ;
}

const std::string& Base_object::get_id() const noexcept
{
   return variables_["id"].as<std::string>();
}

std::unique_ptr<Any> Base_object::add_key_value(const std::string& name,
                                                Any& key,
                                                Any& value)
{
   return nullptr;
}

} // namespace cpp_client
