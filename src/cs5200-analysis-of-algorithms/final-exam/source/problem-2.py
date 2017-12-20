#!/usr/local/bin/python3
#
# problem-2.py
# source
#
# Created by Illya Starikov on 12/14/17.
# Copyright 2017. Illya Starikov. All rights reserved.
#

import numpy as np


class Graph:
    __adjacency_list = {}
    is_directed = False

    def __init__(self, is_directed=False):
        self.__adjacency_list = {}
        self.is_directed = is_directed

    @property
    def vertices(self):
        vertices = set()

        for key, value in self.__adjacency_list.items():
            vertices.add(key)
            vertices = vertices.union(value)

        return vertices

    @property
    def edges(self):
        edges = set()

        for key, values in self.__adjacency_list.items():
            for value in values:
                edges.add((key, value))

        return edges

    @property
    def adjacency_list_raw(self):
        return self.__adjacency_list

    @property
    def adjacency_list(self):
        max_dimension = max(self.vertices) + 1
        adj_list = [[0 for i in range(max_dimension)] for j in range(max_dimension)]

        for start, value in self.__adjacency_list.items():
            for destination in value:
                adj_list[start][destination] = 1

        return adj_list

    @property
    def number_of_edges(self):
        return len(self.edges)

    @property
    def number_of_vertices(self):
        return len(self.vertices)

    @property
    def number_of_connected_components(self):
        return len(self.connected_components)

    @property
    def number_of_components_with_euler_path(self):
        connected_components = self.connected_components

        number_of_connected_components_with_euler_path = 0
        for connected_component in connected_components:
            number_of_vertices_with_odd_degree = 0

            for vertex in connected_component:

                if vertex in self.__adjacency_list.keys():
                    if len(self.__adjacency_list[vertex]) % 2 != 0:
                        number_of_vertices_with_odd_degree += 1

            if number_of_vertices_with_odd_degree == 0 or number_of_vertices_with_odd_degree == 2:
                number_of_connected_components_with_euler_path += 1

        return number_of_connected_components_with_euler_path

    @property
    def number_of_components_with_euler_circuits(self):
        connected_components = self.connected_components

        number_of_connected_components_with_euler_circuit = 0
        for connected_component in connected_components:
            number_of_vertices_with_odd_degree = 0

            for vertex in connected_component:

                if vertex in self.__adjacency_list.keys():
                    if len(self.__adjacency_list[vertex]) % 2 != 0:
                        number_of_vertices_with_odd_degree += 1

            if number_of_vertices_with_odd_degree == 0:
                number_of_connected_components_with_euler_circuit += 1

        return number_of_connected_components_with_euler_circuit

    @property
    def connected_components(self):
        colors = {}
        for vertex in self.vertices:
            colors[vertex] = "WHITE"

        connected_components = []
        for vertex in self.vertices:
            if colors[vertex] is "WHITE":
                colors[vertex] = "GREY"
                connected_components += [self.__dfs_connected_components_visit(vertex, colors, [])]
                colors[vertex] = "BLACK"

        return connected_components

    def __dfs_connected_components_visit(self, vertex, colors, connected_components):
        connected_components += [vertex]

        if vertex in self.__adjacency_list.keys():
            for adjacent_vertex in self.__adjacency_list[vertex]:
                if colors[adjacent_vertex] is "WHITE":
                    colors[adjacent_vertex] = "GREY"
                    self.__dfs_connected_components_visit(adjacent_vertex, colors, connected_components)
                    colors[adjacent_vertex] = "BLACK"

        return list(set(connected_components))

    def add_edge(self, start, destination):
        if start not in self.__adjacency_list.keys():
            self.add_vertex(start)

        self.__adjacency_list[start].add(destination)

        if not self.is_directed:
            if destination not in self.__adjacency_list.keys():
                self.add_vertex(destination)

            self.__adjacency_list[destination].add(start)

    def add_vertex(self, vertex):
        if vertex not in self.__adjacency_list:
            self.__adjacency_list[vertex] = set()


def read_edges_from_file(filename):
    with open(filename, 'r') as content_file:
        content = content_file.read()

        content = content.replace("(", "").replace(")", "").replace(" ", "")
        vertices_string = content.split("\n")

        vertices = []
        for vertex in vertices_string:
            if vertex != "":
                vertices += [tuple([int(v) for v in vertex.split(",")])]

        return vertices

    return []


def add_list_of_edges_to_graph(graph, edges):
    for (start, destination) in edges:
        graph.add_edge(start, destination)


def dictionary_to_string_description(dictionary):
    result = ""
    for key, value in dictionary.items():
        value_printable = str(value).replace("{", "").replace("}", "")
        result += "{}: {}\n".format(key, value_printable)

    return result


def main():
    np.set_printoptions(threshold=np.nan)

    filename = "input/graph-data.txt"
    vertices = read_edges_from_file(filename)

    graph = Graph(False)
    add_list_of_edges_to_graph(graph, vertices)

    print("The number of vertices in the graph is {}".format(graph.number_of_vertices))
    print("The number of edges in the graph is {}".format(graph.number_of_edges))
    print("Below is the adjacency list for this graph with the vertices sorted.")
    print(np.matrix(graph.adjacency_list))
    print("Below is the adjacency list with of the form Vertex: Neighbor1, Neighbor2, ...")
    print(dictionary_to_string_description(graph.adjacency_list_raw))
    print("The number of connected components of this graph is {}".format(graph.number_of_connected_components))
    print("The number of connected components of the graph that have an Euler path is {}".format(graph.number_of_components_with_euler_path))
    print("I could not do this part.")
    print("The number of connected components of the graph that have an Euler circuit is {}".format(graph.number_of_components_with_euler_circuits))
    print("I could not do this part.")


if __name__ == "__main__":
    main()
