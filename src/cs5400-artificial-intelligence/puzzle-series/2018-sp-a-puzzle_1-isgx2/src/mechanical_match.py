#!/usr/local/bin/python3
#
# mechanical_match.py
# puzzle-assignment
#
# Created by Illya Starikov on 01/22/18.
# Copyright 2018. Illya Starikov. All rights reserved.
#




class MechanicalMatch():
    @property
    def initial_state(self):
        """An initial state for the game board."""
        return State(self.grid, self.pool, 0, 0, 0, self.device_types)

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

    @staticmethod
    def grid_size(grid):
        """Generates the grid size and ensures grid is of proper dimensions.

        Note:
            This will throw if board dimensions are not 3x3 or higher. Meaning
            if the number of columns < 3 or rows < 3, AssertionError will be
            raised.

        Args:
            grid (list of list): The game grid.

        Returns:
            (int, int): The max row, max column (0 indexed).
        """

        row_max = len(grid)
        assert row_max > 2

        column_max = len(grid[0])
        assert column_max > 2

        return (row_max, column_max)

    @staticmethod
    def pool_size(pool):
        """Generates the pool size and ensures grid is of proper dimensions.

        Note:
            This will throw if board dimensions are not 1x3 or higher. Meaning
            if the number of columns < 3 or rows < 0, AssertionError will be
            raised.

        Args:
            grid ([list of list): The pool.

        Returns:
            (int, int): The max row, max column (0 indexed).
        """

        row_max = len(pool)
        assert row_max > 0

        column_max = len(pool[0])
        assert column_max > 2

        return (row_max, column_max)
