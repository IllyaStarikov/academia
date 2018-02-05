#!/usr/local/bin/python3
#
# functions.py
# puzzle-assignment
#
# Created by Illya Starikov on 01/22/18.
# Copyright 2018. Illya Starikov. All rights reserved.
#

import argparse
from argparse import Namespace

from mechanical_match import MechanicalMatch


def parse_arguments():
    """Parses the arguments necessary for the program to run,
    requiring only the input instance, and optionally allowing to specify
    a place to output the solution.

    Returns:
        Namespace: The arguments in a Namespace type.
    """

    parser = argparse.ArgumentParser(description='An AI to play a Candy Crush-esque game')
    parser.add_argument('puzzle_path', metavar='puzzle-path', type=str, help='The input puzzle that should be played')
    parser.add_argument('--solution_path', metavar='--solution-path', type=str, help='The directory to which the solution should be output to')

    arguments = parser.parse_args()
    return arguments.puzzle_path, arguments.solution_path


def get_file_contents(filename):
    """Returns the contents of the file specified by the filename.

    Args:
        filename (str): The filename to get content from.

    Returns:
        str or None: The file contents in one giant string (\n) and all
        or None if there is no such file.
    """

    with open(filename) as file_handler:
        return file_handler.read()


def parse_game_parameters(file_contents):
    """Extract the game parameters from the input specified.

    Args:
        file_contents (str): The contents of the specified input file.

    Returns:
        Namespace: All of the game arguments in a Namespace object.
    """

    file_contents_split = file_contents.split('\n')

    # I'm so sorry. This is ugly.
    # But I really have no idea how to make it cleaner while
    # while maintaining readability
    (
        quota,
        swaps_allowed,
        device_types,
        column_max,
        row_max,
        pool_height,
        bonuses_being_used
    ) = [int(x) for x in file_contents_split[:7]]

    # This is ugly too. But it's taking the contents after the 7th line to the
    # and adding create a 2D list with it
    pool = [[int(x) for x in x.split(' ')]
            for x in file_contents_split[7:7 + pool_height]]

    grid = [[int(x) for x in x.split(' ')]
            for x in file_contents_split[7 + pool_height:7 + row_max]]

    return Namespace(
        quota=quota,
        swaps_allowed=swaps_allowed,
        device_types=device_types,
        column_max=column_max,
        row_max=row_max,
        pool_height=pool_height,
        bonuses_being_used=bonuses_being_used,
        pool=pool,
        grid=grid
    )


def generate_game_from_namespace(namespace):
    """From a Namespace object, generate a MechanicalMatch object.

    Args:
        namespace (Namespace): All of the game parameters.

    Returns:
        MechanicalMatch: The game object.

    """
    return MechanicalMatch(
        quota=namespace.quota,
        swaps_allowed=namespace.swaps_allowed,
        device_types=namespace.device_types,
        column_max=namespace.column_max,
        row_max=namespace.row_max,
        pool_height=namespace.pool_height,
        bonuses_being_used=namespace.bonuses_being_used,
        pool=namespace.pool,
        grid=namespace.grid
    )


def calculate_new_row_column(row_column_pair, direction):
    """From a row_column_pair a direction, calculate what the complementary
    point would be.

    Args:
        row_column_pair (int, int): A tuple of value (row, column) of the initial point.
        direction (Direction): A Direction to determine which way the point should be swapped.

    Returns:
        (int, int): The point after applying the direction onto the new point.
    """

    as_unit_vector = direction.unit_vector
    return (row_column_pair[0] + as_unit_vector[0], row_column_pair[1] + as_unit_vector[1])


def determine_swaps(node, game):
    """Determine the swaps that got the game into the new state.

    Args:
        node (SearchNode): The SearchNode of the solution.
        game (MechanicalMatch): The initial game setup (used to get the pool height).

    Returns:
        list of ((int, int), (int, int)): The swaps of the form (old_x, old_y), (new_x, new_y) that led to the solution.
    """
    runner = node
    swaps = []

    while runner.parent:
        before = runner.action.row_column_pair
        after = calculate_new_row_column(runner.action.row_column_pair, runner.action.direction)

        # To get into the weird format Dr. T wants
        before = (before[1], before[0] + game.pool_height)
        after = (after[1], after[0] + game.pool_height)

        swaps += [(before, after)]
        runner = runner.parent

    return reversed(swaps)


def generate_swaps_string(swaps):
    """String-ify the weird swap data structure

    Args:
        swaps (list of ((int, int), (int, int))): The swaps of the form (old_x, old_y), (new_x, new_y)
        that led to the solution.

    Returns:
        str: A nice, clean string of the swaps (with newlines).
    """

    string = ""

    for before, after in swaps:
        string += "{}, {}\n".format(before, after)

    return string[:-1]


def output_to_file(filename, content):
    """Output content to a file.

    Args:
        filename (str): The output filename.
        content (str): What is to go into the actual file
    """

    with open(filename, "w") as text_file:
        text_file.write(content)


def output_solution(filename_of_output, filename_of_input, timer_difference, solution_node, game):
    """Outputs the solution to stdout and, optionally, to a file

    Args:
        filename_of_output (str): The filename to output the solution to, or None if output to file
        is not desired.
        filename_of_input (str): The original file the game parameters were taken from.
        timer_different (float): The amount of time (in seconds) the algorithm took to run.
        solution_node (SearchNode): The SearchNode where the solution was found.
        game (MechanicalMatch): The initial game instance.
    """

    file_contents = get_file_contents(filename_of_input)
    swap_string = generate_swaps_string(determine_swaps(solution_node, game))

    print(file_contents)
    print(swap_string)
    print(timer_difference)

    if filename_of_output:
        output_to_file(filename_of_output, "{}\n{}\n{}\n".format(file_contents, swap_string, timer_difference))
