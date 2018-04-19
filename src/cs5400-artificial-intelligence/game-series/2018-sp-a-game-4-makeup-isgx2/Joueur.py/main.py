# Please do not modify this file.
# Instead have a look at `README.md` for how to start writing you AI.

import argparse
from joueur.run import run

parser = argparse.ArgumentParser(description='Runs the python client with options. Must provide a game name to play on the server.')
parser.add_argument('game', action='store', help='the name of the game you want to play on the server')
parser.add_argument('-s, --server', action='store', dest='server', default='localhost', help='the hostname or the server you want to connect to e.g. locahost:3000')
parser.add_argument('-p, --port', action='store', dest='port', default=3000, help='the port to connect to on the server. Can be defined on the server arg via server:port')
parser.add_argument('-n, --name', action='store', dest='name', help='the name you want to use as your AI\'s player name. This over-rides the name you set in your code')
parser.add_argument('-i, --index', action='store', dest='index', help='the player number you want to be, with 0 being the first player')
parser.add_argument('-w, --password', action='store', dest='password', default=None, help='the password required for authentication on official servers')
parser.add_argument('-r, --session', action='store', dest='session', default='*', help='the requested game session you want to play on the server')
parser.add_argument('--gameSettings', action='store', dest='game_settings', default=None, help='Any settings for the game server to force. Must be query string formatted (key=value&otherKey=otherValue)')
parser.add_argument('--aiSettings', action='store', dest='ai_settings', default=None, help='Any settings for the AI. Delimit pairs by an ampersand (key=value&otherKey=otherValue)')
parser.add_argument('--printIO', action='store_true', dest='print_io', help='(debugging) print IO through the TCP socket to the terminal')

run(parser.parse_args())
