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
    """Returns the contents of the file specified by the filename

    Args:
        filename (str): The filename to get content from

    Returns:
        str: The file contents in one giant string (\n) and all
    """

    with open(filename) as file_handler:
        return file_handler.read()


def parse_game_parameters(file_contents):
    """Extract the game parameters from the input specified.

    Args:
        file_contents (str): The contents of the specified input file.

    Returns:
        Namespace: All of the game arguments in a Namespace object
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
    """From a Namespace object, generate a MechanicalMatch object

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
