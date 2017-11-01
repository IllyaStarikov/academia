#!/usr/local/bin/python3
#
# main.py
# source
#
# Created by Illya Starikov on 09/17/17.
# Copyright 2017. Illya Starikov. All rights reserved.
#

from fractions import gcd
import random


def is_gcd(gcd_value, a, b):
    return gcd_value == gcd(a, b)


def is_gcd_fast(gcd_value, a, b):
    return a % gcd_value == b % gcd_value == 0


def main():
    for i in range(1000):
        a = random.randint(-1000000, 1000000)
        b = random.randint(-1000000, 1000000)
        g = gcd(a, b) if random.choice([True, False]) else random.randint(-1000000, 1000000)

        print(is_gcd_fast(g, a, b) == is_gcd(g, a, b))


if __name__ == "__main__":
    main()
