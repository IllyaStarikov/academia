#!/usr/local/bin/python3
#
# test_mechanical_match.py
# tests
#
# Created by Illya Starikov on 01/27/18.
# Copyright 2018. Illya Starikov. All rights reserved.
#

import unittest
import sys

sys.path.append('./src')

from mechanical_match import MechanicalMatch
from state import State
from direction import Direction
from action import Action

from functions import parse_game_parameters, generate_game_from_namespace


class MechanicalTestCase(unittest.TestCase):
    def generate_board(self):
        grid = [[3, 2, 2, 3],
                [1, 3, 2, 4],
                [2, 1, 4, 2],
                [3, 2, 3, 2]]
        pool = [[4, 2, 3, 1],
                [2, 2, 1, 3],
                [1, 3, 3, 4],
                [4, 3, 3, 4]]

        test_string = """50
10
4
4
8
4
0
4 2 3 1
2 2 1 3
1 3 3 4
4 3 3 4
3 2 2 3
1 3 2 4
2 1 4 2
3 2 3 2

1 2 3 4
5 6 7 8"""

        return generate_game_from_namespace(parse_game_parameters(test_string)), grid, pool

    def test_init(self):
        match, grid, pool = self.generate_board()

        self.assertEqual(match.quota, 50)
        self.assertEqual(match.swaps_allowed, 10)
        self.assertEqual(match.device_types, 4)
        self.assertEqual(match.column_max, 4)
        self.assertEqual(match.row_max, 8)
        self.assertEqual(match.pool_height, 4)
        self.assertEqual(match.bonuses_being_used, 0)
        self.assertEqual(match.grid, grid)
        self.assertEqual(match.pool, pool)

    def test_initial_state(self):
        match, grid, pool = self.generate_board()
        initial_state = match.initial_state

        self.assertEqual(initial_state.grid, grid)
        self.assertEqual(initial_state.pool, pool)
        self.assertEqual(initial_state.swaps, 0)
        self.assertEqual(initial_state.points, 0)
        self.assertEqual(initial_state.number_of_device_types, match.device_types)

    def test_grid_size(self):
        not_long_enough = [list(range(2)), list(range(2)), list(range(2))]
        not_tall_enough = [list(range(3)), list(range(3))]

        rows, columns = 5, 7
        just_right = [list(range(columns)) for i in range(rows)]

        self.assertRaises(AssertionError, MechanicalMatch.grid_size, not_long_enough)
        self.assertRaises(AssertionError, MechanicalMatch.grid_size, not_tall_enough)

        grid_rows, grid_columns = MechanicalMatch.grid_size(just_right)
        self.assertEqual(grid_rows, rows)
        self.assertEqual(grid_columns, columns)

    def test_pool_size(self):
        not_long_enough = [list(range(2)), list(range(2)), list(range(2))]
        not_tall_enough = [[], [], []]

        rows, columns = 5, 7
        just_right = [list(range(columns)) for i in range(rows)]

        self.assertRaises(AssertionError, MechanicalMatch.pool_size, not_long_enough)
        self.assertRaises(AssertionError, MechanicalMatch.pool_size, not_tall_enough)

        grid_rows, grid_columns = MechanicalMatch.pool_size(just_right)
        self.assertEqual(grid_rows, rows)
        self.assertEqual(grid_columns, columns)

    def test_goal_test(self):
        quota = 420

        not_goal = State(None, None, None, None, 1/2 * quota, None)
        is_goal = State(None, None, None, None, 2*quota, None)

        self.assertFalse(MechanicalMatch.goal_test(not_goal, quota))
        self.assertTrue(MechanicalMatch.goal_test(is_goal, quota))

    def test_actions(self):
        grid = [
            ['X', 'X', 'a', 'b', 'X', 'c', 'd', 'X'],
            ['e', 'f', 'g', 'h', 'i', 'j', 'k', 'l'],
            ['X', 'm', 'n', 'X', 'X', 'o', 'p', 'X'],
            ['q', 'r', 's', 't', 'X', 'u', 'X', 'X']
        ]

        all_actions = [
            Action((0, 7), Direction.DOWN),
            Action((3, 4), Direction.RIGHT),
            Action((0, 4), Direction.DOWN)
        ]

        state = State(grid, None, None, None, None)
        actions = list(MechanicalMatch.actions(state))

        for action in all_actions:
            self.assertTrue(action in actions)

    def test_result(self):
        pool = [[2, 2, 2, 1]]
        grid = [[1, 2, 2, 4],
                [3, 1, 3, 3],
                [1, 3, 4, 4]]

        expected_pool = [[2, 3, 1, 2]]
        expected_grid = [[3, 2, 2, 1],
                         [4, 2, 2, 4],
                         [2, 3, 4, 4]]

        state = State(grid, pool, 0, 0, 4)
        action = Action((1, 0), Direction.RIGHT)
        result = MechanicalMatch.result(state, action)

        self.assertEqual(result.grid, expected_grid)
        self.assertEqual(result.pool, expected_pool)
        self.assertEqual(result.swaps, 1)
        self.assertEqual(result.points, 6)
        self.assertEqual(result.number_of_device_types, 4)

    def test_path_cost(self):
        state = State(None, None, None, None, None)
        action = Action((0, 0), Direction.RIGHT)

        self.assertEqual(MechanicalMatch.path_cost(state, action), 1)

    def test_swap(self):
        rows, columns = 5, 7
        grid = [list(range(columns)) for i in range(rows)]

        self.assertRaises(AssertionError, MechanicalMatch.swap, grid, (rows - 1, columns - 1), Direction.RIGHT)
        self.assertRaises(AssertionError, MechanicalMatch.swap, grid, (0, 0), Direction.UP)

        before = (grid[0][0], grid[0][1])
        MechanicalMatch.swap(grid, (0, 0), Direction.RIGHT)
        after = (grid[0][0], grid[0][1])

        self.assertEqual(before[0], after[1])
        self.assertEqual(before[1], after[0])

    def test_reduce(self):
        pool = [[1, 2,  3,  4],
                [5, 6,  7,  8],
                [9, 10, 11, 12]]

        grid = [[1, 5,  5,  5],
                [2, 5,  7,  4],
                [1, 5,  11, 5],
                [5, 5,  12, 3]]

        expected_pool = [[1, 9,  4, 7],
                         [5, 9,  3,  4],
                         [9, 12, 7,  8]]

        expected_grid = [[1, 1,  11, 12],
                         [2, 2,  7,  4],
                         [1, 6,  11, 5],
                         [5, 10, 12, 3]]

        MechanicalMatch.reduce(grid, pool, 12)

        self.assertEqual(grid, expected_grid)
        self.assertEqual(pool, expected_pool)

    def test_swap_is_valid(self):
        grid = [[1, 2, 2, 4],
                [3, 1, 3, 3],
                [1, 3, 4, 4]]

        self.assertTrue(MechanicalMatch.swap_is_valid(grid, (1, 0), Direction.RIGHT))
        self.assertFalse(MechanicalMatch.swap_is_valid(grid, (0, 0), Direction.DOWN))

    def test_match_exists(self):
        grid = [[1, 2, 2, 4],
                [3, 1, 3, 3],
                [1, 3, 4, 4]]

        self.assertFalse(MechanicalMatch.match_exists(grid))

        MechanicalMatch.swap(grid, (1, 0), Direction.RIGHT)
        self.assertTrue(MechanicalMatch.match_exists(grid))

    def test_find_all_points(self):
        grid = [[1, 2, 2, 4],
                [3, 1, 3, 3],
                [1, 3, 4, 4]]
        grid_points = set([(0, 0), (1, 0), (2, 0), (1, 1), (1, 2), (1, 3)])

        self.assertTrue(MechanicalMatch.find_all_points_of_matches(grid) == set())

        MechanicalMatch.swap(grid, (1, 0), Direction.RIGHT)
        self.assertTrue(MechanicalMatch.find_all_points_of_matches(grid) == grid_points)
