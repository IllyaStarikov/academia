#!/usr/local/bin/python3
#
# test-AI.py
# tests
#
# Created by Illya Starikov on 02/01/18.
# Copyright 2018. Illya Starikov. All rights reserved.
#

import unittest
import sys

sys.path.append('./src')

from mechanical_match import MechanicalMatch
from state import State
from direction import Direction
from action import Action
from AI import AI

from functions import parse_game_parameters, generate_game_from_namespace


class AITestCase(unittest.TestCase):
    failure = """1
100
56
4
14
4
0
1 2 3 4
5 6 7 8
9 10 11 12
13 14 15 16
17 18 19 20
21 22 23 24
25 26 27 28
29 30 31 32
33 34 35 36
37 38 39 40
41 42 43 44
45 46 47 48
49 50 51 52
53 54 55 56"""

    positive = """50
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
3 2 3 2"""

    def generate_board(self, from_input):
        return generate_game_from_namespace(parse_game_parameters(from_input))

    def test_DFS(self):
        game = self.generate_board(self.failure)
        ai = AI(game)

        result = ai.breadth_first_tree_search()
        self.assertEqual(result, None)

        game = self.generate_board(self.positive)
        ai = AI(game)

        result = ai.breadth_first_tree_search()







