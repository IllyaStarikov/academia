from bb import BasicBlock
from graphviz import Digraph
class CFG:
    def __init__(self, name=''):
        self.function_name = name
        self.basic_blocks = dict()
        self.entry_node = ''
        self.exit_node = ''

    def add_block(self, lines):
        # first line should be the name.  All basic blocks should be wrapped in []
        block_id = lines[0].strip()[1:-1].split()[0]
        bb = BasicBlock(block_id)
        if 'ENTRY' in lines[0]:
            self.entry_node = block_id
        if 'EXIT' in lines[0]:
            self.exit_node = block_id
        if not self.exit_node is block_id:
            # we have successors
            bb.successors = lines[-1].split(':')[-1].strip().split()
        if not self.entry_node is block_id:
            ## we have preds
            bb.preds = lines[-2].split(':')[-1].strip().split()
        self.basic_blocks[block_id] = bb

    def to_dot(self, fname = None):
        g = Digraph(self.function_name, fname)
        # set up nodes
        for bb in self.basic_blocks:
            if bb is self.entry_node:
                g.node(bb, label=self.function_name.replace(' ','_') + '_ENTER', shape='rectangle')
            elif bb is self.exit_node:
                g.node(bb, label=self.function_name.replace(' ','_') + '_EXIT', shape='rectangle')
            elif len(self.basic_blocks[bb].successors) > 1:
                g.node(bb, '{'+bb+'|{<T>T|<F>F}}', shape='record')
            else:
                g.node(bb, label=bb, shape='rectangle')
        for bb in self.basic_blocks:
            if len(self.basic_blocks[bb].successors) == 1:
                g.edge(bb, self.basic_blocks[bb].successors[0])
            elif len(self.basic_blocks[bb].successors) > 1:
                g.edge(bb+':T', self.basic_blocks[bb].successors[0])
                g.edge(bb+':F', self.basic_blocks[bb].successors[1])

        #g.save()
        g.view()
