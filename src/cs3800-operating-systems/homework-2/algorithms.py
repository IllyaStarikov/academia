#
#  main.py
#  CS3801 — Homework #2
#
#  Created by Illya Starikov on 02/04/2017
#  Copyright 2017. Illya Starikov. All rights reserved.
#

from functions import *

# clock default is a static variable to keep track of clock pointer
def clockPageReplacement(memory, pageSize, __clockPointer=[0]):
    while True:
        if __clockPointer[0] >= AVAILABLE_FRAME/pageSize:
            __clockPointer[0] = 0

        if memory[__clockPointer[0]].clock:
            memory[__clockPointer[0]].clock = False
        else:
            selector = __clockPointer[0]
            break

        __clockPointer[0] += 1

    __clockPointer[0] += 1
    return selector

