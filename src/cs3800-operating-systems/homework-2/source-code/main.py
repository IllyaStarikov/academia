#!/usr/bin/env python3

#
#  main.py
#  CS3801 — Homework #2
#
#  Created by Illya Starikov on 26/03/2017
#  Copyright 2017. Illya Starikov. All rights reserved.
#

from functions import *
from algorithms import *

# Usage: python3 main.py programlist commandlist pagesize algorithm --(prepaging|ondemand)
def main():
    programList, commandList, pageSize, algorithmName, pagingString = parseArguments()
    programListContents = readFromFile(programList)
    commandListContents = readFromFile(commandList)

    programs = loadProgramList(programListContents, pageSize)
    memory = loadMemory(programs, pageSize)

    algorithm = determineAlgorithm(algorithmName)
    if algorithm == "None":
        printError("You fucking broke my program")

    prepaging = determinePaging(pagingString)
    numberOfFaults = runSimulation(algorithm, commandListContents, pageSize, programs, memory, prepaging)

    print("Number of Faults: {0}".format(numberOfFaults))

if __name__ == "__main__":
    main()
