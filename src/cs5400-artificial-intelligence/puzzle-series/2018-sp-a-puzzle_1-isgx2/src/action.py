#!/usr/local/bin/python3
#
# action.py
# puzzle-assignment
#
# Created by Illya Starikov on 01/25/18.
# Copyright 2018. Illya Starikov. All rights reserved.
#


class Action():
    def __init__(self, row_column_pair, direction):
        """Generate an action, described by a row_column_pair and a direction"""
        self.row_column_pair = row_column_pair
        self.direction = direction

    def __eq__(self, other):
        """Standard equality operator overload."""
        as_unit_vector = other.direction.unit_vector

        return self.row_column_pair[0] == (other.row_column_pair[0] + as_unit_vector[0]) and self.row_column_pair[1] == (other.row_column_pair[1] + as_unit_vector[1])
