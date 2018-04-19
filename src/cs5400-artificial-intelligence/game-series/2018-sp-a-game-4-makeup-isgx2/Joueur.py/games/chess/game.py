# Game: The traditional 8x8 chess board with pieces.

# DO NOT MODIFY THIS FILE
# Never try to directly create an instance of this class, or modify its member variables.
# Instead, you should only be reading its variables and calling its functions.

from joueur.base_game import BaseGame

# import game objects
from games.chess.game_object import GameObject
from games.chess.move import Move
from games.chess.piece import Piece
from games.chess.player import Player


class Game(BaseGame):
    """The class representing the Game in the Chess game.

    The traditional 8x8 chess board with pieces.
    """

    def __init__(self):
        """Initializes a Game with basic logic as provided by the Creer code generator."""
        BaseGame.__init__(self)

        # private attributes to hold the properties so they appear read only
        self._current_player = None
        self._current_turn = 0
        self._fen = ""
        self._game_objects = {}
        self._max_turns = 100
        self._moves = []
        self._pieces = []
        self._players = []
        self._session = ""
        self._turns_to_draw = 0

        self.name = "Chess"

        self._game_object_classes = {
            'GameObject': GameObject,
            'Move': Move,
            'Piece': Piece,
            'Player': Player
        }

    @property
    def current_player(self):
        """The player whose turn it is currently. That player can send commands. Other players cannot.

        :rtype: Player
        """
        return self._current_player

    @property
    def current_turn(self):
        """The current turn number, starting at 0 for the first player's turn.

        :rtype: int
        """
        return self._current_turn

    @property
    def fen(self):
        """Forsyth–Edwards Notation, a notation that describes the game board.

        :rtype: str
        """
        return self._fen

    @property
    def game_objects(self):
        """A mapping of every game object's ID to the actual game object. Primarily used by the server and client to easily refer to the game objects via ID.

        :rtype: dict[str, GameObject]
        """
        return self._game_objects

    @property
    def max_turns(self):
        """The maximum number of turns before the game will automatically end.

        :rtype: int
        """
        return self._max_turns

    @property
    def moves(self):
        """The list of Moves that have occurred, in order.

        :rtype: list[Move]
        """
        return self._moves

    @property
    def pieces(self):
        """All the uncaptured Pieces in the game.

        :rtype: list[Piece]
        """
        return self._pieces

    @property
    def players(self):
        """List of all the players in the game.

        :rtype: list[Player]
        """
        return self._players

    @property
    def session(self):
        """A unique identifier for the game instance that is being played.

        :rtype: str
        """
        return self._session

    @property
    def turns_to_draw(self):
        """How many turns until the game ends because no pawn has moved and no Piece has been taken.

        :rtype: int
        """
        return self._turns_to_draw
