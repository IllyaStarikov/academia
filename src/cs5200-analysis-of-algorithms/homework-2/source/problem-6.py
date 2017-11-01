#!/usr/local/bin/python3
#
# main.py
# source
#
# Created by Illya Starikov on 09/11/17.
# Copyright 2017. Illya Starikov. All rights reserved.
#


def depth(n):
    if n < 2:
        return 1
    if n % 2 == 1:
        return 1 + depth(3 * n + 1)
    else:
        return 1 + depth(n // 2)


def main():
    for i in range(101):
        print("%3.0f & %5.0f\\\\" % (i, depth(i)))


if __name__ == "__main__":
    main()
