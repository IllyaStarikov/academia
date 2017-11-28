#!/usr/local/bin/python3
#
# problem-8-1.py
# source
#
# Created by Illya Starikov on 11/26/17.
# Copyright 2017. Illya Starikov. All rights reserved.
#


def all_combinations(list_one, list_two):
    """Returns all two-element combinations of both lists"""

    all_combinations = []
    for element_one in list_one:
        for element_two in list_two:
            all_combinations += [[element_one, element_two]]

    return all_combinations


def bonnie_and_clyde(x_worth, y_worth, x_amount, y_amount):
    """Literally a brute force solution"""
    all_combinations_of_x_y = all_combinations(range(x_amount), range(y_amount))

    for candidate_x, candidate_y in all_combinations_of_x_y:
        if (candidate_x * x_worth + candidate_y * y_worth) == (x_worth * (x_amount - candidate_x) + y_worth * (y_amount - candidate_y)):
            return (True, candidate_x, candidate_y)

    return (False, None, None)


def main():
    # Impossible Case
    x_worth, y_worth = 100, 7
    x_amount, y_amount = 1, 2

    print(bonnie_and_clyde(x_worth, y_worth, x_amount, y_amount))

    # Possible Case (Literally one of each)
    x_worth, y_worth = 100, 7
    x_amount, y_amount = 2, 2

    print(bonnie_and_clyde(x_worth, y_worth, x_amount, y_amount))

if __name__ == "__main__":
    main()
