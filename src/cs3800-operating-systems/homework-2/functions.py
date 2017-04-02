#
#  functions.py
#  CS3800 — Homework #2
#
#  Created by Illya Starikov on 01/04/2017
#  Copyright 2017. Illya Starikov. All rights reserved.
#

import sys

from page import *
from program import *

AVAILABLE_FRAME = 512

def printError(error):
    sys.stdout = sys.stderr
    print(error)
    sys.stdout = sys.stderr

# Thank you http://stackoverflow.com/questions/1265665/python-check-if-a-string-represents-an-int-without-using-try-except
def representsInt(s):
    try:
        int(s)
        return True
    except ValueError:
        return False

def parseArguments():
    # needs at least 5 parameters (see usage) and main.py
    if len(sys.argv) < 6:
        printError("Need a minimum of five arguments.")
        sys.exit(1)

    for argument in sys.argv:
        if "main" in argument:
            pass
        elif "program" in argument:
            programlist = argument
        elif "command" in argument:
            commandlist = argument
        elif representsInt(argument) and 0 <= int(argument) <= 8:
            pagesize = int(argument)
        elif argument in ["lru", "fifo", "clock"]:
            algorithm = argument
        elif argument in ["ondemand", "prepaging"]:
            paging = argument
        else:
            printError("Invalid Argument ({0})".format(argument))

    print("Program List: {0}\nCommand List: {1}\nPage Size: {2}\nAlgorithm: {3}\nPaging: {4}".format(programlist, commandlist, pagesize, algorithm, paging))

    return programlist, commandlist, pagesize, algorithm, paging

def readFromFile(filename):
    filehandler = open(filename)
    contents = []

    for line in filehandler:
       contents += [[int(i) for i in line.split()]]

    filehandler.close()
    return contents

def loadProgramList(programListContents, pageSize):
    pageCount = 0
    programs = []

    for identifier, numberOfPages in programListContents:
        programs += [Program(identifier, pageCount, numberOfPages/pageSize)]
        pageCount += numberOfPages/pageSize

    return programs

def loadMemory(programs):
    memory = [Page()]*AVAILABLE_FRAME

    memoryForEachProgram = int(AVAILABLE_FRAME / len(programs))

    for programIndex, program in enumerate(programs):
        size = 0

        if (program.numberOfPages > memoryForEachProgram):
            size = memoryForEachProgram
        else:
            size = program.numberOfPages

        for i in range(int(size)):
            mainMemory = programIndex*memoryForEachProgram + i
            virtualMemory = program.firstPage + i

            memory[mainMemory].updatePage(program, virtualMemory, 0)

    return memory

