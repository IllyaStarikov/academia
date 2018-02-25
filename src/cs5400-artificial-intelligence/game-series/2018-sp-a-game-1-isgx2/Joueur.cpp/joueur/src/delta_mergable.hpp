#ifndef DELTA_MERGABLE_HPP
#define DELTA_MERGABLE_HPP

#include "exceptions.hpp"

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include <ostream>

namespace cpp_client
{

//kind of stupid, but this needs to be done
class Any;
struct Delta_mergable_delay_variables;
class Base_object;

class Delta_mergable
{
public:
   Delta_mergable(std::initializer_list<std::pair<std::string, Any&&>> init);
   ~Delta_mergable();

   //erase a variable name
   void erase(const std::string& to_erase);

   //so other erasures can compile (should never happen, however)
   template<typename T>
   void erase(const T&)
   {
      throw Bad_manipulation("Non-string erase called on object.");
   }

   std::unique_ptr<Delta_mergable_delay_variables> variable_storage_;
   std::unordered_map<std::string, Any>& variables_;

   //some things to allow doing stuff by name
   virtual void resize(const std::string& name, std::size_t size) = 0;
   virtual void change_vec_values(const std::string& name, std::vector<std::pair<std::size_t, Any>>& values) = 0;
   virtual void remove_key(const std::string& name, Any& key) = 0;
   virtual std::unique_ptr<Any> add_key_value(const std::string& name, Any& key, Any& value) = 0;
   virtual bool is_map(const std::string& name) = 0;
   virtual void rebind_by_name(Any* to_change, const std::string& member, std::shared_ptr<Base_object> ref) = 0;
};

std::ostream& operator<<(std::ostream& out, const Delta_mergable& obj);

}

#endif // DELTA_MERGABLE_HPP
