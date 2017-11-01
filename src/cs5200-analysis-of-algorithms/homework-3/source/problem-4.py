#!/usr/local/bin/python3
#
# main.py
# source
#
# Created by Illya Starikov on 09/17/17.
# Copyright 2017. Illya Starikov. All rights reserved.
#


def sum_solution(n):
    if n <= 1:
        return 1
    else:
        return (-1)**(n - 1) * n**3 + sum_solution(n - 1)


def explicit_solution(n):
    return -int(
        (1.0 / 8.0) *
        ((-1)**n) *
        (4 * n**3 + 6 * n**2 - 1) +
        1.0 / 8.0)


def main():
    for n in range(1,  0):
        print(sum_solution(n), explicit_solution(n), sum_solution(n) - explicit_solution(n))


if __name__ == "__main__":
    main()
