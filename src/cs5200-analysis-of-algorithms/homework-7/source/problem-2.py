#!/usr/local/bin/python3
#
# problem-2.py
# homework-7
#
# Created by Illya Starikov on 10/16/17.
# Copyright 2017. Illya Starikov. All rights reserved.
#

import random
from graph import Graph

max_number_of_nodes = 10
max_number_of_edges = 30

dfs_traversals = 15
bfs_traversals = 15


def main():
    graph = Graph(False)
    all_possible_edges = range(max_number_of_nodes)

    for node_counter in range(max_number_of_nodes):
        graph.add_node(node_counter)

    for edge_counter in range(max_number_of_edges):
        start, destination = random.sample(all_possible_edges, 2)
        graph.add_edge(start, destination)

    graph.print_graph()

    for _ in range(dfs_traversals):
        random_start, random_destination = random.sample(all_possible_edges, 2)
        visited_nodes_bfs = graph.breadth_first_search(random_start)
        visited_nodes_dfs = graph.depth_first_search(random_start)

        print(visited_nodes_dfs, visited_nodes_bfs)


if __name__ == "__main__":
    main()
