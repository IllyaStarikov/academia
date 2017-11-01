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
        numerator = ((-1)**(x - 1)) * x**2
        return numerator

    sum_ = 0
    for i in range(1, n + 1):
        sum_ += f(i)

    return sum_


def explicit_solution(n):
    numerator = ((-1)**(n - 1)) * float(n* (n + 1)) / 2.0
    return numerator


max_diff = 1.0
for i in range(1, 40):
    sum_ = sum_solution(i)
    explicit = explicit_solution(i)

    print("%15.10f & %15.10f & %0.15f \\\\" % (
        sum_,
        explicit,
        (i * (i + 1))//2.0)
    )
