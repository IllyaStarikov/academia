from parse_cfgs import parse_cfgs
import networkx as nx
import sys
import json


def cfg_to_nx(cfg):
    graph = nx.DiGraph()
    print(cfg.basic_blocks.keys())
    graph.add_nodes_from(cfg.basic_blocks.keys())
    for bb in cfg.basic_blocks:
        graph.add_edges_from([(bb, dest) for dest in cfg.basic_blocks[bb].successors])
    return graph


def build_trace_graph(trace, graph):
    newgraph = graph.copy()
    newgraph.remove_nodes_from(trace.trace)
    return newgraph


def graph_stats(graphs):
    nodes = {}
    edges = {}

    for g in graphs:
        for n in g.nodes():
            if n in nodes:
                nodes[n] += 1
            else:
                nodes[n] = 1
        for e in g.edges():
            if e in edges:
                edges[e] += 1
            else:
                edges[e] = 1
    return nodes, edges


def discriminant_graph_totality(verts1, verts2, edges2, count):
    dgraph = nx.DiGraph()
    for v in verts2:
        if verts2[v] == count:
            dgraph.add_node(v)
    for e in edges2:
        if edges2[v] == count:
            dgraph.add_edge(e)
    dgraph.remove_nodes_from(verts1.keys())
    return dgraph


def discriminant_graph(verts1, verts2, edges2, count, thresh):
    dgraph = nx.DiGraph()
    for v in verts2:
        if verts2[v] == count:
            dgraph.add_node(v)
    for e in edges2:
        if edges2[v] == count:
            dgraph.add_edge(e)

    inc=0
    running = True
    gcopy = dgraph.copy()
    while inc < thresh and running:
        torem = [v for v in verts1 if verts1[v] > inc]
        gcopy.remove_nodes_from(torem)
        if len(gcopy.nodes()) > 0:
            running = False
        else:
            inc += 1
            gcopy=dgraph.copy()
    return gcopy




cfg_file = sys.argv[1]
cfg = parse_cfgs(cfg_file)[0]
G = cfg_to_nx(cfg)
#sys.argv[2] should be a json string of all of the traces as from the ui
traces = json.loads(sys.argv[2])
good_runs = [build_trace_graph(t.trace, G) for t in traces if t.good]
bad_runs = [build_trace_graph(t.trace, G) for t in traces if not t.good]

non_disc_edges = set(G.edges())
for g in good_runs + bad_runs:
    non_disc_edges &= g.edges

for g in good_runs:
    g.remove_edges_from(non_disc_edges)
    g.remove_nodes_from(nx.isolates(g))

for g in bad_runs:
    g.remove_edges_from(non_disc_edges)
    g.remove_nodes_from(nx.isolates(g))

good_verts, good_edges = graph_stats(good_runs)
bad_verts, bad_edges = graph_stats(bad_runs)

dgraph = discriminant_graph(good_verts, bad_verts, bad_edges, len(bad_runs), len(good_runs))

print(min(nx.connected_components(dgraph), key=lambda x: len(x)))