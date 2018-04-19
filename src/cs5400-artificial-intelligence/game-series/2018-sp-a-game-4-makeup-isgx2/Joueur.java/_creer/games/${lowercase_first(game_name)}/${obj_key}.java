/**
 * ${obj['description']}
 */

// DO NOT MODIFY THIS FILE
// Never try to directly create an instance of this class, or modify its member variables.
// Instead, you should only be reading its variables and calling its functions.

package games.${lowercase_first(game_name)};
<%include file="functions.noCreer" />
import java.util.List;
import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import org.json.JSONObject;
import joueur.Client;
import joueur.BaseGame;
import joueur.BaseGameObject;

${merge("// ", "imports", "// you can add additional import(s) here", optional=True)}
<%parent_classes = list(obj['parentClasses'])

if not parent_classes:
    if obj_key == "Game":
        parent_classes = [ "BaseGame" ]
    else:
        parent_classes = [ "BaseGameObject" ]
else:
    for i in range(len(parent_classes)):
        parent_classes[i] = parent_classes[i]

inherit_str = ", ".join(parent_classes) # note: this could have multi-inheritance, which java does not support. Will need to make some sore of Interface system in the future, or combine all multi-inheritied features into one for java

%>
/**
 * ${obj['description']}
 */
public class ${obj_key} extends ${inherit_str} {
% for attr_name in obj['attribute_names']:
<% attr_parms = obj['attributes'][attr_name]
if (obj_key == "Game" and (attr_name == "gameObjects" or attr_name == "name")) or attr_name == "id" or attr_name == "gameObjectName":
    continue
%>    /**
     * ${attr_parms['description']}
     */
    public ${shared['java']['type'](attr_parms['type'])} ${attr_name};

% endfor

${merge("    // ", "fields", "    // you can add additional field(s) here. None of them will be tracked or updated by the server.", optional=True)}


    /**
     * Creates a new instance of a ${obj_key}. Used during game initialization, do not call directly.
     */
    protected ${obj_key}() {
        super();
% if obj_key == "Game":
        this.name = "${game_name}";

% endif
% for attr_name in obj['attribute_names']:
% if obj['attributes'][attr_name]['type']['name'] == "list" or obj['attributes'][attr_name]['type']['name'] == "dictionary":
% if obj_key != "Game" or attr_name != "gameObjects": # special case where the value needs to be BaseGameObject, not GameObject as the prototype claims
        this.${attr_name} = ${shared['java']['default'](obj['attributes'][attr_name]['type'], obj['attributes'][attr_name]['default'])};
% endif
% endif
% endfor
    }
% for function_name in obj['function_names']:
<%
function_parms = obj['functions'][function_name]
arg_strings = []
arg_names = []
all_types = []
return_type = shared['java']['type'](function_parms['returns']['type']) if function_parms['returns'] else None
if function_parms['returns']:
    shared['java']['type'](function_parms['returns']['type'])

if 'arguments' in function_parms:
    for i, arg_parms in enumerate(function_parms['arguments']):
        ty = shared['java']['type'](arg_parms['type'])
        all_types.append(ty)
        if arg_parms['optional']:
            continue
        else:
            arg_strings.append(ty + " " + arg_parms['name'])
            arg_names.append(arg_parms['name'])
%>
% if "optionals" in function_parms: # then we need to make some overloaded function with optional args omitted
% for optional_arg_parms in function_parms['arguments'][function_parms['optionals_start_index']:]:
<%
    optional_arg_names = list(arg_names)
    def_val = shared['java']['value'](optional_arg_parms['type'], optional_arg_parms['default'])
    optional_arg_names.append(def_val)
%>    /**
     * Defaults the value for the optional arg '${optional_arg_parms['name']}' to '${def_val}'
     *
     * @see ${obj_key}#${function_name}(${", ".join(all_types)})
     */
    public ${return_type or 'void'} ${function_name}(${", ".join(arg_strings)}) {
        ${"return " if function_parms['returns'] else ""}this.${function_name}(${", ".join(optional_arg_names)});
    }
<%
    arg_strings.append(shared['java']['type'](optional_arg_parms['type']) + " " + optional_arg_parms['name'])
    arg_names.append(optional_arg_parms['name'])
%>
% endfor
% endif
    /**
     * ${function_parms['description']}<% a = "*/ this is to appease the syntax highlighter\"" %>
% if 'arguments' in function_parms:
     *
% for arg_parms in function_parms['arguments']:
     * @param   ${arg_parms['name']}  ${arg_parms['description']}
% endfor
% endif
% if function_parms['returns']:
% if 'arguments' not in function_parms:
     *
% endif
     * @return ${function_parms['returns']['description']}
% endif
     */
    public ${return_type or 'void'} ${function_name}(${", ".join(arg_strings)}) {
        JSONObject args = new JSONObject();
% for i, arg_parms in enumerate(function_parms['arguments']):
        args.put("${arg_parms['name']}", Client.getInstance().gameManager.serializeSafe(${arg_parms['name']}));
% endfor
        ${"return " if function_parms['returns'] else ""}${('(' + return_type + ')') if return_type else ''}this.runOnServer("${function_name}", args);
    }
% endfor

% if 'Tile' in game_objs:
% if 'TiledGame' in game['serverParentClasses']: #// then we need to add some client side utility functions
% if obj_key == 'Game':
    /**
     * Gets the Tile at a specified (x, y) position
     * @param  x  integer between 0 and the mapWidth
     * @param  y  integer between 0 and the mapHeight
     * @return the Tile at (x, y) or null if out of bounds
     */
    public Tile getTileAt(int x, int y)
    {
        if (x < 0 || y < 0 || x >= this.mapWidth || y >= this.mapHeight) {
            // out of bounds
            return null;
        }

        return this.tiles.get(x + y * this.mapWidth);
    }
% elif obj_key == 'Tile':
    /**
     * Gets the neighbors of this Tile
     * @return The neighboring (adjacent) Tiles to this tile
     */
    public List<Tile> getNeighbors() {
        List<Tile> list = new ArrayList<Tile>();

        if (this.tileNorth != null) {
            list.add(this.tileNorth);
        }

        if (this.tileEast != null) {
            list.add(this.tileEast);
        }

        if (this.tileSouth != null) {
            list.add(this.tileSouth);
        }

        if (this.tileWest != null) {
            list.add(this.tileWest);
        }

        return list;
    }

    /**
     * Checks if a Tile is pathable to units
     * @return True if pathable, false otherwise
     */
    public boolean isPathable() {
${merge("        // ", "is_pathable_builtin", "        return false; // DEVELOPER ADD LOGIC HERE")}
    }

    /**
     * Checks if this Tile has a specific neighboring Tile
     * @param  tile  Tile to check against
     * @return true if the tile is a neighbor of this Tile, false otherwise
     */
    public boolean hasNeighbor(Tile tile) {
        if (tile == null) {
            return false;
        }

        return (this.tileNorth == tile || this.tileEast == tile || this.tileSouth == tile || this.tileEast == tile);
    }

% endif
% endif

% endif
${merge("    // ", "methods", "    // you can add additional method(s) here.", optional=True)}
}
