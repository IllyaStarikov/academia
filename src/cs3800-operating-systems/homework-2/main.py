#
#  main.py
#  CS3801 — Homework #2
#
#  Created by Illya Starikov on 26/03/2017
#  Copyright 2017. Illya Starikov. All rights reserved.
#

# Usage: python3 main.py programlist commandlist pagesize algorithm --(prepaging|ondemand)
def main():
    programlist, commandlist, pagesize, algorithm, paging = parseArguments()
    programlistContents = readFromFile(programlist)
    commandlistContents = readFromFile(commandlist)
    print(programlist)

if __name__ == "__main__":
    main()
