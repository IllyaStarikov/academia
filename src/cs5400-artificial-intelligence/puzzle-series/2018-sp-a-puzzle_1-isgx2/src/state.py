#!/usr/local/bin/python3
#
# state.py
# puzzle-assignment
#
# Created by Illya Starikov on 01/25/18.
# Copyright 2018. Illya Starikov. All rights reserved.
#


class State():
    def __init__(self, grid, pool, swaps, points, number_of_device_types):
        """Generates a new State object"""
        self.grid = grid
        self.pool = pool
        self.swaps = swaps
        self.points = points
        self.number_of_device_types = number_of_device_types
