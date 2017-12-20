#!/usr/local/bin/python3
#
# problem-3.py
# source
#
# Created by Illya Starikov on 12/15/17.
# Copyright 2017. Illya Starikov. All rights reserved.
#


def q(n):
    if n <= 0:
        return 1
    elif n < 2:
        return 7
    else:
        return q(n - 1) + q(n - 2)


def sq(n):
    if n < 0:
        return 0
    else:
        return sq(n - 1) + q(n)


def main():
    print("{: <5} {: <5} {: <5}".format("q(n)", "sq(n)", "q(n+2)-7"))
    for n in range(15):
        print("{: <5}, {: <5}, {: <5}".format(q(n), sq(n), q(n + 2) - 7))


if __name__ == "__main__":
    main()
