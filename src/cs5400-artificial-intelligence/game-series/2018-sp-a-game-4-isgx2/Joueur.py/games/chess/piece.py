# Piece: A chess piece.

# DO NOT MODIFY THIS FILE
# Never try to directly create an instance of this class, or modify its member variables.
# Instead, you should only be reading its variables and calling its functions.

from games.chess.game_object import GameObject

# <<-- Creer-Merge: imports -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
# you can add additional import(s) here
# <<-- /Creer-Merge: imports -->>

class Piece(GameObject):
    """The class representing the Piece in the Chess game.

    A chess piece.
    """

    def __init__(self):
        """Initializes a Piece with basic logic as provided by the Creer code generator."""
        GameObject.__init__(self)

        # private attributes to hold the properties so they appear read only
        self._captured = False
        self._file = ""
        self._has_moved = False
        self._owner = None
        self._rank = 0
        self._type = ""

    @property
    def captured(self):
        """When the Piece has been captured (removed from the board) this is True. Otherwise False.

        :rtype: bool
        """
        return self._captured

    @property
    def file(self):
        """The file (column) coordinate of the Piece represented as a letter [a-h], with 'a' starting at the left of the board.

        :rtype: str
        """
        return self._file

    @property
    def has_moved(self):
        """If the Piece has moved from its starting position.

        :rtype: bool
        """
        return self._has_moved

    @property
    def owner(self):
        """The player that controls this chess Piece.

        :rtype: Player
        """
        return self._owner

    @property
    def rank(self):
        """The rank (row) coordinate of the Piece represented as a number [1-8], with 1 starting at the bottom of the board.

        :rtype: int
        """
        return self._rank

    @property
    def type(self):
        """The type of chess Piece this is, either: 'King', 'Queen', 'Knight', 'Rook', 'Bishop', or 'Pawn'.

        :rtype: str
        """
        return self._type

    def move(self, file, rank, promotionType=""):
        """ Moves the Piece from its current location to the given rank and file.

        Args:
            file (str): The file coordinate to move to. Must be [a-h].
            rank (int): The rank coordinate to move to. Must be [1-8].
            promotion_type (Optional[str]): If this is a Pawn moving to the end of the board then this parameter is what to promote it to. When used must be 'Queen', 'Knight', 'Rook', or 'Bishop'.

        Returns:
            Move: The Move you did if successful, otherwise None if invalid. In addition if your move was invalid you will lose.
        """
        return self._run_on_server('move', file=file, rank=rank, promotionType=promotionType)
