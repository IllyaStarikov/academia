#!/usr/local/bin/python3
#
# main.py
# puzzle-assignment
#
# Created by Illya Starikov on 01/22/18.
# Copyright 2018. Illya Starikov. All rights reserved.
#

from functions import parse_arguments, parse_game_parameters, get_file_contents, generate_game_from_namespace, output_solution
from timer import Timer
from AI import AI


def main():
    timer = Timer()

    filename, output_path = parse_arguments()
    game_parameters = parse_game_parameters(get_file_contents(filename))

    game = generate_game_from_namespace(game_parameters)
    ai = AI(game)

    timer.start()
    solution = ai.breadth_first_tree_search()
    timer.stop()

    output_solution(output_path, filename, timer.difference, solution, game)


if __name__ == "__main__":
    main()
