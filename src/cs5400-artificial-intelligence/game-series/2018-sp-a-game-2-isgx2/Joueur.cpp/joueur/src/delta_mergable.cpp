#include "delta_mergable.hpp"

#include "any.hpp"
#include "base_ai.hpp"
#include "base_object.hpp"

namespace cpp_client
{

struct Delta_mergable_delay_variables
{
   std::unordered_map<std::string, Any> variables_;
};

Delta_mergable::~Delta_mergable() = default;

Delta_mergable::Delta_mergable(std::initializer_list<std::pair<std::string, Any&&>> init) :
   variable_storage_(new Delta_mergable_delay_variables{}),
   variables_(variable_storage_->variables_)
{
   for(auto&& obj : init)
   {
      variables_.emplace(std::make_pair(std::move(obj.first), std::move(obj.second)));
   }
}

void Delta_mergable::erase(const std::string& to_erase)
{
   variables_.erase(to_erase);
}

std::ostream& operator<<(std::ostream& out, const Delta_mergable& obj)
{
   for(const auto& var : obj.variables_)
   {
      out << var.first << ": " << var.second << '\n';
   }
   return out;
}

} // namespace cpp_client

