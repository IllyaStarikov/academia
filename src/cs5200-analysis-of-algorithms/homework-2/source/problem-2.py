#!/usr/local/bin/python3
#
# homework-1.py
# source
#
# Created by Illya Starikov on 09/05/17.
# Copyright 2017. Illya Starikov. All rights reserved.
#


def sum_solution(n):
    def f(x):
        numerator = float(x**2)
        denominator = float((2 * x - 1) * (2 * x + 1))

        return numerator / denominator

    sum_ = 0
    for i in range(1, n + 1):
        sum_ += f(i)

    return sum_


def explicit_solution(n):
    numerator = float(n * (n + 1))
    denominator = float(2 * (2 * n + 1))
    return numerator / denominator


max_diff = 1.0
for i in range(1, 1000):
    sum_ = sum_solution(i)
    explicit = explicit_solution(i)

    print("%15.12f & %15.12f & %0.15f \\\\" % (
        sum_,
        explicit,
        abs(sum_ - explicit))
    )
