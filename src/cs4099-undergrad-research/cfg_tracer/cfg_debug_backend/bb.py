class BasicBlock:
    def __init__(self, name='', successors=[]):
        self.name = name
        self.successors = successors