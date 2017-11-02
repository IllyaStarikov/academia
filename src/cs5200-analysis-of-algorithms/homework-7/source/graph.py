#!/usr/local/bin/python3
#
# graph.py
# homework-7
#
# Created by Illya Starikov on 10/19/17.
# Copyright 2017. Illya Starikov. All rights reserved.
#


from numpy import matrix


class Graph:
    adjacency_list = {}
    is_directed = False

    def __init__(self, is_directed=False):
        self.adjacency_list = {}
        self.is_directed = is_directed

    def add_edge(self, start, destination):
        self.adjacency_list[start].add(destination)

        if self.is_directed:
            self.adjacency_list[destination].add(start)

    def add_node(self, node):
        if node not in self.adjacency_list:
            self.adjacency_list[node] = set()

    def print_graph(self):
        max_row, max_column = self.max_dimensions
        list_version = [[0 for i in range(max_column)] for j in range(max_row)]

        for source, destination_set in self.adjacency_list.items():
            for destination in destination_set:
                list_version[source][destination] = 1

        print(matrix(list_version))

    @property
    def max_dimensions(self):
        max_element = max(self.adjacency_list.keys())

        for _, value in self.adjacency_list.items():
            value = list(value)

            if value:
                if max(value) > max_element:
                    max_element = max(value)

        return max_element + 1, max_element + 1

    def depth_first_search(self, start_node, preserve_order=True):
        if preserve_order:
            colors = {}
            for vertex in self.adjacency_list:
                colors[vertex] = "white"

            return self.__depth_first_search_preserve_order(start_node, colors, None)
        else:
            return self.__depth_first_search(start_node, None)

    def breadth_first_search(self, start_node, preserve_order=True):
        if preserve_order:
            return self.__breadth_first_search_preserve_order(start_node)
        else:
            return self.__breadth_first_search(start_node)

    def __depth_first_search(self, start_node, visited_nodes):
        if visited_nodes is None:
            visited_nodes = set()

        visited_nodes.add(start_node)
        for unvisited_node in self.adjacency_list[start_node] - visited_nodes:
            self.__depth_first_search(unvisited_node, visited_nodes)

        return visited_nodes

    def __depth_first_search_preserve_order(self, start_node, colors, visited_nodes):
        if visited_nodes is None:
            visited_nodes = []

        if colors[start_node] is "white":
            colors[start_node] = "grey"
            visited_nodes += [start_node]

        for unvisited_node in [x for x in self.adjacency_list[start_node] if x not in visited_nodes]:
            if colors[unvisited_node] is "white":
                self.__depth_first_search_preserve_order(unvisited_node, colors, visited_nodes)

        colors[start_node] = "black"

        return visited_nodes

    def __breadth_first_search(self, start):
        visited, queue = set(), [start]

        while queue:
            vertex = queue.pop(0)

            if vertex not in visited:
                visited.add(vertex)
                queue.extend(self.adjacency_list[vertex] - visited)

        return visited

    def __breadth_first_search_preserve_order(self, start):
        colors = {}

        for vertex in self.adjacency_list:
            colors[vertex] = "white"

        queue = [start]
        visited_nodes = [start]

        while queue:
            node = queue.pop(0)

            for unvisited_node in list(self.adjacency_list[node]):
                if colors[unvisited_node] is "white":
                    colors[unvisited_node] = "grey"
                    queue.insert(0, unvisited_node)
                    visited_nodes += [unvisited_node]

            colors[node] = "black"

        return visited_nodes
