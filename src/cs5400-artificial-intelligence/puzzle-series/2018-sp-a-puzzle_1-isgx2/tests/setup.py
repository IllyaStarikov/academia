#!/usr/local/bin/python3
#
# setup.py
# tests
#
# Created by Illya Starikov on 01/28/18.
# Copyright 2018. Illya Starikov. All rights reserved.
#

import unittest
from test_mechanical_match import MechanicalTestCase
from test_action import ActionTestCase
from test_AI import AITestCase


def load_suite():
    tests = [MechanicalTestCase, ActionTestCase, AITestCase]

    for test in tests:
        unittest.TestLoader().loadTestsFromTestCase(test)


if __name__ == "__main__":
    load_suite()
    unittest.main()
