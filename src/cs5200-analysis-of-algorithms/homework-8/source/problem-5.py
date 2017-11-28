#!/usr/local/bin/python3
#
# problem-5.py
# source
#
# Created by Illya Starikov on 11/24/17.
# Copyright 2017. Illya Starikov. All rights reserved.
#

from random import sample
from math import log2, ceil


def static_vars(**kwargs):
    def decorate(func):
        for k in kwargs:
            setattr(func, k, kwargs[k])
        return func
    return decorate


def pairwise(iterable):
    """s -> (s0, s1), (s2, s3), (s4, s5), ..."""

    a = iter(iterable)
    return list(zip(a, a))


@static_vars(comparison_counter=0)
def find_smallest_value(iterable, pairwised=False):

    if iterable != []:
        if pairwised is False:
            iterabale_pairwise = pairwise(iterable)
        else:
            iterabale_pairwise = iterable

        minimum = iterabale_pairwise.pop(0)

        for element in iterabale_pairwise:
            find_smallest_value.comparison_counter += 1

            if min(element) < min(minimum):
                minimum = element

        return min(minimum), max(minimum), [x for x in iterable if x not in minimum], find_smallest_value.comparison_counter

    return None, None, None, None


def find_second_smallest_element(iterable):
    """Returns second smallest of two inputs"""
    smallest, pair_of_smallest, new_iterable, _ = find_smallest_value(iterable)
    smallest_second_iteration, _, _, comparison_counter = find_smallest_value(new_iterable)

    second_smallest = pair_of_smallest if smallest_second_iteration is None else min(pair_of_smallest, smallest_second_iteration)
    return second_smallest, comparison_counter


def generate_input(of_length):
    """Generates random input for problem #7. Returns (iterable, second_smallest_element)"""
    input_ = sample(range(of_length * 100), of_length)

    smallest = min(input_)
    second_smallest = min([x for x in input_ if smallest != x])

    return input_, second_smallest


def main():
    length_of_input = 10

    input_iterable, second_smallest_from_input = generate_input(length_of_input)
    second_smallest, comparisons = find_second_smallest_element(input_iterable)
    print("Input: {}".format(input_iterable))

    print("Length: {}\nElements {} = {} => {}\nNumber of Comparisons ({}) <= n + lg(n) - 2 ({}) => {}".format(
        length_of_input,
        second_smallest_from_input, second_smallest, second_smallest_from_input == second_smallest,
        comparisons, length_of_input + ceil(log2(length_of_input)) - 2, (comparisons <= length_of_input + ceil(log2(length_of_input)) - 2)
        ))


if __name__ == "__main__":
    main()
