// DO NOT MODIFY THIS FILE
// Never try to directly create an instance of this class, or modify its member variables.
// This contains implementation details, written by code, and only useful to code
<% obj_key_name = underscore(obj_key).capitalize() %>
<%include file="functions.noCreer" />
#include "../${underscore(obj_key)}.hpp"
#include "../../../joueur/src/base_ai.hpp"
#include "../../../joueur/src/any.hpp"
#include "../../../joueur/src/exceptions.hpp"
#include "../../../joueur/src/delta.hpp"
% for game_obj_key in sort_dict_keys(game_objs):
#include "../${underscore(game_obj_key)}.hpp"
% endfor
#include "${underscore(game_name)}.hpp"

#include <type_traits>

namespace cpp_client
{

namespace ${underscore(game_name)}
{
% for function_name in obj['function_names']:
<% function_params = obj['functions'][function_name]
if function_params['returns']:
  return_type = shared['gen_base_type'](function_params['returns']['type'])
else:
  return_type = 'void'
name = underscore(function_name)
args = shared['make_args'](function_params, False)
%>
${return_type} ${obj_key_name}_::${name}(${args})
{
    std::string order = R"({"event": "run", "data": {"functionName": "${function_name}", "caller": {"id": ")";
    order += this->id + R"("}, "args": {)";
<% comma = '' %>
% for arg_params in function_params['arguments']:
    order += std::string("${comma}\"${arg_params['name']}\":") + ${shared['make_string_arg'](arg_params)};
<% comma = ',' %>
% endfor
    order += "}}}";
    ${underscore(game_name).capitalize()}::instance()->send(order);
    //Go until not a delta
    std::unique_ptr<Any> info;
    //until a not bool is seen (i.e., the delta has been processed)
    do
    {
        info = ${underscore(game_name).capitalize()}::instance()->handle_response();
    } while(info->type() == typeid(bool));
% if return_type == 'void':
    return;
% elif shared['is_ref'](return_type):
    //reference - just pull the id
    auto doc = info->as<rapidjson::Document*>();
    auto loc = doc->FindMember("data");
    if(loc == doc->MemberEnd())
    {
        return nullptr;
    }
    auto& val = loc->value;
    if(val.IsNull())
    {
        return nullptr;
    }
    else
    {
        auto target = attr_wrapper::get_attribute<std::string>(val, "id");
        return std::dynamic_pointer_cast<${return_type}_>(${underscore(game_name).capitalize()}::instance()->get_objects()[target]);
    }
% else:
    auto doc = info->as<rapidjson::Document*>();
    auto loc = doc->FindMember("data");
    if(loc == doc->MemberEnd())
    {
       return {};
    }
    auto& val = loc->value;
    Any to_return;
    morph_any(to_return, val);
    return to_return.as<${return_type}>();
% endif
}
% endfor

<%
parent_classes = []
for par in obj['parentClasses']:
    parent_classes.append(underscore(par).capitalize() + '_')
call_parents = True
if obj_key == "Game":
    parent_classes = [ 'Base_game' ]
    call_parents = False
elif obj_key == "GameObject":
    parent_classes = [ 'Base_object' ]
    call_parents = False
i = len(obj['attribute_names']) - 1
comma = ','
initcomma = ','
if i == -1:
    initcomma = ''
if i == 0:
    comma = ''%>
${obj_key_name}_::${obj_key_name}_(std::initializer_list<std::pair<std::string, Any&&>> init) :
% for par in parent_classes:
    ${underscore(par).capitalize()}{
% for attr_name in obj['attribute_names']:
        {"${attr_name}", Any{std::decay<decltype(${underscore(attr_name)})>::type{}}},
% endfor
    }${initcomma}
% endfor
% for attr_name in obj['attribute_names']:
    ${underscore(attr_name)}(variables_["${attr_name}"].as<std::decay<decltype(${underscore(attr_name)})>::type>())${comma}<% i -=1
 if i == 0:
     comma = ''%>
% endfor
{
    for(auto&& obj : init)
    {
      variables_.emplace(std::make_pair(std::move(obj.first), std::move(obj.second)));
    }
}

${obj_key_name}_::~${obj_key_name}_() = default;

void ${obj_key_name}_::resize(const std::string& name, std::size_t size)
{<% if_str = 'if' %>
% for attr_name in obj['attribute_names']:
% if obj['attributes'][attr_name]['type'] and obj['attributes'][attr_name]['type']['name'] == 'list':
    ${if_str}(name == "${attr_name}")
    {
        auto& vec = variables_["${attr_name}"].as<std::decay<decltype(${underscore(attr_name)})>::type>();
        vec.resize(size);
        return;
    }<% if_str = 'else if' %>
% endif
% endfor
% if call_parents:
% for parent in parent_classes:
    try
    {
        ${underscore(par).capitalize()}::resize(name, size);
        return;
    }
    catch(...){}
% endfor
% endif
    throw Bad_manipulation(name + " in ${obj_key_name} treated as a vector, but it is not a vector.");
}

