# NOTE: this file should not be modified by competitors
from joueur.utilities import camel_case_converter
import joueur.error_code as error_code
import joueur.ansi_color_coder as color
import sys


# @class BaseAI: the basic AI functions that are the same between games
class BaseAI:
    def __init__(self, game):
        self._game = game
        self._player = None
        self._settings = {}

    def set_player(self, player):
        self._player = player

    @property
    def game(self):
        """The reference to the Game instance this AI is playing.

        :rtype: Game
        """
        return self._game

    @property
    def player(self):
        """Player: The reference to the Player this AI controls in the Game.

        :rtype: Player
        """
        return self._player

    def set_settings(self, ai_settings_str):
        if ai_settings_str:
            settings = ai_settings_str.split("&")
            for pair in settings:
                kv = pair.split("=")
                self._settings[kv[0]] = kv[1] if len(kv) == 2 else ""

    def get_setting(self, key):
        """Gets an AI setting passed to the program via the `--aiSettings`
        flag. If the flag was set it will be returned as a string value,
        None otherwise.

        Args:
            key (str): The key of the setting you wish to get the value for

        Returns:
            str: A string representing the value set via command line, or None
            if the key was not set
        """
        return self._settings[key] if key in self._settings else None

    # intended to be overridden by the AI class
    def start(self):
        pass

    # intended to be overridden by the AI class
    def game_updated(self):
        pass

    # intended to be overridden by the AI class
    def _do_order(self, order, arguments):
        callback = getattr(self, camel_case_converter(order))

        if callback is not None:
            try:
                return callback(*arguments)
            except:
                error_code.handle_error(
                    error_code.AI_ERRORED, sys.exc_info()[0],
                    "AI caused exception while trying to execute order '{}'."
                    .format(order)
                )
        else:
            error_code.handle_error(
                error_code.REFLECTION_FAILED,
                message="AI has no function '' to respond with.".format(order)
            )

    # This is called when this AI sends some invalid command to the server.
    # The message explaining why it is invalid will be automatically printed to
    # the screen via this function.
    # You can manually inherit this method, but because the only data you get
    # about the invalid event is a human readable message, printing it to the
    # terminal should be enough to not expose it to all except the curious.
    def invalid(self, message):
        print(color.text("yellow") + "Invalid: " + message + color.reset())

    # intended to be overridden by the AI class
    def end(self):
        pass
