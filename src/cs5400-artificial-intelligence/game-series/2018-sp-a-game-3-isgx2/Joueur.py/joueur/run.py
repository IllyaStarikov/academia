import importlib.util
import joueur.client
import sys
import joueur.error_code as error_code
from joueur.game_manager import GameManager
from joueur.utilities import camel_case_converter
import joueur.ansi_color_coder as color


def run(args):
    split_server = args.server.split(":")
    args.server = split_server[0]
    args.port = int((len(split_server) == 2 and split_server[1])) or args.port

    joueur.client.connect(args.server, args.port, args.print_io)

    joueur.client.send("alias", args.game)
    game_name = joueur.client.wait_for_event("named")

    module_str = "games." + camel_case_converter(game_name)

    spec = importlib.util.find_spec(module_str)
    if spec is None:
        error_code.handle_error(
            error_code.GAME_NOT_FOUND,
            None,
            'Could not find the module for game "{}".'.format(game_name)
        )

    try:
        # should load Game and AI to load based on the game selected in args
        module = importlib.import_module(module_str)
    except ImportError as e:
        error_code.handle_error(
            error_code.REFLECTION_FAILED,
            e,
            'Could not import game module: "{}".'.format(module_str)
        )

    game = module.Game()
    try:
        ai = module.AI(game)
    except:
        error_code.handle_error(
            error_code.AI_ERRORED,
            sys.exc_info()[0],
            'Could not initialize the AI class. ' +
            'Probably a syntax error in your AI.'
        )

    manager = GameManager(game)

    joueur.client.setup(game, ai, manager)

    ai.set_settings(args.ai_settings)

    joueur.client.send("play", {
        'gameName': game_name,
        'password': args.password,
        'requestedSession': args.session,
        'clientType': "Python",
        'playerName': args.name or ai.get_name() or "Python Player",
        'playerIndex': args.index,
        'gameSettings': args.game_settings
    })

    lobby_data = joueur.client.wait_for_event("lobbied")

    print('{}In Lobby for game "{}" in session "{}".{}'.format(
            color.text("cyan"),
            lobby_data['gameName'],
            lobby_data['gameSession'],
            color.reset()
        )
    )

    manager.set_constants(lobby_data['constants'])

    start_data = joueur.client.wait_for_event("start")

    print(color.text("green") + "Game is starting." + color.reset())

    ai.set_player(game.get_game_object(start_data['playerID']))
    try:
        ai.start()
        ai.game_updated()
    except:
        error_code.handle_error(
            error_code.AI_ERRORED,
            sys.exc_info()[0],
            'AI errored during game initialization'
        )

    joueur.client.play()
