NONE = 0
INVALID_ARGS = 20
COULD_NOT_CONNECT = 21
DISCONNECTED_UNEXPECTEDLY = 22
CANNOT_READ_SOCKET = 23
DELTA_MERGE_FAILURE = 24
REFLECTION_FAILED = 25
UNKNOWN_EVENT_FROM_SERVER = 26
SERVER_TIMEOUT = 27
FATAL_EVENT = 28
GAME_NOT_FOUND = 29
MALFORMED_JSON = 30
UNAUTHENTICATED = 31
AI_ERRORED = 42

_by_code = {}

for key, value in dict(locals()).items():
    if not key.startswith("_"): # then it's not a special/private variable name, so it should be an above error code name
        _by_code[value] = key

# now import so they don't get put in _by_code

import traceback
import sys
import joueur.ansi_color_coder as color
import os

def handle_error(error_code, e=None, message=None):
    if isinstance(e, SystemExit) or isinstance(e, KeyboardInterrupt): # we accidentally caught an exit exception, just re-throw it till it gets to the end of the runtime stack
        sys.exit(e.code)

    import joueur.client # avoid circular imports (sphinx won't build docs otherwise)
    joueur.client.disconnect()

    sys.stderr.write(color.text("red") + "---\nError: {}\n---".format(_by_code[error_code] if error_code in _by_code else "UNKNOWN ERROR {}".format(error_code)))

    if message:
        sys.stderr.write("\n{}\n---".format(message))

    if e:
        sys.stderr.write("\n{}\n---\n".format(str(e)))

        traceback.print_exc()

        sys.stderr.write("---")

    sys.stderr.write("\n" + color.reset())
    os._exit(error_code)
