#ifndef ATTRWRAPPER_HPP
#define ATTRWRAPPER_HPP

#include "rapidjson/document.h"

#include <iostream>
#include <string>
#include <cstdint>
#include <stdexcept>

//wraps numeric and string attributes in template form
namespace attr_wrapper
{
   //define some exceptions
   struct Non_object_error : public std::runtime_error
   {
      using std::runtime_error::runtime_error;
   };

   struct Member_not_found_error : public std::runtime_error
   {
      using std::runtime_error::runtime_error;
   };

   struct Type_error : public std::runtime_error
   {
      using std::runtime_error::runtime_error;
   };

   //returns the location of the name, or throws an error if not present
   inline
   rapidjson::Value::ConstMemberIterator get_loc(const rapidjson::Value& doc,
                                                 const char* name)
   {
      //make sure it is an object too
      if(!doc.IsObject())
      {
         throw Non_object_error("Document is not object.");
      }
      auto itr = doc.FindMember(name);
      if(itr == doc.MemberEnd())
      {
         std::string error = "Member ";
         error += name;
         error += " not found";
         throw Member_not_found_error(error);
      }
      return itr;
   }
   //generate type error
   //not that a space is present to allow for for an
   inline Type_error genTypeError(const std::string& name,
                                  const std::string& type)
   {
      std::string toReturn = name;
      toReturn += " is not a" + type;
      return Type_error(toReturn);
   }

   //wrapper that throws errors and has templates and stuff
   template<typename T>
   inline T get_attribute(const rapidjson::Value& doc, const char* name);

   template<>
   inline int get_attribute<int>(const rapidjson::Value& doc,
                                 const char* name)
   {
      auto loc = get_loc(doc, name);
      if(!loc->value.IsInt())
      {
         throw genTypeError(name, "n integer.");
      }
      return loc->value.GetInt();
   }

   template<>
   inline unsigned get_attribute<unsigned>(const rapidjson::Value& doc,
                                           const char* name)
   {
      auto loc = get_loc(doc, name);
      if(!loc->value.IsUint())
      {
         throw genTypeError(name, "n unsigned integer.");
      }
      return loc->value.GetUint();
   }

   template<>
   inline double get_attribute<double>(const rapidjson::Value& doc,
                                       const char* name)
   {
      auto loc = get_loc(doc, name);
      if(!loc->value.IsDouble())
      {
         throw genTypeError(name, " double");
      }
      return loc->value.GetDouble();
   }

   template<>
   inline const char* get_attribute<const char*>(const rapidjson::Value& doc,
                                                 const char* name)
   {
      auto loc = get_loc(doc, name);
      if(!loc->value.IsString())
      {
         throw genTypeError(name, " string");
      }
      return loc->value.GetString();
   }

   template<>
   inline std::string get_attribute<std::string>(const rapidjson::Value& doc,
                                                 const char* name)
   {
      auto loc = get_loc(doc, name);
      if(!loc->value.IsString())
      {
         throw genTypeError(name, " string");
      }
      return std::string(loc->value.GetString(), loc->value.GetStringLength());
   }

   template<>
   inline bool get_attribute<bool>(const rapidjson::Value& doc,
                                   const char* name)
   {
      auto loc = get_loc(doc, name);
      if(!loc->value.IsBool())
      {
         throw genTypeError(name, " boolean");
      }
      return loc->value.GetBool();
   }

   template<typename T>
   inline T as(const rapidjson::Value& doc);

   template<>
   inline uint64_t as(const rapidjson::Value& doc)
   {
      return doc.GetUint64();
   }

   template<>
   inline int64_t as(const rapidjson::Value& doc)
   {
      return doc.GetInt64();
   }

   template<>
   inline int as(const rapidjson::Value& doc)
   {
      return doc.GetInt();
   }

   template<>
   inline unsigned as(const rapidjson::Value& doc)
   {
      return doc.GetUint();
   }

   template<>
   inline bool as(const rapidjson::Value& doc)
   {
      return doc.GetBool();
   }

   template<>
   inline double as(const rapidjson::Value& doc)
   {
      return doc.GetDouble();
   }

   template<>
   inline std::string as(const rapidjson::Value& doc)
   {
      return doc.GetString();
   }

   //extra helpers
   template<typename T>
   inline std::string json_val(const T& val)
   {
      return std::to_string(val);
   }

   inline std::string json_val(bool b)
   {
      return (b ? "true" : "false");
   }

   inline std::string json_val(const std::string& str)
   {
      return "\"" + str + "\"";
   }

   inline std::string json_val(const char* str)
   {
      return "\"" + std::string(str) + "\"";
   }
}

#endif // ATTRWRAPPER_HPP
