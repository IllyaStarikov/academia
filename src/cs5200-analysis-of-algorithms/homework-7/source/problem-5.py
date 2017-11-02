#!/usr/local/bin/python3
#
# problem-4.py
# homework-7
#
# Created by Illya Starikov on 10/16/17.
# Copyright 2017. Illya Starikov. All rights reserved.
#

import random
from graph import Graph


class ParentheticalOrder(Graph):
    def print_parenthetical_order(self, start_node):
        colors = {}
        for vertex in self.adjacency_list:
            colors[vertex] = "white"

        for node in sorted(self.adjacency_list):
            if colors[node] is "white":
                self.__print_parenthetical_order(node, colors)

    def __print_parenthetical_order(self, node, colors):
        colors[node] = "grey"
        print("({} ".format(node), end='')
        for neighbor in sorted(self.adjacency_list[node]):
            if colors[neighbor] is "white":
                self.__print_parenthetical_order(neighbor, colors)
        colors[node] = 'black'
        print(" {})".format(node), end='')

    def print(self):
        for x in self.adjacency_list:
            print("{} -> {}".format(x, self.adjacency_list[x]))


def main():
    graph = ParentheticalOrder(False)
    for letter in "uvwxyz":
        graph.add_node(letter)

    graph.add_edge('u', 'v')
    graph.add_edge('u', 'x')
    graph.add_edge('v', 'y')
    graph.add_edge('y', 'x')
    graph.add_edge('x', 'v')
    graph.add_edge('w', 'y')
    graph.add_edge('w', 'z')
    graph.add_edge('z', 'z')

    graph.print()
    graph.print_parenthetical_order('u')


if __name__ == "__main__":
    main()
