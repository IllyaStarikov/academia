#ifndef DELTA_HPP
#define DELTA_HPP

#include "rapidjson/document.h"
#include "any.hpp"
#include "exceptions.hpp"

namespace cpp_client
{

class Base_game;

//apply a delta to an object
void apply_delta(rapidjson::Value& delta, Base_game& apply_to);

//create an any from a json value
void morph_any(Any& to_morph, const rapidjson::Value& val);


} // cpp_client

#endif // DELTA_HPP
