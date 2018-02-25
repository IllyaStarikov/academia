#!/usr/local/bin/python3
#
# direction.py
# testing
#
# Created by Illya Starikov on 01/24/18.
# Copyright 2018. Illya Starikov. All rights reserved.
#


from enum import Enum


class Direction(Enum):
    LEFT = 0,
    RIGHT = 1,
    UP = 2,
    DOWN = 3

    @property
    def unit_vector(self):
        """Create unit vector from current direction.

        Note:
            Although it's unit vector as in (x, y), it's actually a unit vector of (row, column).

        Returns:
            (int, int): The unit vector of the form (row, column) for the associated direction.
        """

        return {
            Direction.LEFT:  (0 , -1),  # noqa
            Direction.RIGHT: (0 ,  1),  # noqa
            Direction.UP:    (-1, 0),   # noqa
            Direction.DOWN:  (1 ,  0)   # noqa
        }[self]
