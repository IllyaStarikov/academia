class BasicBlock:
    def __init__(self, name='', successors=[], preds = []):
        self.name = name
        self.successors = successors
        self.preds = []