#!/usr/local/bin/python3
#
# problem-9.py
# source
#
# Created by Illya Starikov on 11/27/17.
# Copyright 2017. Illya Starikov. All rights reserved.
#

import random


def vertex_cover(adjacency_matrix):
    if sum([item for sublist in adjacency_matrix for item in sublist]) != 0:
        random_verties = random.sample(range(len(adjacency_matrix[0])), 2)

        for i in range(len(adjacency_matrix[0])):
            adjacency_matrix[i][random_verties[0]] = 0
            adjacency_matrix[random_verties[0]][i] = 0

            adjacency_matrix[i][random_verties[1]] = 0
            adjacency_matrix[random_verties[1]][i] = 0

        return vertex_cover(adjacency_matrix).union(set(random_verties))

    else:
        return set()


def main():
    matrix = [[0, 0, 1, 0, 1],
              [1, 0, 0, 1, 0],
              [0, 1, 0, 0, 1],
              [1, 0, 1, 0, 0],
              [1, 0, 0, 0, 1]]

    print(vertex_cover(matrix))


if __name__ == "__main__":
    main()
