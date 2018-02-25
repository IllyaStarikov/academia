from joueur.delta_mergeable import DeltaMergeable


# the base class that every game object within a game inherit from for Python
# manipulation that would be redundant via Creer
class BaseGameObject(DeltaMergeable):
    def __init__(self):
        DeltaMergeable.__init__(self)

    def __str__(self):
        return "{} #{}".format(self.game_object_name, self.id)

    def __repr__(self):
        return str(self)

    def __hash__(self):
        # id will always be unique server side anyways,
        #   so it should be safe to hash on
        return hash(self.id)
