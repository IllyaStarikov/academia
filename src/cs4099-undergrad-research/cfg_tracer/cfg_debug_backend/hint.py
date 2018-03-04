from parse_cfgs import parse_cfgs
import networkx as nx
import sys
import os
import json


def cfg_to_nx(cfg):
    graph = nx.DiGraph()
    graph.add_nodes_from(cfg.basic_blocks.keys())
    for bb in cfg.basic_blocks:
        graph.add_edges_from([(bb, dest) for dest in cfg.basic_blocks[bb].successors])
    return graph


def build_trace_graph(trace):
    newgraph = nx.DiGraph()
    newgraph.add_nodes_from(trace)
    newgraph.add_edges_from(zip(trace[:-1], trace[1:]))
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


def build_dgraph(verts, edges, count):
    disc_graph = nx.DiGraph()
    for v in verts:
        if verts[v] == count:
            disc_graph.add_node(v)
    for e in edges:
        if edges[e] == count:
            disc_graph.add_edge(*e)
    return disc_graph


def discriminant_graph_total(verts_include, edges_include, verts_exclude, target_num):
    disc_graph = build_dgraph(verts_include, edges_include, target_num)
    disc_graph.remove_nodes_from(verts_exclude.keys())
    return disc_graph


def discriminant_graph_threshold(verts_include, edges_include, verts_exclude, target_num, threshold):
    disc_graph = build_dgraph(verts_include, edges_include, target_num)
    counter = 1
    gcopy = disc_graph.copy()
    while counter < threshold:
        to_remove = [v for v in verts_exclude if verts_exclude[v] > counter]
        gcopy.remove_nodes_from(to_remove)
        if len(gcopy.nodes()) > 0:
            return gcopy
        gcopy = disc_graph.copy()
        counter += 1
    # if we're here, there is no majority of discriminant graph, so return an empty graph
    return nx.DiGraph()


cfg_file = os.path.join(sys.argv[1], 'out.cfg')
cfg = parse_cfgs(cfg_file)[0]
G = cfg_to_nx(cfg)
# sys.argv[2] should be a json string of all of the traces as from the ui
traces = json.loads(sys.argv[2])
good_runs = [build_trace_graph(t['trace']) for t in traces if t['good'] == 'true']
bad_runs = [build_trace_graph(t['trace']) for t in traces if t['good'] == 'false']
non_disc_edges = set(G.edges())
for g in good_runs + bad_runs:
    non_disc_edges &= set(g.edges())

for g in good_runs:
    g.remove_edges_from(non_disc_edges)
    g.remove_nodes_from(list(nx.isolates(g)))

for g in bad_runs:
    g.remove_edges_from(non_disc_edges)
    g.remove_nodes_from(list(nx.isolates(g)))

good_verts, good_edges = graph_stats(good_runs)
bad_verts, bad_edges = graph_stats(bad_runs)

# find what is in bad that is not in good
dgraph = discriminant_graph_total(bad_verts, bad_edges, good_verts, len(bad_runs))
if len(dgraph.nodes()) == 0:
    dgraph = discriminant_graph_threshold(bad_verts, bad_edges, good_verts, len(bad_runs), (len(good_runs) + 1) // 2)
if len(dgraph.nodes()) == 0:
    dgraph = discriminant_graph_total(good_verts, good_edges, bad_verts, len(good_runs))
if len(dgraph.nodes()) == 0:
    dgraph = discriminant_graph_threshold(good_verts, good_edges, bad_verts, len(good_runs), len(good_runs))

if len(dgraph.nodes()) > 0:
    print(json.dumps(list(min(nx.weakly_connected_components(dgraph), key=lambda x: len(x)))))
else:
    print(json.dumps([]))