void ${obj_key_name}_::change_vec_values(const std::string& name, std::vector<std::pair<std::size_t, Any>>& values)
{<% if_str = 'if' %>
% for attr_name in obj['attribute_names']:
% if obj['attributes'][attr_name]['type'] and obj['attributes'][attr_name]['type']['name'] == 'list':
    ${if_str}(name == "${attr_name}")
    {
        using type = std::decay<decltype(${underscore(attr_name)})>::type;
        auto& vec = variables_["${attr_name}"].as<type>();
        for(auto&& val : values)
        { <% game = "get_game()->" if obj_key_name != "Game" else "" %>
            % if 'valueType' in obj['attributes'][attr_name]['type'] and obj['attributes'][attr_name]['type']['valueType']['is_game_object']:
            vec[val.first] = std::static_pointer_cast<type::value_type::element_type>(${game}get_objects()[val.second.as<std::string>()]);
            % else:
            vec[val.first] = std::move(val.second.as<type::value_type>());
            % endif
        }
        return;
    } <% if_str = 'else if' %>
% endif
% endfor
% if call_parents:
% for parent in parent_classes:
    try
    {
        ${underscore(par).capitalize()}::change_vec_values(name, values);
        return;
    }
    catch(...){}
% endfor
% endif
    throw Bad_manipulation(name + " in ${obj_key_name} treated as a vector, but it is not a vector.");
}

void ${obj_key_name}_::remove_key(const std::string& name, Any& key)
{<% if_str = 'if' %>
% for attr_name in obj['attribute_names']:
% if obj['attributes'][attr_name]['type'] and obj['attributes'][attr_name]['type']['name'] == 'dictionary':
    ${if_str}(name == "${attr_name}")
    {
        auto& map = variables_["${attr_name}"].as<std::decay<decltype(${underscore(attr_name)})>::type>();
        using type = std::decay<decltype(map)>::type;
        map.erase(key.as<type::key_type>());
        return;
    }<% if_str = 'else if' %>
% endif
% endfor
% if call_parents:
% for parent in parent_classes:
    try
    {
        ${underscore(par).capitalize()}::remove_key(name, key);
        return;
    }
    catch(...){}
% endfor
% endif
    throw Bad_manipulation(name + " in ${obj_key_name} treated as a map, but it is not a map.");
}

std::unique_ptr<Any> ${obj_key_name}_::add_key_value(const std::string& name, Any& key, Any& value)
{<% if_str = 'if' %>
% for attr_name in obj['attribute_names']:
% if obj['attributes'][attr_name]['type'] and obj['attributes'][attr_name]['type']['name'] == 'dictionary':
    ${if_str}(name == "${attr_name}")
    {
        auto& map = variables_["${attr_name}"].as<std::decay<decltype(${underscore(attr_name)})>::type>();
        using type = std::decay<decltype(map)>::type;
        auto real_key = key.as<type::key_type>();
        if(value)
        {
            map[real_key] = std::move(value.as<type::mapped_type>());
        }
% if obj['attributes'][attr_name]['type']['valueType'] in ['boolean', 'float', 'int', 'string']:
        return std::unique_ptr<Any>(new Any{map[real_key]});
% else:
        auto val = std::static_pointer_cast<Base_object>(map[real_key]);
        return std::unique_ptr<Any>(new Any{std::shared_ptr<Base_object>{val}});
% endif
    }<% if_str = 'else if' %>
% endif
% endfor
% if call_parents:
% for parent in parent_classes:
    try
    {
        return ${underscore(par).capitalize()}::add_key_value(name, key, value);
    }
    catch(...){}
% endfor
% endif
    throw Bad_manipulation(name + " in ${obj_key_name} treated as a map, but it is not a map.");
}

bool ${obj_key_name}_::is_map(const std::string& name)
{
% for attr_name in obj['attribute_names']:
% if obj['attributes'][attr_name]['type'] and obj['attributes'][attr_name]['type']['name'] == 'dictionary':
    if(name == "${attr_name}")
    {
        return true;
    }
% endif
% endfor
% if call_parents:
% for parent in parent_classes:
    try
    {
        return ${underscore(par).capitalize()}::is_map(name);
    }
    catch(...){}
% endfor
% endif
    return false;
}

void ${obj_key_name}_::rebind_by_name(Any* to_change, const std::string& member, std::shared_ptr<Base_object> ref)
{
   % for attr_name in obj['attribute_names']:
   % if obj['attributes'][attr_name]['type'] and obj['attributes'][attr_name]['type']['is_game_object']:
   if(member == "${attr_name}")
   { <% name = underscore(obj['attributes'][attr_name]['type']['name']).capitalize() %>
      to_change->as<${name}>() = std::static_pointer_cast<${name}_>(ref);
      return;
   }
   % endif
   % endfor
   % if call_parents:
   % for parent in parent_classes:
   try
   {
      ${underscore(par).capitalize()}::rebind_by_name(to_change, member, ref);
      return;
   }
   catch(...){}
   % endfor
   % endif
   throw Bad_manipulation(member + " in ${obj_key_name} treated as a reference, but it is not a reference.");
}

% if obj_key_name == 'Game_object':
    Base_game* ${obj_key_name}_::get_game() { return ${underscore(game_name).capitalize()}::instance(); }
% endif

} // ${underscore(game_name)}

} // cpp_client
