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
from logger import logger, LogPriority

from AI import AI
from ai_heuristic import HeuristicType


def main():
    timer = Timer()

    filename, output_path = parse_arguments()
    game_parameters = parse_game_parameters(get_file_contents(filename))

    game = generate_game_from_namespace(game_parameters)
    ai = AI(game)

    timer.start()

    logger.log("Start DFS", LogPriority.INFO)
    solution = ai.best_first_search(HeuristicType.SCORE_DIFFERENCE)

    logger.log("Finish DFS", LogPriority.INFO)
    timer.stop()
    logger.stop_progress_bar()
    print("")

    logger.log("Outputting Solution", LogPriority.INFO)

    if solution is None:
        print("No Solution Found")
    else:
        output_solution(output_path, filename, timer.difference, solution, game)

    logger.log("Finished", LogPriority.INFO)


if __name__ == "__main__":
    main()
