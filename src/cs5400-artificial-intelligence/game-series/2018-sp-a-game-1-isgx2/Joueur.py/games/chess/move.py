# Move: Contains all details about a Piece's move in the game.

# DO NOT MODIFY THIS FILE
# Never try to directly create an instance of this class, or modify its member variables.
# Instead, you should only be reading its variables and calling its functions.

from games.chess.game_object import GameObject

# <<-- Creer-Merge: imports -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
# you can add additional import(s) here
# <<-- /Creer-Merge: imports -->>

class Move(GameObject):
    """The class representing the Move in the Chess game.

    Contains all details about a Piece's move in the game.
    """

    def __init__(self):
        """Initializes a Move with basic logic as provided by the Creer code generator."""
        GameObject.__init__(self)

        # private attributes to hold the properties so they appear read only
        self._captured = None
        self._from_file = ""
        self._from_rank = 0
        self._piece = None
        self._promotion = ""
        self._san = ""
        self._to_file = ""
        self._to_rank = 0

    @property
    def captured(self):
        """The Piece captured by this Move, None if no capture.

        :rtype: Piece
        """
        return self._captured

    @property
    def from_file(self):
        """The file the Piece moved from.

        :rtype: str
        """
        return self._from_file

    @property
    def from_rank(self):
        """The rank the Piece moved from.

        :rtype: int
        """
        return self._from_rank

    @property
    def piece(self):
        """The Piece that was moved.

        :rtype: Piece
        """
        return self._piece

    @property
    def promotion(self):
        """The Piece type this Move's Piece was promoted to from a Pawn, empty string if no promotion occurred.

        :rtype: str
        """
        return self._promotion

    @property
    def san(self):
        """The standard algebraic notation (SAN) representation of the move.

        :rtype: str
        """
        return self._san

    @property
    def to_file(self):
        """The file the Piece moved to.

        :rtype: str
        """
        return self._to_file

    @property
    def to_rank(self):
        """The rank the Piece moved to.

        :rtype: int
        """
        return self._to_rank

    # <<-- Creer-Merge: functions -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    # if you want to add any client side logic (such as state checking functions) this is where you can add them
    # <<-- /Creer-Merge: functions -->>
