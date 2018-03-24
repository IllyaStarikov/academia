#ifndef BASE_OBJECT_HPP
#define BASE_OBJECT_HPP

#include <vector>
#include <string>
#include <unordered_map>
#include <initializer_list>
#include <utility>
#include <iostream>
#include <typeindex>

#include "sgr.hpp"
#include "delta_mergable.hpp"
#include "base_game.hpp"

namespace cpp_client
{

class Base_object : public Delta_mergable
{
public:
   Base_object(std::initializer_list<std::pair<std::string, Any&&>> init);
   virtual ~Base_object();
   Base_object() noexcept;

   /// <summary>
   /// Dynamically casts this object to another type.  Returns nullptr if it cannot be converted
   /// to the type.
   /// </summary>
   /// <returns>A pointer to the desired type, or nullptr if it could not be converted</returns>
   template<typename T>
   std::shared_ptr<typename T::element_type> as()
   {
      auto& self = get_game()->get_objects()[get_id()];
      return std::dynamic_pointer_cast<typename T::element_type>(self);
   }

   /// <summary>
   /// Determines if this object is of the specified object type
   /// </summary>
   /// <returns>true if the object is the object type, false otherwise</returns>
   template<typename T>
   bool is()
   {
      return (this->as<T>() != nullptr);
   }

   //Don't really like doing this, but I can't think of a better way
   /// \cond FALSE
   virtual void resize(const std::string& name, std::size_t size) override {}
   virtual void change_vec_values(const std::string& name,
                                  std::vector<std::pair<std::size_t, Any>>& values) override {}
   virtual void remove_key(const std::string& name, Any& key) override {}
   virtual std::unique_ptr<Any>
      add_key_value(const std::string& name, Any& key, Any& value) override;
   virtual bool is_map(const std::string& name) override { return false; }
   virtual Base_game* get_game() { return nullptr; }
   virtual void rebind_by_name(Any* to_change, const std::string& member, std::shared_ptr<Base_object> ref) override {}
   /// \endcond

private:

   const std::string& get_id() const noexcept;
};

} // cpp_client

#endif // BASE_OBJECT_HPP
