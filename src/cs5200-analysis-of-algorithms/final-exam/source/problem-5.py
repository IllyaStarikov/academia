#!/usr/local/bin/python3
#
# problem-5.py
# final-exam
#
# Created by Illya Starikov on 12/13/17.
# Copyright 2017. Illya Starikov. All rights reserved.
#


def static_vars(**kwargs):
    def decorate(func):
        for k in kwargs:
            setattr(func, k, kwargs[k])
        return func
    return decorate


@static_vars(values=[])
def G(n):
    if n > len(G.values) - 1:
        G.values += [None] * (n - len(G.values) + 1)

    if G.values[n] is not None:
        return G.values[n]

    if n == 0:
        return 5
    elif n == 1:
        return 15
    elif n == 2:
        return 40
    elif n > 2:
        G.values[n] = G(n - 1) + G(n - 2) + G(n - 3)
        return G.values[n]


@static_vars(values=[])
def H(n):
    if n > len(H.values) - 1:
        H.values += [None] * (n - len(H.values) + 1)

    if H.values[n] is not None:
        return H.values[n]

    if n == 0:
        return 6
    elif n == 1:
        return 7
    elif n == 2:
        return 8
    elif n > 2:
        H.values[n] = H(n - 1) - H(n - 2) + H(n - 3)
        return H.values[n]


def H_fast(n):
    if n % 2 != 0:
        return 7
    elif (n - 2) % 4 == 0:
        return 8
    elif n % 4 == 0:
        return 6


def main():
    n = 500

    print("G({}) = {}".format(n, G(n)))
    print("H({}) = {}".format(n, H(n)))
    print("H_fast({}) = {}".format(n, H_fast(n)))


if __name__ == "__main__":
    main()
