#
#  functions.py
#  CS3800 — Homework #2
#
#  Created by Illya Starikov on 01/04/2017
#  Copyright 2017. Illya Starikov. All rights reserved.
#

from program import *

class Page(object):
    __nextID = 0

    def __init__(self):
        # Assign subsequent ID
        self.__ID = Page.__nextID
        Page.__nextID += 1

        self.loadedCount = self.accessedCount = self.content = 1
        self.owner = None
        self.clock = False

    def updatePage(self, program, word, PC):
        if self.owner is not None:
            self.owner.pageTable[self.content] = -1

        self.owner = program
        program.pageTable[word] = self.__ID

        self.content = word
        self.loadedCount = PC
        self.accessedCount = PC

        self.clock = True

    def access(self, PC):
        self.accessedCount = PC
        self.clock = True

