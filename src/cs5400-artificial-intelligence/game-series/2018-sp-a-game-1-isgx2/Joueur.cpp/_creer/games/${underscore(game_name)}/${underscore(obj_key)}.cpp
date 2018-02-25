// ${obj_key}
// ${obj['description']}

// DO NOT MODIFY THIS FILE
// Never try to directly create an instance of this class, or modify its member variables.
// Instead, you should only be reading its variables and calling its functions.
<% obj_key_name = underscore(obj_key).capitalize() %>
<%include file="impl/functions.noCreer" />
#include "${underscore(obj_key)}.hpp"
#include "../../joueur/src/base_ai.hpp"
#include "../../joueur/src/any.hpp"
#include "../../joueur/src/exceptions.hpp"
#include "../../joueur/src/delta.hpp"
% for game_obj_key in sort_dict_keys(game_objs):
#include "${underscore(game_obj_key)}.hpp"
% endfor
#include "impl/${underscore(game_name)}.hpp"

#include <type_traits>

namespace cpp_client
{

namespace ${underscore(game_name)}
{

% if 'Tile' in game_objs:
% if 'TiledGame' in game['serverParentClasses']: #// then we need to add some client side utility functions
% if obj_key == 'Game':
/// <summary>
/// Gets the Tile at a specified (x, y) position
/// </summary>
/// <param name="x">integer between 0 and the mapWidth</param>
/// <param name="y">integer between 0 and the mapHeight</param>
/// <returns>the Tile at (x, y) or null if out of bounds
Tile Game_::get_tile_at(const int x, const int y)
{
    if(x < 0 || y < 0 || x >= map_width || y >= map_height) {
        // out of bounds
        return nullptr;
    }

    return tiles[x + y * map_width];
}
% elif obj_key == 'Tile':
const std::vector<std::string> Tile_::directions({"North", "East", "South", "West"});

/// <summary>
/// Gets the neighbors of this Tile
/// </summary>
/// <returns>The neighboring (adjacent) Tiles to this tile</returns>
std::vector<Tile> Tile_::get_neighbors()
{
    std::vector<Tile> neighbors;

    if(tile_north)
    {
        neighbors.push_back(tile_north);
    }

    if(tile_east)
    {
        neighbors.push_back(tile_east);
    }

    if(tile_south)
    {
        neighbors.push_back(tile_south);
    }

    if(tile_west)
    {
        neighbors.push_back(tile_west);
    }

    return neighbors;
}

/// <summary>
/// Checks if a Tile is pathable to units
/// </summary>
/// <return>true if pathable, false otherwise</return>
bool Tile_::is_pathable()
{
${merge("    // ", "is_pathable_builtin", "    return false; // DEVELOPER ADD LOGIC HERE")}
}

/// <summary>
/// Checks if this Tile has a specific neighboring Tile
/// </summary>
/// <param name="tile">Tile to check against</param>
/// <return>if the tile is a neighbor of this Tile, false otherwise</return>
bool Tile_::has_neighbor(const Tile& tile)
{
    return (tile && (tile_north == tile || tile_east == tile || tile_south == tile || tile_west == tile));
}
% endif
% endif
% endif

} // ${underscore(game_name)}

} // cpp_client
