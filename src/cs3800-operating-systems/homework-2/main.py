#
#  main.py
#  CS3800 — Homework #2
#
#  Created by Illya Starikov on 26/03/2017
#  Copyright 2017. Illya Starikov. All rights reserved.
#

import sys

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
            pagesize = argument
        elif argument in ["lru", "fifo", "clock"]:
            algorithm = argument
        elif argument in ["ondemand", "prepaging"]:
            paging = argument
        else:
            printError("Invalid Argument")

    print("Program List: {0}\nCommand List: {1}\nPage Size: {2}\nAlgorithm: {3}\nPaging: {4}".format(programlist, commandlist, pagesize, algorithm, paging))

    return programlist, commandlist, pagesize, algorithm, paging


# Usage: python3 main.py programlist commandlist pagesize algorithm --(prepaging|ondemand)
def main():
    programlist, commandlist, pagesize, algorithm, paging = parseArguments()

if __name__ == "__main__":
    main()
