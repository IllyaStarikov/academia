# GameObject: An object in the game. The most basic class that all game classes should inherit from automatically.

# DO NOT MODIFY THIS FILE
# Never try to directly create an instance of this class, or modify its member variables.
# Instead, you should only be reading its variables and calling its functions.

from joueur.base_game_object import BaseGameObject

# <<-- Creer-Merge: imports -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
# you can add additional import(s) here
# <<-- /Creer-Merge: imports -->>

class GameObject(BaseGameObject):
    """The class representing the GameObject in the Chess game.

    An object in the game. The most basic class that all game classes should inherit from automatically.
    """

    def __init__(self):
        """Initializes a GameObject with basic logic as provided by the Creer code generator."""
        BaseGameObject.__init__(self)

        # private attributes to hold the properties so they appear read only
        self._game_object_name = ""
        self._id = ""
        self._logs = []

    @property
    def game_object_name(self):
        """String representing the top level Class that this game object is an instance of. Used for reflection to create new instances on clients, but exposed for convenience should AIs want this data.

        :rtype: str
        """
        return self._game_object_name

    @property
    def id(self):
        """A unique id for each instance of a GameObject or a sub class. Used for client and server communication. Should never change value after being set.

        :rtype: str
        """
        return self._id

    @property
    def logs(self):
        """Any strings logged will be stored here. Intended for debugging.

        :rtype: list[str]
        """
        return self._logs

    def log(self, message):
        """ Adds a message to this GameObject's logs. Intended for your own debugging purposes, as strings stored here are saved in the gamelog.

        Args:
            message (str): A string to add to this GameObject's log. Intended for debugging.
        """
        return self._run_on_server('log', message=message)

    # <<-- Creer-Merge: functions -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    # if you want to add any client side logic (such as state checking functions) this is where you can add them
    # <<-- /Creer-Merge: functions -->>
