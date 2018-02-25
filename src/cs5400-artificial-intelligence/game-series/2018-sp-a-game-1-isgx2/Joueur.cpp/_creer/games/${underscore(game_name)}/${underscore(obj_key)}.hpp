#ifndef GAMES_${game_name.upper()}_${underscore(obj_key).upper()}_H
#define GAMES_${game_name.upper()}_${underscore(obj_key).upper()}_H

// ${obj_key}
// ${obj['description']}

// DO NOT MODIFY THIS FILE
// Never try to directly create an instance of this class, or modify its member variables.
// Instead, you should only be reading its variables and calling its functions.

#include <vector>
#include <queue>
#include <deque>
#include <unordered_map>
#include <string>
#include <initializer_list>

#include "../../joueur/src/any.hpp"
<%include file="impl/functions.noCreer" />
<% obj_key_name = underscore(obj_key).capitalize()
parent_classes = []
for par in obj['parentClasses']:
    parent_classes.append(underscore(par).capitalize() + '_')
%>
% if len(parent_classes) > 0:
%     for parent_class in parent_classes:
#include "${underscore(parent_class)[:-1]}.hpp"
%     endfor
% endif
<%
mod = False
if obj_key == "Game":
    mod = True
    parent_classes = [ 'Base_game' ]
elif obj_key == "GameObject":
    mod = True
    parent_classes = [ 'Base_object' ]
%>
% if mod:
#include "../../joueur/src/${underscore(parent_classes[0])}.hpp"
% endif
#include "impl/${underscore(game_name)}_fwd.hpp"

${merge("// ", "includes", "// you can add additional #includes here")}

namespace cpp_client
{

namespace ${underscore(game_name)}
{

/// <summary>
/// ${obj['description']}
/// </summary>
class ${obj_key_name}_ : public ${(", public ").join(parent_classes)}
{
public:
% for attr_name in obj['attribute_names']:
<% attr_params = obj['attributes'][attr_name] %>
    /// <summary>
    /// ${attr_params['description']}
    /// </summary>
    ${shared['gen_base_type2'](attr_params['type'])} ${underscore(attr_name)};
% endfor

${merge("    // ", "member variables", "    // You can add additional member variables here. None of them will be tracked or updated by the server.")}

% for function_name in obj['function_names']:
<% function_params = obj['functions'][function_name] %>
    /// <summary>
    /// ${underscore(function_params['description'])}
    /// </summary>
% if 'arguments' in function_params:
% for arg_params in function_params['arguments']:
    /// <param name="${underscore(arg_params['name'])}"> ${arg_params['description']} </param>
% endfor
<%
if function_params['returns']:
  return_type = shared['gen_base_type'](function_params['returns']['type'])
else:
  return_type = 'void'
name = underscore(function_name)
args = shared['make_args'](function_params, True)
%>    ${return_type} ${name}(${args});
% endif
% endfor

% if game['serverParentClasses']: #// then we need to add some client side utility functions
% if obj_key == 'Game':
% if 'Tile' in game_objs:
    /// <summary>
    /// Gets the Tile at a specified (x, y) position
    /// </summary>
    /// <param name="x">integer between 0 and the mapWidth</param>
    /// <param name="y">integer between 0 and the mapHeight</param>
    /// <returns>the Tile at (x, y) or null if out of bounds
    Tile get_tile_at(const int x, const int y);
% endif
% elif obj_key == 'Tile':
    /// <summary>
    /// The list of all valid directions Tiles can be in
    /// </summary>
    static const std::vector<std::string> directions;

    /// <summary>
    /// Gets the neighbors of this Tile
    /// </summary>
    /// <returns>The neighboring (adjacent) Tiles to this tile</returns>
    std::vector<Tile> get_neighbors();

    /// <summary>
    /// Checks if a Tile is pathable to units
    /// </summary>
    /// <return>true if pathable, false otherwise</return>
    bool is_pathable();

    /// <summary>
    /// Checks if this Tile has a specific neighboring Tile
    /// </summary>
    /// <param name="tile">Tile to check against</param>
    /// <return>if the tile is a neighbor of this Tile, false otherwise</return>
    bool has_neighbor(const Tile& tile);
% endif

% endif
${merge("   // ", "methods", "   // You can add additional methods here.")}

   ~${obj_key_name}_();

   // ####################
   // Don't edit these!
   // ####################
   /// \cond FALSE
   ${obj_key_name}_(std::initializer_list<std::pair<std::string, Any&&>> init);
   ${obj_key_name}_() : ${obj_key_name}_({}){}
   virtual void resize(const std::string& name, std::size_t size) override;
   virtual void change_vec_values(const std::string& name, std::vector<std::pair<std::size_t, Any>>& values) override;
   virtual void remove_key(const std::string& name, Any& key) override;
   virtual std::unique_ptr<Any> add_key_value(const std::string& name, Any& key, Any& value) override;
   virtual bool is_map(const std::string& name) override;
   virtual void rebind_by_name(Any* to_change, const std::string& member, std::shared_ptr<Base_object> ref) override;
% if obj_key_name == 'Game_object':
    virtual Base_game* get_game() override;
% endif
    /// \endcond
    // ####################
    // Don't edit these!
    // ####################
};

} // ${lowercase_first(game_name)}

} // cpp_client

#endif // GAMES_${game_name.upper()}_${underscore(obj_key).upper()}_H
