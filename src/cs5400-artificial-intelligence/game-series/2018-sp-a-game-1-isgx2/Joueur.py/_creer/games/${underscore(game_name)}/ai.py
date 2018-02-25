# This is where you build your AI for the ${game_name} game.
<%include file="functions.noCreer" />
from joueur.base_ai import BaseAI

${merge("# ", "imports", "# you can add additional import(s) here", optional=True)}

class AI(BaseAI):
    """ The basic AI functions that are the same between games. """

    def get_name(self):
        """ This is the name you send to the server so your AI will control the player named this string.

        Returns
            str: The name of your Player.
        """
${merge("        # ", "get-name", '        return "' + game_name + ' Python Player" # REPLACE THIS WITH YOUR TEAM NAME')}

    def start(self):
        """ This is called once the game starts and your AI knows its playerID and game. You can initialize your AI here.
        """
${merge("        # ", "start", "        # replace with your start logic")}

    def game_updated(self):
        """ This is called every time the game's state updates, so if you are tracking anything you can update it here.
        """
${merge("        # ", "game-updated", "        # replace with your game updated logic")}

    def end(self, won, reason):
        """ This is called when the game ends, you can clean up your data and dump files here if need be.

        Args:
            won (bool): True means you won, False means you lost.
            reason (str): The human readable string explaining why you won or lost.
        """
${merge("        # ", "end", "        # replace with your end logic")}
% for function_name in ai['function_names']:
<% function_parms = ai['functions'][function_name]
%>    def ${underscore(function_name)}(self${", ".join([""] + function_parms['argument_names'])}):
        """ ${shared['py']['format_description'](function_parms['description'])}
% if len(function_parms['arguments']) > 0:

        Args:
% for arg_parms in function_parms['arguments']:
            ${underscore(arg_parms['name'])} (${shared['py']['type'](arg_parms['type'])}): ${shared['py']['format_description'](arg_parms['description'])}
% endfor
% endif
% if function_parms['returns']:

        Returns:
            ${shared['py']['type'](function_parms['returns']['type'])}: ${shared['py']['format_description'](function_parms['returns']['description'])}
% endif
        """
${merge("        # ", function_name,
"""        # Put your game logic here for {0}
        return {1}
""".format(function_name, shared['py']['default'](function_parms['returns']['type'], function_parms['returns']['default']) if function_parms['returns'] else "")
)}
% endfor

% if 'TiledGame' in game['serverParentClasses']: #// then we need to add some client side utility functions
    def find_path(self, start, goal):
        """A very basic path finding algorithm (Breadth First Search) that when given a starting Tile, will return a valid path to the goal Tile.
        Args:
            start (Tile): the starting Tile
            goal (Tile): the goal Tile
        Returns:
            list[Tile]: A list of Tiles representing the path, the the first element being a valid adjacent Tile to the start, and the last element being the goal.
        """

        if start == goal:
            # no need to make a path to here...
            return []

        # queue of the tiles that will have their neighbors searched for 'goal'
        fringe = []

        # How we got to each tile that went into the fringe.
        came_from = {}

        # Enqueue start as the first tile to have its neighbors searched.
        fringe.append(start)

        # keep exploring neighbors of neighbors... until there are no more.
        while len(fringe) > 0:
            # the tile we are currently exploring.
            inspect = fringe.pop(0)

            # cycle through the tile's neighbors.
            for neighbor in inspect.get_neighbors():
                # if we found the goal, we have the path!
                if neighbor == goal:
                    # Follow the path backward to the start from the goal and return it.
                    path = [goal]

                    # Starting at the tile we are currently at, insert them retracing our steps till we get to the starting tile
                    while inspect != start:
                        path.insert(0, inspect)
                        inspect = came_from[inspect.id]
                    return path
                # else we did not find the goal, so enqueue this tile's neighbors to be inspected

                # if the tile exists, has not been explored or added to the fringe yet, and it is pathable
                if neighbor and neighbor.id not in came_from and neighbor.is_pathable():
                    # add it to the tiles to be explored and add where it came from for path reconstruction.
                    fringe.append(neighbor)
                    came_from[neighbor.id] = inspect

        # if you're here, that means that there was not a path to get to where you want to go.
        #   in that case, we'll just return an empty path.
        return []

% endif
${merge("    # ", "functions", "    # if you need additional functions for your AI you can add them here", optional=True)}
