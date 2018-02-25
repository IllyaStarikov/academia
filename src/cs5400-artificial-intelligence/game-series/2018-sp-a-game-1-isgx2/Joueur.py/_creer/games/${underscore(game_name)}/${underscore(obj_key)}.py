<%include file="functions.noCreer" /># ${obj_key}: ${shared['py']['format_description'](obj['description'])}

# DO NOT MODIFY THIS FILE
# Never try to directly create an instance of this class, or modify its member variables.
# Instead, you should only be reading its variables and calling its functions.
<% parent_classes = obj['parentClasses'] %>
% if len(parent_classes) > 0:
% for parent_class in parent_classes:
from games.${underscore(game_name)}.${underscore(parent_class)} import ${parent_class}
% endfor
% else:
<% if obj_key == "Game":
    parent_classes = [ 'BaseGame' ]
else:
    parent_classes = [ 'BaseGameObject' ]
%>from joueur.${underscore(parent_classes[0])} import ${parent_classes[0]}
% endif

% if obj_key == "Game":
# import game objects
% for game_obj_key in sort_dict_keys(game_objs):
from games.${underscore(game_name)}.${underscore(game_obj_key)} import ${game_obj_key}
% endfor

% endif
${merge("# ", "imports", "# you can add additional import(s) here", optional=True)}

class ${obj_key}(${", ".join(parent_classes)}):
    """The class representing the ${obj_key} in the ${game_name} game.

    ${shared['py']['format_description'](obj['description'])}
    """

    def __init__(self):
        """Initializes a ${obj_key} with basic logic as provided by the Creer code generator."""
% for parent_class in reversed(parent_classes):
        ${parent_class}.__init__(self)
% endfor

        # private attributes to hold the properties so they appear read only
% for attr_name in obj['attribute_names']:
<% attr_parms = obj['attributes'][attr_name]
%>        self._${underscore(attr_name)} = ${shared['py']['default'](attr_parms['type'], attr_parms['default'])}
% endfor

% if obj_key == "Game":
        self.name = "${game_name}"

        self._game_object_classes = {<% c = len(game_objs) %>
% for game_obj_key in sort_dict_keys(game_objs):
<% c -= 1
%>            '${game_obj_key}': ${game_obj_key}${',' if c != 0 else ''}
% endfor
        }

% endif
% for attr_name in obj['attribute_names']:
<% attr_parms = obj['attributes'][attr_name]
%>    @property
    def ${underscore(attr_name)}(self):
        """${shared['py']['format_description'](attr_parms['description'])}

        :rtype: ${shared['py']['type'](attr_parms['type'])}
        """
        return self._${underscore(attr_name)}

% endfor
% for function_name in obj['function_names']:
<% function_parms = obj['functions'][function_name]
%>    def ${underscore(function_name)}(self${shared['py']['args'](function_parms['arguments'])}):
        """ ${shared['py']['format_description'](function_parms['description'])}
% if len(function_parms['arguments']) > 0:

        Args:
% for arg_parms in function_parms['arguments']:
            ${underscore(arg_parms['name'])} (${"Optional[" if arg_parms['optional'] else ""}${shared['py']['type'](arg_parms['type'])}${"]" if arg_parms['optional'] else ""}): ${shared['py']['format_description'](arg_parms['description'])}
% endfor
% endif
% if function_parms['returns']:

        Returns:
            ${shared['py']['type'](function_parms['returns']['type'])}: ${shared['py']['format_description'](function_parms['returns']['description'])}
% endif
        """
        return self._run_on_server('${function_name}'${shared['py']['kwargs'](function_parms['argument_names'])})

% endfor
% if 'Tile' in game_objs:
% if 'TiledGame' in game['serverParentClasses']: #// then we need to add some client side utility functions

% if obj_key == 'Game':
    def get_tile_at(self, x, y):
        """Gets the Tile at a specified (x, y) position
        Args:
            x (int): integer between 0 and the mapWidth
            y (int): integer between 0 and the mapHeight
        Returns:
            Tile: the Tile at (x, y) or None if out of bounds
        """
        if x < 0 or y < 0 or x >= self.map_width or y >= self.map_height:
            # out of bounds
            return None

        return self.tiles[x + y * self.mapWidth]
% elif obj_key == 'Tile':
    directions = ["North", "East", "South", "West"]
    """int: The valid directions that tiles can be in, "North", "East", "South", or "West"
    """

    def get_neighbors(self):
        """Gets the neighbors of this Tile
        :rtype list[Tile]
        """
        neighbors = []

        for direction in Tile.directions:
            neighbor = getattr(self, "tile_" + direction.lower())
            if neighbor:
                neighbors.append(neighbor)

        return neighbors

    def is_pathable(self):
        """Checks if a Tile is pathable to units
        Returns:
            bool: True if pathable, False otherwise
        """
${merge("        # ", "is_pathable_builtin", "        return false  # DEVELOPER ADD LOGIC HERE")}

    def has_neighbor(self, tile):
        """Checks if this Tile has a specific neighboring Tile
        Args:
            tile (Tile): tile to check against
        Returns:
            bool: True if the tile is a neighbor of this Tile, False otherwise
        """
        return bool(tile and tile in self.get_neighbors())
% endif
% endif

% endif
${merge("    # ", "functions", "    # if you want to add any client side logic (such as state checking functions) this is where you can add them", optional=True)}
