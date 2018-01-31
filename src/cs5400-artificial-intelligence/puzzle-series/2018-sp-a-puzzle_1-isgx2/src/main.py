#!/usr/local/bin/python3
#
# main.py
# puzzle-assignment
#
# Created by Illya Starikov on 01/22/18.
# Copyright 2018. Illya Starikov. All rights reserved.
#

from functions import parse_arguments, parse_game_parameters, get_file_contents, generate_game_from_namespace


def main():
    filename, output_path = parse_arguments()
    game_parameters = parse_game_parameters(get_file_contents(filename))

    game = generate_game_from_namespace(game_parameters)


if __name__ == "__main__":
    main()
