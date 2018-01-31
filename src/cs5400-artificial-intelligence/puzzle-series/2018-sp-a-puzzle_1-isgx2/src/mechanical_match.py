#!/usr/local/bin/python3
#
# mechanical_match.py
# puzzle-assignment
#
# Created by Illya Starikov on 01/22/18.
# Copyright 2018. Illya Starikov. All rights reserved.
#

from direction import Direction
from action import Action
from state import State



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

    @staticmethod
    def goal_test(state, quota):
        """Determines if the current state is the goal.

        Args:
            state (State): The current state of the game.
            quota (int): The score limit for the game.

        Returns:
            bool: True if is goal, False if not.
        """
        return state.points >= quota

    @staticmethod
    def actions(state):
        """Generates all actions that are valid (i.e., every action in the
        in the list will produce a match.

        Args:
            state (State): The current state of the game.

        Returns:
            list of action: a list of Actions such that every action will produce
            some match.
        """

        # This is ugly, but by abusing list comprehension, I get lazy evaluation.
        # In turn, I actually do a linear search of the entire space, but only store
        # the states that are legal. Thank you, generators.

        row_max, column_max = MechanicalMatch.grid_size(state.grid)

        return (
            Action((row, column), direction)
            for row in range(0, row_max)
            for column in range(0, column_max)
            for direction in [Direction.UP, Direction.LEFT]
            if MechanicalMatch.swap_is_valid(state.grid, (row, column), direction)
        )
    @staticmethod
    def path_cost(state, action):
        """Calculates the score of applying an action onto a state.

        Args:
            state (State): The current state of the game.
            action (Action): The action that will transition the state.

        Returns:
            int: The cost of applying the action.
        """

        return 1  # I think
