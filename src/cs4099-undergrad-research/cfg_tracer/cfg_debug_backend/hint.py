from parse_cfgs import parse_cfgs
import networkx as nx
import sys
import os
import json
from collections import deque

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
            nodes[n] = nodes.get(n, 0) + 1
        for e in g.edges():
            edges[e] = edges.get(e, 0) + 1
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


#def create_discriminative_graph(S1_vert_count, S1_edge_count, S2_vert_count, target_num):
#    disc_graph = build_dgraph(S1_vert_count, S1_edge_count, target_num)
#    disc_graph.remove_nodes_from(S2_vert_count.keys()) # will remove edges going to those verts as well
    # by definition, all of the nodes in S2 should have edges going from them (since we removed isolates)
#    return disc_graph


def contains_subgraph(G, edges):
    return all(map(lambda x: G.has_edge(*x), edges))


def augment_subgraph(g, freq_edges):
    return [g + [e] for e in freq_edges if e[0] == g[-1][1]]


def create_discriminative_graph(S1, S2):
    vinc, einc = graph_stats(S1) # do we even need vinc?  is there a more efficient way of generating this info?
    freq_edges = {e for e in einc if einc[e] == len(S1)}
    freq_sg = deque([[e] for e in einc if einc[e] == len(S1)])
    result = nx.DiGraph()
    while not len(freq_sg) == 0:
        sg = freq_sg.popleft()
        if not any(map(lambda g: contains_subgraph(g, sg))):
            result.add_edges_from(sg)
            freq_sg.clear()
        else:
            freq_sg.extend(augment_subgraph(sg,freq_edges))
    return result


def relaxed_create_discriminative_graph(S1_verts_count, S1_edges_count, S2_verts_count, S2_edges_count, target_num, threshold):
    counter = 1
    disc_graph = build_dgraph(S2_verts_count, S2_edges_count, target_num)
    gcopy = nx.DiGraph()
    while counter <= threshold and len(gcopy.nodes()) == 0:
        gcopy = disc_graph.copy()
        to_remove = [e for e in S1_edges_count if S1_edges_count[e] > counter]
        gcopy.remove_edges_from(to_remove)
        gcopy.remove_nodes_from(nx.isolates(gcopy))
        if len(gcopy.nodes()) > 0:
            return gcopy
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

#good_verts, good_edges = graph_stats(good_runs)
#bad_verts, bad_edges = graph_stats(bad_runs)

# find what is in bad that is not in good
dgraph = create_discriminative_graph(bad_runs, good_runs)
#if len(dgraph.nodes()) == 0:
#    dgraph = relaxed_create_discriminative_graph(good_verts, good_edges, bad_verts, bad_edges,
#                                                 len(good_runs), (len(good_runs) + 1) // 2)
#if len(dgraph.nodes()) == 0:
#    dgraph = create_discriminative_graph(good_verts, good_edges, bad_verts, len(good_runs))
#if len(dgraph.nodes()) == 0:
#    dgraph = relaxed_create_discriminative_graph(good_verts, good_edges, bad_verts, bad_edges,
                                                 #len(good_runs), len(good_runs))

if len(dgraph.nodes()) > 0:
    print(json.dumps(list(min(nx.weakly_connected_components(dgraph), key=lambda x: len(x)))))
else:
    print(json.dumps([]))