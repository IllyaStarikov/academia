#!/usr/local/bin/python3
#
# state.py
# puzzle-assignment
#
# Created by Illya Starikov on 01/25/18.
# Copyright 2018. Illya Starikov. All rights reserved.
#


class State():
    def __init__(self, grid, pool, swaps, max_swaps, points, number_of_device_types):
        """Generates a new State object."""
        self.grid = grid
        self.pool = pool
        self.swaps = swaps
        self.max_swaps = max_swaps
        self.points = points
        self.number_of_device_types = number_of_device_types

    def __eq__(self, other):
        """Determine if two states are different."""
        return self.__dict__ == other.__dict__

    def __str__(self):
        """A string description of a state.
        All are primitives, so I can get away with this."""
        return str(self.__dict__)
