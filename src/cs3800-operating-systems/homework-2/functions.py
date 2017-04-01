#
#  program.py
#  CS3800 — Homework #2
#
#  Created by Illya Starikov on 01/04/2017
#  Copyright 2017. Illya Starikov. All rights reserved.
#

class Program:
    pageTable = {}

    def __init__(self, programNumber = None, numberOfPages = None, firstPage = None):
        if programNumber is None:
            self.programNumber = 0
        else:
            self.programNumber = programNumber

        if numberOfPages is None:
            self.numberOfPages = 0
        else:
            self.numberOfPages = numberOfPages

        if firstPage is None:
            self.firstPage = 0
        else:
            self.firstPage = firstPage

        for i in range(firstPage, numberOfPages + 1):
            pageTable[i] = -1


