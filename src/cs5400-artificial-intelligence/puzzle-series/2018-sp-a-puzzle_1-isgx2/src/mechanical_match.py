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

from copy import deepcopy
from logger import logger, LogPriority


class MechanicalMatch():
    @property
    def initial_state(self):
        """An initial state for the game board."""
        return State(self.grid, self.pool, 0, 0, self.device_types)

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

        logger.configure_progress_bar(quota)
        logger.log("Configured Initial Parameters...", LogPriority.INFO)
        logger.log("quota: {}".format(quota), LogPriority.INFO)
        logger.log("swaps_allowed: {}".format(swaps_allowed), LogPriority.INFO)
        logger.log("device_types: {}".format(device_types), LogPriority.INFO)
        logger.log("column_max: {}".format(column_max), LogPriority.INFO)
        logger.log("row_max: {}".format(row_max), LogPriority.INFO)
        logger.log("pool_height: {}".format(pool_height), LogPriority.INFO)
        logger.log("bonuses_being_used: {}".format(bonuses_being_used), LogPriority.INFO)
        logger.log("pool: {}".format(pool), LogPriority.INFO)
        logger.log("grid: {}".format(grid), LogPriority.INFO)

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

        if __debug__:
            # sorry about this, but you can't really copy generators.
            # so I just have to do it all over again

            actions = [
                str(Action((row, column), direction))
                for row in range(0, row_max)
                for column in range(0, column_max)
                for direction in [Direction.UP, Direction.LEFT]
                if MechanicalMatch.swap_is_valid(state.grid, (row, column), direction)
            ]

            logger.log("Generated the following actions: {}".format(actions), LogPriority.INFO)

        return (
            Action((row, column), direction)
            for row in range(0, row_max)
            for column in range(0, column_max)
            for direction in [Direction.UP, Direction.LEFT]
            if MechanicalMatch.swap_is_valid(state.grid, (row, column), direction)
        )

    @staticmethod
    def result(state, action):
        """A transition model from one state and one action. Will take the
        current state and reduce it until there's no more matches.

        Note:
            This will not mutate the current state.

        Args:
            state (State): The current state of the game.
            action (Action): The action that will transition the state.

        Returns:
            State: The state after reducing the grid, with updates scores,
            number of devices swaps, swap, and number of devices types.
        """

        new_grid = deepcopy(state.grid)
        new_pool = deepcopy(state.pool)
        points = state.points

        MechanicalMatch.swap(new_grid, action.row_column_pair, action.direction)

        while MechanicalMatch.match_exists(new_grid):
            number_of_matches = len(MechanicalMatch.find_all_points_of_matches(new_grid))
            points += number_of_matches
            MechanicalMatch.reduce(new_grid, new_pool, state.number_of_device_types)

        logger.log("Ran Result, {} -> {}".format(state.grid, new_grid), LogPriority.INFO)
        return State(new_grid, new_pool, state.swaps + 1, points, state.number_of_device_types)

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

    @staticmethod
    def swap(grid, row_column_pair, direction):
        """Swaps the value of a point (specified by row_column_pair), in the direction
        specified by direction.

        Note:
            Does mutate the game grid. Also check to see the swap is valid; if not,
            throws an AssertError.

        Args:
            row_column_pair (int, int): a tuple of value (row, column) of which point to swap.
            direction (Direction): a Direction that specifies which direction to swap the element.
        """

        as_unit_vector = direction.unit_vector

        old_row, old_column = row_column_pair
        new_row, new_column = (old_row + as_unit_vector[0], old_column + as_unit_vector[1])

        row_max, column_max = MechanicalMatch.grid_size(grid)

        assert 0 <= new_row < row_max and 0 <= old_row < row_max
        assert 0 <= new_column < column_max and 0 <= old_column < column_max

        # pretty standard tuple swap
        grid[old_row][old_column], grid[new_row][new_column] = grid[new_row][new_column], grid[old_row][old_column]

    @staticmethod
    def reduce(grid, pool, number_of_device_types):
        """Removes all matches from the board, and properly inserts all new
        elements back on the board.

        Note:
            This does mutate the board. It also only does one round of reductions.
            If a reduction produces new matches, it's up to the calling function to
            take care of it. Also, uses a formula function of the form:

            ((device type at (x,1) + x + number of devices replaced so far
              during the current match cycle including the current one)
              % number of type of devices) + 1

            The location for this is down below.


        Args:
            grid (list of list): The current game grid.
            pool (list of list): The current pool.
            thus far into the game. Used to calculate new device.
            number_of_device_types (int): The total number of device types there are.
            Used to calculate the device types.

        .. _Website Description
            http://web.mst.edu/~tauritzd/courses/cs5400/sp2018/puzzle.html
        """
        def pool_fill_function(column, column_device_type, device_replace_count, number_of_device_types):
            return (column_device_type + column + device_replace_count + number_of_device_types) % number_of_device_types + 1

        row_columns_of_matches = sorted(list(MechanicalMatch.find_all_points_of_matches(grid)))
        pool_row_max, _ = MechanicalMatch.pool_size(pool)
        device_replace_count = 0

        for (row, column) in row_columns_of_matches:
            device_replace_count += 1
            new_pool_device = pool_fill_function(column, pool[0][column], device_replace_count, number_of_device_types)

            if row > 0:
                MechanicalMatch.__percolate_down(grid, column, row + 1)

            grid[0][column] = pool[-1][column]

            MechanicalMatch.__percolate_down(pool, column, pool_row_max)
            pool[0][column] = new_pool_device

    @staticmethod
    def __percolate_down(pool_or_grid, column_to_percolate, row_max_to_percolate):
        """A utility function to push down elements. Useful for reduction.

        Note:
            This will mutate pool_or_grid. Also, the last element will be copied over.

        Args:
            pool_or_grid (list of list): A list for the percolation to occur on.
            column_to_percolate (int): The column for the percolation to occur.
            row_max_to_percolate (int): The max row to percolate to.
        """

        sorted_ = sorted(range(row_max_to_percolate), reverse=True)

        for i in range(len(sorted_) - 1):
            column = column_to_percolate

            old_row = sorted_[i]
            new_row = sorted_[i + 1]

            pool_or_grid[old_row][column], pool_or_grid[new_row][column] = pool_or_grid[new_row][column], pool_or_grid[old_row][column]

    @staticmethod
    def swap_is_valid(grid, row_column_pair, direction):
        """Determines if the swap will lead to a match. Accomplishes this
        by actually performing the swap, looking to see if a match exists,
        and then swapping back.

        Note:
            This temporarily mutates the grid. Will mutate back to original
            state. Also, if out of bounds, will only return that it is not a valid state.

        Args:
            grid (list of list): The current game grid.
            row_column_pair (int, int): A tuple of value (row, column) of which point to swap.
            direction (Direction): A Direction that specifies which direction to swap the element.

        Returns:
            bool: True if the swap will lead to a match, False otherwise.
        """

        row, column = row_column_pair
        row_unit_vector, column_unit_vector = direction.unit_vector
        row_max, column_max = MechanicalMatch.grid_size(grid)

        if not (0 <= row + row_unit_vector < row_max) or not (0 <= column + column_unit_vector < column_max):
            return False

        MechanicalMatch.swap(grid, row_column_pair, direction)
        is_valid = MechanicalMatch.match_exists(grid)
        MechanicalMatch.swap(grid, row_column_pair, direction)

        return is_valid

    @staticmethod
    def match_exists(grid):
        """Determines if the grid passed contains a valid match.

        Args:
            grid (list of list): The current game grid.

        Returns:
            bool: True if the board contains three adjacent rows.
            or three adjacent column of the same device type, False otherwise.
        """

        row_max, column_max = MechanicalMatch.grid_size(grid)

        for row in range(0, row_max):
            last_two = (grid[row][0], grid[row][1])

            for column in range(2, column_max):
                current_element = grid[row][column]

                if last_two[0] == last_two[1] == current_element:
                    return True

                last_two = (last_two[1], current_element)

        for column in range(0, column_max):
            last_two = (grid[0][column], grid[1][column])

            for row in range(2, row_max):
                current_element = grid[row][column]

                if last_two[0] == last_two[1] == current_element:
                    return True

                last_two = (last_two[1], current_element)

        return False

    @staticmethod
    def find_all_points_of_matches(grid):
        """Find all the matches, and returns them. Makes use of two helper functions,
        __find_all_vertical_matches and __find_all_horizontal_matches.

        Returns:
            list of tuples: A list of tuples (row, column) that represent the points
            of three adjacent rows or three adjacent columns.
        """
        matches = MechanicalMatch.__find_all_horizontal_matches(grid).union(MechanicalMatch.__find_all_vertical_matches(grid))
        logger.log("Matches Found: {}".format(matches), LogPriority.INFO)

        return matches

    @staticmethod
    def __find_all_horizontal_matches(grid):
        """Find all the horizontal matches, and returns them.

        Returns:
            list of tuples: A list of tuples (row, column) that represent the points
            of three adjacent columns.
        """

        intersecting_points = set()
        row_max, column_max = MechanicalMatch.grid_size(grid)

        for row in range(0, row_max):
            last_two = (grid[row][0], grid[row][1])

            for column in range(2, column_max):
                current_element = grid[row][column]

                if last_two[0] == last_two[1] == current_element:
                    points = [(row, column - i) for i in range(3)]
                    intersecting_points = intersecting_points.union(points)

                last_two = (last_two[1], current_element)

        return intersecting_points

    @staticmethod
    def __find_all_vertical_matches(grid):
        """Find all the vertical matches, and returns them.

        Returns:
            list of tuples: A list of tuples (row, column) that represent the points
            of three adjacent rows.
        """

        intersecting_points = set()
        row_max, column_max = MechanicalMatch.grid_size(grid)

        for column in range(0, column_max):
            last_two = (grid[0][column], grid[1][column])

            for row in range(2, row_max):
                current_element = grid[row][column]

                if last_two[0] == last_two[1] == current_element:
                    points = [(row - i, column) for i in range(3)]
                    intersecting_points = intersecting_points.union(points)

                last_two = (last_two[1], current_element)

        return intersecting_points
