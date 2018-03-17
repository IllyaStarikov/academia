# Player: A player in this game. Every AI controls one player.

# DO NOT MODIFY THIS FILE
# Never try to directly create an instance of this class, or modify its member variables.
# Instead, you should only be reading its variables and calling its functions.

from games.chess.game_object import GameObject


class Player(GameObject):
    """The class representing the Player in the Chess game.

    A player in this game. Every AI controls one player.
    """

    def __init__(self):
        """Initializes a Player with basic logic as provided by the Creer code generator."""
        GameObject.__init__(self)

        # private attributes to hold the properties so they appear read only
        self._client_type = ""
        self._color = ""
        self._in_check = False
        self._lost = False
        self._made_move = False
        self._name = "Anonymous"
        self._opponent = None
        self._pieces = []
        self._rank_direction = 0
        self._reason_lost = ""
        self._reason_won = ""
        self._time_remaining = 0
        self._won = False

    @property
    def client_type(self):
        """What type of client this is, e.g. 'Python', 'JavaScript', or some other language. For potential data mining purposes.

        :rtype: str
        """
        return self._client_type

    @property
    def color(self):
        """The color (side) of this player. Either 'White' or 'Black', with the 'White' player having the first move.

        :rtype: str
        """
        return self._color

    @property
    def in_check(self):
        """True if this player is currently in check, and must move out of check, False otherwise.

        :rtype: bool
        """
        return self._in_check

    @property
    def lost(self):
        """If the player lost the game or not.

        :rtype: bool
        """
        return self._lost

    @property
    def made_move(self):
        """If the Player has made their move for the turn. True means they can no longer move a Piece this turn.

        :rtype: bool
        """
        return self._made_move

    @property
    def name(self):
        """The name of the player.

        :rtype: str
        """
        return self._name

    @property
    def opponent(self):
        """This player's opponent in the game.

        :rtype: Player
        """
        return self._opponent

    @property
    def pieces(self):
        """All the uncaptured chess Pieces owned by this player.

        :rtype: list[Piece]
        """
        return self._pieces

    @property
    def rank_direction(self):
        """The direction your Pieces must go along the rank axis until they reach the other side.

        :rtype: int
        """
        return self._rank_direction

    @property
    def reason_lost(self):
        """The reason why the player lost the game.

        :rtype: str
        """
        return self._reason_lost

    @property
    def reason_won(self):
        """The reason why the player won the game.

        :rtype: str
        """
        return self._reason_won

    @property
    def time_remaining(self):
        """The amount of time (in ns) remaining for this AI to send commands.

        :rtype: float
        """
        return self._time_remaining

    @property
    def won(self):
        """If the player won the game or not.

        :rtype: bool
        """
        return self._won
