#!/usr/local/bin/python3
#
# search_node.py
# puzzle-assignment
#
# Created by Illya Starikov on 01/25/18.
# Copyright 2018. Illya Starikov. All rights reserved.
#


class SearchNode():
    def __init__(self, state, action, parent, path_cost):
        """Generate a new search node."""
        self.state = state
        self.action = action
        self.parent = parent
        self.path_cost = path_cost

    def __eq__(self, other):
        """Determine if two search nodes are equal."""
        return self.__dict__ == other.__dict__

    def __hash__(self):
        """Hash a search node."""
        string = "{}-{}".format(self.state, self.path_cost)
        return hash(str(string))
