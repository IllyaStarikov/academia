#
#  program.py
#  CS3800 — Homework #2
#
#  Created by Illya Starikov on 01/04/2017
#  Copyright 2017. Illya Starikov. All rights reserved.
#

class Program:
    def __init__(self, ID = None, firstPage = None, numberOfPages = None):

        if ID is None:
            self.ID = 0
        else:
            self.ID = ID

        if firstPage is None:
            self.firstPage = 0
        else:
            self.firstPage = firstPage

        if numberOfPages is None:
            self.numberOfPages = 0
        else:
            self.numberOfPages = numberOfPages

        self.pageTable = {}

        for i in range(int(self.firstPage), int(self.firstPage + self.numberOfPages)):
            self.pageTable[i] = -1

