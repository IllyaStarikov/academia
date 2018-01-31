#!/usr/local/bin/python3
#
# mechanical_match.py
# puzzle-assignment
#
# Created by Illya Starikov on 01/22/18.
# Copyright 2018. Illya Starikov. All rights reserved.
#


class MechanicalMatch():
    def __init__(self, quota, swaps_allowed, device_types, column_max, row_max, pool_height, bonuses_being_used, pool, grid):
        """Generate initial configuration of the board and all if it's parameters."""

        self.quota = quota
        self.swaps_allowed = swaps_allowed
        self.device_types = device_types
        self.column_max = column_max
        self.row_max = row_max
        self.pool_height = pool_height
        self.bonuses_being_used = bonuses_being_used
        self.pool = pool
        self.grid = grid
