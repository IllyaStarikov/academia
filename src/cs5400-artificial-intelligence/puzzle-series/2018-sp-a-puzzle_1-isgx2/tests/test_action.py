#!/usr/local/bin/python3
#
# test_action.py
# tests
#
# Created by Illya Starikov on 01/27/18.
# Copyright 2018. Illya Starikov. All rights reserved.
#

import unittest
import sys

sys.path.append('./src')

from direction import Direction
from action import Action


class ActionTestCase(unittest.TestCase):
    def test_eq(self):
        action_1 = Action((2, 3), Direction.RIGHT)
        action_2 = Action((2, 4), Direction.LEFT)

        self.assertTrue(action_1 == action_2)

        action_1 = Action((2, 5), Direction.UP)
        action_2 = Action((1, 5), Direction.DOWN)

        self.assertTrue(action_1 == action_2)

        action_1 = Action((0, 0), Direction.RIGHT)
        action_2 = Action((7, 7), Direction.RIGHT)

        self.assertFalse(action_1 == action_2)
