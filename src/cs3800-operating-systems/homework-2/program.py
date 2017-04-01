#
#  program.py
#  CS3800 — Homework #2
#
#  Created by Illya Starikov on 01/04/2017
#  Copyright 2017. Illya Starikov. All rights reserved.
#

class Program:
    pageTable = {}

    def __init__(self, ID = None, pageNumber = None, numberOfPages = None):

        if ID is None:
            self.ID = 0
        else:
            self.ID = ID

        if pageNumber is None:
            self.pageNumber = 0
        else:
            self.pageNumber = pageNumber

        if numberOfPages is None:
            self.numberOfPages = 0
        else:
            self.numberOfPages = numberOfPages

