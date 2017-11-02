#!/usr/local/bin/python3
#
# problem-7-1.py
# homework-7
#
# Created by Illya Starikov on 10/23/17.
# Copyright 2017. Illya Starikov. All rights reserved.
#

from graph import Graph
import random
import sys


class ArticulateGraph(Graph):
    time = 0
    times, colors, lows = {}, {}, {}

    def find_minimum(self, start_node, visited_nodes=None):
        if visited_nodes is None:
            self.times, self.colors, self.lowes = {}, {}, {}
            self.time = 0

            for vertex in self.adjacency_list:
                self.colors[vertex] = "white"

            visited_nodes = []

        for unvisited_node in [x for x in self.adjacency_list[start_node] if x not in visited_nodes]:
            if self.colors[unvisited_node] is "white":
                self.colors[start_node] = "grey"
                self.time += 1
                visited_nodes += [start_node]

                self.times[start_node] = self.time
                self.lows[start_node] = self.times[start_node]

                for adjacent_node in self.adjacency_list[start_node]:
                    self.find_minimum(adjacent_node, visited_nodes)

                    if self.colors[adjacent_node] is "white":
                        if self.time[start_node] < self.lows[self.adjacency_list]:
                            self.lows[start_node] = self.times[adjacent_node]

        self.colors[start_node] = "black"
        self.time += 1

        return self.lows, self.times


max_number_of_nodes = 10
max_number_of_edges = 30

dfs_traversals = 15
bfs_traversals = 15


def main():
    sys.setrecursionlimit(20000)
    graph = ArticulateGraph(False)
    all_possible_edges = range(max_number_of_nodes)

    for node_counter in range(max_number_of_nodes):
        graph.add_node(node_counter)

    for edge_counter in range(max_number_of_edges):
        start, destination = random.sample(all_possible_edges, 2)
        graph.add_edge(start, destination)

    graph.print_graph()

    v = random.sample(graph.adjacency_list.keys(), 1)[0]
    lows, times = graph.find_minimum(v)
    print(lows == times)


if __name__ == "__main__":
    main()
