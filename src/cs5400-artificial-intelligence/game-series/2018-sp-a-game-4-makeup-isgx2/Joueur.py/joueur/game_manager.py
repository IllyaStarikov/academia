from joueur.delta_mergeable import DeltaMergeable
from joueur.base_game_object import BaseGameObject
from joueur.utilities import camel_case_converter
from joueur.serializer import is_game_object_reference, is_object

# @class GameManager: managed the game and it's game objects including unserializing deltas
class GameManager():
    def __init__(self, game):
        self.game = game
        self._game_object_classes = game._game_object_classes

    def set_constants(self, constants):
        self._server_constants = constants
        self._DELTA_REMOVED = constants['DELTA_REMOVED']
        self._DELTA_LIST_LENGTH = constants['DELTA_LIST_LENGTH']

    ## applies a delta state (change in state information) to this game
    def apply_delta_state(self, delta):
        if 'gameObjects' in delta:
            self._init_game_objects(delta['gameObjects'])

        self._merge_delta(self.game, delta)

    ## game objects can be refences in the delta states for cycles, they will all point to the game objects here.
    def _init_game_objects(self, delta_game_objects):
        for id, obj in delta_game_objects.items():
            if not id in self.game._game_objects: # then we need to create it
                self.game._game_objects[id] = self._game_object_classes[obj['gameObjectName']]()

    ## Correctly apply a single change to a member of a list, dict, or object
    def _set_member(self, state, state_key, value):
        if isinstance(state_key, int) or isinstance(state, dict):
            state[state_key] = value
        else:
            setattr(state, state_key, value)

    ## recursively merges delta changes to the game.
    def _merge_delta(self, state, delta):
        delta_length = -1
        if self._DELTA_LIST_LENGTH in delta:
            delta_length = delta[self._DELTA_LIST_LENGTH]
            del delta[self._DELTA_LIST_LENGTH] # we don't want to copy this key/value over to the state, it was just to signify it is an array

        if delta_length > -1: # then this part in the state is an array
            while len(state) > delta_length: # remove elements off the array to make it's size correct.
                state.pop()
            while len(state) < delta_length: # append elements on the array to make it's size correct.
                state.append(None)

        for key in delta: # deltas will always be objects when iterating through, arrays just have keys of numbers
            d = delta[key]
            state_key = key # array's keys are real numbers, not strings e.g. "1"
            key_in_state = False

            if isinstance(state, list):
                state_key = int(key)
                key_in_state = state_key < len(state)
            else:
                if isinstance(state, DeltaMergeable):
                    state_key = "_" + camel_case_converter(state_key)
                key_in_state = state_key in state

            if d == self._DELTA_REMOVED:
                if key_in_state:
                    del state[state_key]
            elif is_game_object_reference(d): # then this is a shallow reference to a game object
                referenced_object = self.game.get_game_object(d['id'])
                self._set_member(state, state_key, referenced_object)
            elif is_object(d) and key_in_state and is_object(state[state_key]):
                self._merge_delta(state[state_key], d)
            elif not key_in_state and is_object(d):
                if isinstance(d, dict):
                    state[state_key] = [] if d in self._DELTA_LIST_LENGTH else {}
                    self._merge_delta(state[state_key], d)
            else:
                self._set_member(state, state_key, d)
