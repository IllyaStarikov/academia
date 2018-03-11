from bb import BasicBlock
#from graphviz import Digraph
class CFG:
    def __init__(self, name=''):
        self.function_name = name
        self.basic_blocks = dict()
        self.entry_node = ''
        self.exit_node = ''

    def reverse_labels(self):
        num_blocks = len(self.basic_blocks) - 1 # to account for zero indexing
        label_map = {bb: 'B' + str(num_blocks - int(bb[1:])) for bb in self.basic_blocks}
        self.entry_node = label_map[self.entry_node]
        self.exit_node = label_map[self.exit_node]
        new_blocks = {bb: BasicBlock(bb) for bb in label_map.values()}
        for bb in self.basic_blocks:
            new_blocks[label_map[bb]].successors = [label_map[x] for x in self.basic_blocks[bb].successors]
            new_blocks[label_map[bb]].preds = [label_map[x] for x in self.basic_blocks[bb].preds]
        self.basic_blocks = new_blocks


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
            if self.exit_node is block_id:
                bb.preds = lines[-1].split(':')[-1].strip().split()
            else:
                bb.preds = lines[-2].split(':')[-1].strip().split()
        self.basic_blocks[block_id] = bb

    def label(self, bb_id):
        if bb_id == self.entry_node:
            return bb_id + ' ENTRY'
        if bb_id == self.exit_node:
            return bb_id + ' EXIT'
        return bb_id

    def to_json(self):
        # Dumps this to a json string compatible with vis.js
        keep_nodes = [x for x in self.basic_blocks if x not in (self.entry_node, self.exit_node)]
        nodes = [{'id': bb, 'label': self.label(bb)} for bb in keep_nodes]
        edges = []
        make_edge = lambda b1, b2: {'from': b1, 'to': b2, 'arrows':'to'}
        for bb in keep_nodes:
            for succ in self.basic_blocks[bb].successors:
                if succ not in (self.entry_node, self.exit_node):
                    edges.append(make_edge(bb, succ))
        #print(nodes)
        #print(edges)
        return {'nodes': nodes, 'edges': edges}


    # def to_dot(self, fname = None):
    #     g = Digraph(self.function_name, fname)
    #     # set up nodes
    #     for bb in self.basic_blocks:
    #         if bb is self.entry_node:
    #             g.node(bb, label=self.function_name.replace(' ','_') + '_ENTER', shape='rectangle')
    #         elif bb is self.exit_node:
    #             g.node(bb, label=self.function_name.replace(' ','_') + '_EXIT', shape='rectangle')
    #         elif len(self.basic_blocks[bb].successors) > 1:
    #             g.node(bb, '{'+bb+'|{<T>T|<F>F}}', shape='record')
    #         else:
    #             g.node(bb, label=bb, shape='rectangle')
    #     for bb in self.basic_blocks:
    #         if len(self.basic_blocks[bb].successors) == 1:
    #             g.edge(bb, self.basic_blocks[bb].successors[0])
    #         elif len(self.basic_blocks[bb].successors) > 1:
    #             g.edge(bb+':T', self.basic_blocks[bb].successors[0])
    #             g.edge(bb+':F', self.basic_blocks[bb].successors[1])
    #
    #     #g.save()
    #     g.view()