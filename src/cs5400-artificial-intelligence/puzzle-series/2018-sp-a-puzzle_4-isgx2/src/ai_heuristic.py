#!/usr/local/bin/python3
#
# AI.py
# puzzle-assignment
#
# Created by Illya Starikov on 01/27/18.
# Copyright 2018. Illya Starikov. All rights reserved.
#

from enum import Enum
from math import sqrt
from math import inf as infinity


class HeuristicType(Enum):
    SCORE_DIFFERENCE = 1,
    HOMOGENOUS = 2
    SCORE_PER_NODE = 3


class AIHeuristic():
    @staticmethod
    def get_heuristic(heuristic, max_points=None, max_swaps=None):
        """Get the desired heuristic as a lambda expression.

        Args:
            heuristic (HeuristicType): The type of heuristic wanted.
            max_point (int): The quota to be reached.
            max_swaps (int): The number of swaps allowed for the game.
        """
        if heuristic is HeuristicType.SCORE_DIFFERENCE:
            return lambda node: AIHeuristic.score_difference(node, max_points, max_swaps)
        if heuristic is HeuristicType.HOMOGENOUS:
            return lambda node: AIHeuristic.homogenous_devices(node)
        if heuristic is HeuristicType.SCORE_PER_NODE:
            return lambda node: AIHeuristic.score_per_node(node, max_points)

    @staticmethod
    def score_difference(node, max_points, max_swaps):
        """Just take the comparison of the score difference and the swap difference."""
        return (max_points - node.state.points) / (max_swaps - node.state.swaps + 1)

    @staticmethod
    def homogenous_devices(node):
        """Calculate the standard deviation of all the device types on the board."""
        device_and_count = {}

        for row in node.state.grid:
            for element in row:
                if element not in device_and_count.keys():
                    device_and_count[element] = 0

                device_and_count[element] += 1

        results = device_and_count.values()

        # standard statistics calculations
        mean = sum(results) / len(results)
        variance = sum([(xi - mean) ** 2 for xi in results]) / len(results)
        standard_deviation = sqrt(variance)

        return standard_deviation

    @staticmethod
    def score_per_node(node, max_points):
        if node.state.points == 0:
            return infinity

        return (max_points - node.state.points) / (node.state.points / node.path_cost)
