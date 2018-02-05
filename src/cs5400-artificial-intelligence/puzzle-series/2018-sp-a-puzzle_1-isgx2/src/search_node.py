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
