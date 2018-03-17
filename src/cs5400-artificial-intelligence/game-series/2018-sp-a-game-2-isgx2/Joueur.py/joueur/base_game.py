from joueur.delta_mergeable import DeltaMergeable


# @class BaseGame: the basics of any game
class BaseGame(DeltaMergeable):
    def __init__(self):
        DeltaMergeable.__init__(self)

    def get_game_object(self, id):
        """ gets the game object with the given id, or None

        Returns:
            BaseGameObject in the game with the given id, or None if not found
        """
        if id in self.game_objects:
            return self.game_objects[id]
