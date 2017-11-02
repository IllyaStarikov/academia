#!/usr/local/bin/python3
#
# problem-2.py
# homework-7
#
# Created by Illya Starikov on 10/16/17.
# Copyright 2017. Illya Starikov. All rights reserved.
#

from graph import Graph


class WrestleMania(Graph):
    def determine_valid_rivalry(self):
        rivalry, not_visited = {}, list(self.adjacency_list.keys())

        for vertex in self.adjacency_list:
            rivalry[vertex] = "none"

        while "none" in rivalry.values():
            current_depth, start = 0, not_visited[-1]
            queue = [start]

            while queue:
                current_depth += 1
                node = queue.pop(0)

                for unvisited_node in list(self.adjacency_list[node]):
                    if rivalry[unvisited_node] is "none":
                        if current_depth % 2 == 0:
                            rivalry[unvisited_node] = "Baby Face"
                        else:
                            rivalry[unvisited_node] = "Heel"

                        not_visited.remove(unvisited_node)
                        queue.insert(0, unvisited_node)

        for wrestler, adjacency_wrestlers in self.adjacency_list.items():
            for adjacent_wrestler in adjacency_wrestlers:
                if rivalry[wrestler] == rivalry[adjacent_wrestler]:
                    return None

        return rivalry


def print_results(rivalry):
    if rivalry is None:
        print("No configuration could be found.")
    else:
        for node, status in rivalry.items():
            print("Wrestler {} Is A {}".format(node, status))

def main():
    odd = WrestleMania(True)
    for letter in "xyz":
        odd.add_node(letter)

    odd.add_edge('x', 'y')
    odd.add_edge('y', 'z')
    odd.add_edge('z', 'x')

    print_results(odd.determine_valid_rivalry())
    print("=" * 40)

    even = WrestleMania(True)
    for letter in "wxyz":
        even.add_node(letter)
    even.add_edge('w', 'x')
    even.add_edge('x', 'y')
    even.add_edge('y', 'z')
    even.add_edge('z', 'w')

    print_results(even.determine_valid_rivalry())
    print("=" * 40)

    disjoint = WrestleMania(True)
    for letter in "uvwxyz":
        disjoint.add_node(letter)

    disjoint.add_edge('u', 'v')
    disjoint.add_edge('w', 'x')
    disjoint.add_edge('y', 'z')

    print_results(disjoint.determine_valid_rivalry())


if __name__ == "__main__":
    main()
