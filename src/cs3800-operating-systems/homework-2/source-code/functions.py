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
from algorithms import *

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


def isPowerOfTwo(number):
    return number != 0 and ((number & (number - 1)) == 0)


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
        elif representsInt(argument):
            if not isPowerOfTwo(int(argument)):
                printError("Page size must be a power of two (Page Size: {0}".format(argument))
            elif not 1 <= int(argument) <= 16:
                printError("Page size not in bound (1 <= {0} <= 16)".format(argument))
            else:
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
        programs += [Program(identifier, pageCount, numberOfPages//pageSize)]
        pageCount += numberOfPages//pageSize

    return programs


def loadMemory(programs, pageSize):
    memory = [Page()]*AVAILABLE_FRAME
    memoryForEachProgram = AVAILABLE_FRAME // len(programs) // pageSize

    for programIndex, program in enumerate(programs):
        size = 0

        if program.numberOfPages > memoryForEachProgram:
            size = memoryForEachProgram
        else:
            size = program.numberOfPages

        for i in range(int(size)):
            mainMemory = programIndex*memoryForEachProgram + i
            virtualMemory = program.firstPage + i

            memory[mainMemory].updatePage(program, virtualMemory, 0)

    return memory


def determineAlgorithm(algorithm):
    return {
            "clock": clockPageReplacement,
            "lru": leastRecentlyUsedPageReplacement,
            "fifo": firstInFirstOutPageReplacement,
    }[algorithm]


def determinePaging(string):
    return True if string == "prepaging" else False


def runSimulation(algorithm, commandList, pageSize, programs, memory, prepaging):
    numberOfFaults = 0

    for index, (programNumber, word) in enumerate(commandList):
        numberOfFaults += accessMemory(programNumber, word, programs, pageSize, algorithm, memory, index, prepaging)

    return numberOfFaults


def accessMemory(programIndex, word, programs, pageSize, algorithm, memory, PC, prepaging):
    program = programs[programIndex]
    pageFaults = 0

    if programIndex > len(programs):
        printError("Program requested ({0}) is greater than total number of programs ({1})".format(programNumber, programs))
        return pageFaults

    # Convert relative to absolute page number
    word = word // pageSize + program.firstPage

    programTotalPageRange = program.firstPage + program.numberOfPages
    if word > max(program.pageTable) or word < min(program.pageTable):
        printError("Word {0} is not in page range ({1}...{2})".format(word, program.firstPage, programTotalPageRange))
        return pageFaults

    if program.pageTable[word] == -1:
        pageFaults += 1
        handleFault(algorithm, memory, program, word, PC, pageSize, prepaging)
    else:
        memory[program.pageTable[word]].access(PC)

    return pageFaults


def handleFault(algorithm, memory, program, word, PC, pageSize, prepaging):
    selector = algorithm(memory, pageSize)
    memory[selector].updatePage(program, word, PC)

    if prepaging:
        if word == program.firstPage + program.numberOfPages - 1:
            word = program.firstPage
        else:
            word += 1

        if program.pageTable[word] != -1:
            return

        handleFault(algorithm, memory, program, word, PC, pageSize, False)
