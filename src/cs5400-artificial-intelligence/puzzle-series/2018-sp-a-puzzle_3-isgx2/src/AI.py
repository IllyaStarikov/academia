#!/usr/local/bin/python3
#
# AI.py
# puzzle-assignment
#
# Created by Illya Starikov on 01/27/18.
# Copyright 2018. Illya Starikov. All rights reserved.
#

from search_node import SearchNode
from mechanical_match import MechanicalMatch
from ai_heuristic import AIHeuristic
from logger import logger, LogPriority

from queue import PriorityQueue
from collections import deque
from random import shuffle


class AI():
    def __init__(self, game):
        """Just sets the game up."""
        self.game = game
        self.max_score = 0

    def __get_heuristic(self, heuristic):
        return AIHeuristic.get_heuristic(heuristic, self.game.quota, self.game.swaps_allowed)

    def best_first_search(self, heuristic):
        """Does a greedy Best First Search search on the game state.

        Args:
            herusitic (HeuristicType): The type of heuristic wanted to run
            for this search.

        Returns:
            SearchNode: The node that the solution was found in.
        """

        node = SearchNode(self.game.initial_state, None, None, 1)
        h = self.__get_heuristic(heuristic)
        h_value = h(node)

        self.max_score = 0
        nodes_generated = 0

        if MechanicalMatch.goal_test(node.state, self.game.quota):
            return self.solution(node)

        frontier = PriorityQueue()
        explored = set()

        # The priority queue is sorted based on the h_value, but because the node
        # call doesn't have a comparison operator, there needs to another value to
        # rely on. So we use it's discovery time.
        frontier.put((h_value, nodes_generated, node))
        explored.add(node)

        while not frontier.empty():
            _, _, node = frontier.get()

            for action in MechanicalMatch.actions(node.state):
                child = self.child_node(node.state, node, action)

                if child not in explored:
                    nodes_generated += 1
                    self.log_progress(child)

                    if MechanicalMatch.goal_test(child.state, self.game.quota):
                        logger.log("Nodes Generated: {}".format(nodes_generated), LogPriority.INFO)
                        return self.solution(child)

                    explored.add(child)
                    frontier.put((h(child), nodes_generated, child))

    def iterative_deepening_depth_first_search(self):
        """Does a ID-DFS search on the game state.

        Returns:
            SearchNode: The node that the solution was found in.
        """
        for depth in range(self.game.swaps_allowed + 1):
            result = self.depth_limited_search(depth)

            if result:
                return result

    def depth_limited_search(self, depth_limit):
        """Runs a Depth Limited DFS search on the game state"""
        node = SearchNode(self.game.initial_state, None, None, 1)
        return self.__recursive_depth_limited_seach(node, depth_limit)

    def __recursive_depth_limited_seach(self, node, limit):
        """The actual search function for Depth Limited DFS"""
        if MechanicalMatch.goal_test(node.state, self.game.quota):
            return self.solution(node)
        elif limit == 0:
            return None

        children = []
        for action in MechanicalMatch.actions(node.state):
            child = self.child_node(node.state, node, action)
            children += [child]

        # randomize children to get better average results. note that this will make the
        # output stochastic. if needing more deterministic results, just delete the
        # `shuffle(children` line.
        shuffle(children)
        for child in children:
            result = self.__recursive_depth_limited_seach(child, limit - 1)
            self.log_progress(child)

            if result:
                return result

    def breadth_first_search(self):
        """Does a BFS search on the game state.

        Returns:
            SearchNode: The node that the solution was found in.
        """

        node = SearchNode(self.game.initial_state, None, None, 1)
        self.max_score = 0

        if MechanicalMatch.goal_test(node.state, self.game.quota):
            return self.solution(node)

        frontier = deque([node])

        while len(frontier) > 0:
            node = frontier.popleft()

            for action in MechanicalMatch.actions(node.state):
                child = self.child_node(node.state, node, action)
                self.log_progress(child)

                if MechanicalMatch.goal_test(child.state, self.game.quota):
                    return self.solution(child)

                frontier.append(child)

    @staticmethod
    def child_node(state, parent, action):
        """Generates a child node based on the current state, and the action to take.

        Args:
            state (State): The current state of the game.
            parent (SearchNode): The parent of the returned child node.
            action (Action): The action to take to generate the child.

        Returns:
            SearchNode: The node generated by applying action onto the state.
        """
        state = MechanicalMatch.result(state, action)
        cost = parent.path_cost + MechanicalMatch.path_cost(state, action)

        return SearchNode(state, action, parent, cost)

    @staticmethod
    def solution(node):
        """A function to call when a solution has been found.

        Args:
            node (SearchNode): The node where the solution was found.

        Returns:
            SearchNode: Returns the node passed
        """

        return node

    def log_progress(self, node):
        """Logs the current progress of the game.

        Args:
            node (SearchNode): The current search node
        """
        self.max_score = max(self.max_score, node.state.points)
        logger.log(self.max_score, LogPriority.PROGRESS)
