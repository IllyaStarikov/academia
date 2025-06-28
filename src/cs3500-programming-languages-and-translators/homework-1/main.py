#!/usr/local/bin/python3
#
# main.py
# homework-1
#
# Created by Illya Starikov on 02/07/18.
# Copyright 2018. Illya Starikov. All rights reserved.
#

import string  # only to be used for the lowercase/uppercase letters generation
from enum import Enum


class State(Enum):
    START_STATE = 0
    FAIL = 1
    PLUS_MINUS = 2
    HEX_WITHOUT_H = 3
    HEX_WITHOUT_H_IDENTIFIER = 12
    IDENTIFIER = 4
    INTEGER = 5
    HEX = 6
    DECIMAL_WITHOUT_NUMBER_AFTER_PERIOD = 7
    DECIMAL = 8
    SCIENTIFIC_WITHOUT_ENDING = 9
    SCIENTIFIC_WITH_PM = 10
    SCIENTIFIC = 11


def parse_input():
    number_of_lines = int(input())
    tokens = [input() for _ in range(number_of_lines)]

    return number_of_lines, tokens


def output_solution(number_of_lines, tokens):
    print(number_of_lines)

    for index, token in enumerate(tokens):
        print("{}: {}".format(index + 1, token))


def short_circuit_keywords(token):
    if token in ['while', 'else', 'if', 'print']:
        return 'Keyword.'


def short_circuit_phone_numbers(token):
    integers = [str(integer) for integer in range(10)]

    if len(token.replace(' ', '')) == 13 and token[0] == '(':
        format_ = ['(', integers, integers, integers, ')', integers, integers, integers, '-', integers, integers, integers, integers]

        for (character, format_element) in zip(token.replace(' ', ''), format_):
            if character not in format_element and character != format_element:
                return 'INVALID!'

        return 'Phone.'


def parse_token(token):
    integers = [str(integer) for integer in range(10)]
    non_zero_integers = [str(integer) for integer in range(1, 10)]

    letters = list(string.ascii_letters)
    hex_letters = [chr(i) for i in range(ord('a'), ord('f') + 1)] + [chr(i) for i in range(ord('A'), ord('F') + 1)]
    non_hex_letters = [chr(i) for i in range(ord('g'), ord('z') + 1)] + [chr(i) for i in range(ord('G'), ord('Z') + 1)]
    hex_delimiter = ['h', 'H']

    plus_minus = ['-', '+']
    dashes = ['-', '–', '—']  # these are all different types of dashes

    if short_circuit_keywords(token):
        return short_circuit_keywords(token)

    if short_circuit_phone_numbers(token):
        return short_circuit_phone_numbers(token)

    current_state = State.START_STATE

    for character in token:
        if current_state is State.START_STATE:
            if character in plus_minus:
                current_state = State.PLUS_MINUS
            elif character in integers:
                current_state = State.INTEGER
            elif character in hex_letters:
                current_state = State.HEX_WITHOUT_H_IDENTIFIER
            elif character in non_hex_letters:
                current_state = State.IDENTIFIER
            else:
                current_state = State.FAIL

        elif current_state is State.HEX_WITHOUT_H_IDENTIFIER:
            if character in hex_delimiter:
                current_state = State.HEX
            elif character in integers or character in hex_letters:
                current_state = State.HEX_WITHOUT_H_IDENTIFIER
            elif character in integers or character in letters or character in dashes:
                current_state = State.IDENTIFIER
            else:
                current_state = State.FAIL

        elif current_state is State.PLUS_MINUS:
            if character in integers:
                current_state = State.INTEGER
            elif character in hex_letters:
                current_state = State.HEX_WITHOUT_H
            else:
                current_state = State.FAIL

        elif current_state is State.HEX_WITHOUT_H:
            if character in hex_delimiter:
                current_state = State.HEX
            elif character in integers or character in hex_letters:
                current_state = State.HEX_WITHOUT_H
            else:
                current_state = State.FAIL

        elif current_state is State.IDENTIFIER:
            if character in integers or character in letters or character in dashes:
                current_state = State.IDENTIFIER
            else:
                current_state = State.FAIL

        elif current_state is State.INTEGER:
            if character in integers:
                current_state = State.INTEGER
            elif character is '.':
                current_state = State.DECIMAL_WITHOUT_NUMBER_AFTER_PERIOD
            elif character in hex_letters:
                current_state = State.HEX_WITHOUT_H
            else:
                current_state = State.FAIL

        elif current_state is State.DECIMAL_WITHOUT_NUMBER_AFTER_PERIOD:
            if character in integers:
                current_state = State.DECIMAL
            else:
                current_state = State.FAIL

        elif current_state is State.DECIMAL:
            if character in integers:
                current_state = State.DECIMAL
            elif character is 'E':
                current_state = State.SCIENTIFIC_WITHOUT_ENDING
            else:
                current_state = State.FAIL

        elif current_state is State.SCIENTIFIC_WITHOUT_ENDING:
            if character in non_zero_integers:
                current_state = State.SCIENTIFIC
            elif character in dashes:
                current_state = State.SCIENTIFIC_WITH_PM
            else:
                current_state = State.FAIL

        elif current_state is State.SCIENTIFIC_WITH_PM:
            if character in non_zero_integers:
                current_state = State.SCIENTIFIC
            else:
                current_state = State.FAIL

        elif current_state is State.SCIENTIFIC:
            if character in integers:
                current_state = State.SCIENTIFIC
            else:
                current_state = State.FAIL

        else:
            return 'INVALID!'

    return {
        State.START_STATE:                         'INVALID!',
        State.FAIL:                                'INVALID!',
        State.PLUS_MINUS:                          'INVALID!',
        State.HEX_WITHOUT_H:                       'INVALID!',
        State.HEX_WITHOUT_H_IDENTIFIER:            'Identifier.',
        State.IDENTIFIER:                          'Identifier.',
        State.INTEGER:                             'Integer.',
        State.HEX:                                 'Hexadecimal.',
        State.DECIMAL_WITHOUT_NUMBER_AFTER_PERIOD: 'INVALID!',
        State.DECIMAL:                             'Decimal.',
        State.SCIENTIFIC_WITHOUT_ENDING:           'INVALID!',
        State.SCIENTIFIC_WITH_PM:                  'INVALID!',
        State.SCIENTIFIC:                          'Scientific.'
    }[current_state]


def main():
    number_of_lines, tokens = parse_input()
    parsed_tokens = []

    for token in tokens:
        parsed_tokens += [parse_token(token)]

    output_solution(number_of_lines, parsed_tokens)


if __name__ == "__main__":
    main()
