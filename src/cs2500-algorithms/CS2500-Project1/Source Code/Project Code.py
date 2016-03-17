from __future__ import division
import random
from math import pow
from math import ceil
import time

# Illya's Debugging
import sys
from pprint import pprint

class App:
    memory = -1
    cost = -1
    ratio = -1
    number = -1

    def getratio(self):
        self.ratio = self.cost/self.memory  #Function to find ratio for greedy

    def __init__(self, num):                #Constructor for App
        self.memory = random.randrange(32, 1029)
        self.cost = self.memory * random.uniform(.2, .5)
        self.number = num                   #To make identifying Apps easier

    def __str__(self):
        rep = "#{0}  Memory: {1}  Cost: {2}".format(self.number, self.memory, self.cost)
        return rep

def bruteForce(smartphone, memoryGoal):
    # Make the minimum the sum of all, just for an initial value
    minimum = 0
    greatestSubset = 0

    for App in smartphone:
        minimum += App.cost

    # Iterate over the 2^n subsets
    for i in range(0, int(pow(2,len(smartphone)))):
        binaryRepresenation = bin(i) # A binary representation of the binary
        subset = binaryRepresenation.replace("0b", "") #bin returns 0b..., so this returns ..
        totalMemory = 0
        totalCost = 0

        for j in range(len(subset)):
            if subset[j] == '1':
                totalMemory += smartphone[j].memory #* ord(subset[i])
                totalCost += smartphone[j].cost #* ord(subset[i])

        if totalMemory >= memoryGoal and totalCost < minimum:
            minimum = totalCost
            greatestSubset = i

    binaryRepresenation =  bin(greatestSubset)
    subset = binaryRepresenation.replace("0b", "")
    totalCost = 0
    totalMemory = 0
    optimalSolution = []

    for i in range(len(subset)):
        if subset[i] == '1':
            optimalSolution.append(smartphone[i].number)
            totalCost += smartphone[i].cost
            totalMemory += smartphone[i].memory

    return (optimalSolution, totalCost, totalMemory)



#numofApps = number of applications open
#MemoryGoal = amount of memeory needed to free up

#maxMem = maximum memory of the device

def DelTable(Apps, MemoryGoal):

    numofApps = len(Apps) #This is the number of apps we have open 
    maxMem = 0
    for i in range(0,numofApps):
        maxMem += Apps[i].memory #this calculates the maximum memory we could be asked to clear 

    DelTable = [[0 for j in range(5)] for i in range(maxMem)] #This creates a table for reference 
    #Columns are: Memory to Delete | Apps Used | Total Memory Deleted | Total Cost | Over flow  

    #Set Up Table 
    #Column 0: Label Rows 0 - maxMem for easy reference 
    for j in range(0, maxMem):
        DelTable[j][0] = j

    #Column 1: Set the Apps Used list to empty 
    for j in range(0, maxMem):
        DelTable[j][1] = []

    #Column 2: Set the Total Mem to 0 
    for j in range(0, maxMem):
        DelTable[j][2] = 0

    #Column 3: Set the Total Cost to 0 
    for j in range(0, maxMem):
        DelTable[j][3] = 0

    #Column 4: Set the overflow to Opposite of memory   
    for j in range(0, maxMem):
        DelTable[j][4] = -DelTable[j][0]
    
    #Base Case
    #Asssume the first app has the smallest memory and the lowest cost 
    BaseCase = Apps[0].number
    BaseMem = Apps[0].memory
    BaseCost = Apps[0].cost

    #Check against every other app in the list 
    for i in range (0,numofApps):
        if(Apps[i].memory <= BaseMem):
            if(Apps[i].cost < BaseCost):
                BaseCost = round(Apps[i].cost)
                BaseMem = round(Apps[i].memory)
                BaseCase = round(Apps[i].number)
    #Base Case now holds the app with the lowest memory and the lowest cost 

    #Fill in Base Case Line first 
    intBaseCase = int(round(BaseCase)) #Because apparently sometimes it's a float... *shrug*
    DelTable[intBaseCase][1].append(Apps[intBaseCase].number)  
    DelTable[intBaseCase][2] = Apps[intBaseCase].memory
    DelTable[intBaseCase][3] = Apps[intBaseCase].cost 
    DelTable[intBaseCase][4] = 0 #No over flow becuase it is exact

    #FIll up to the base case line
    for i in range(1, intBaseCase): #Start at 1 because 0 will be empty
        DelTable[i][1].append(Apps[intBaseCase].number)
        DelTable[i][2] = Apps[intBaseCase].memory
        DelTable[i][3] = Apps[intBaseCase].cost
        DelTable[i][4] = Apps[intBaseCase].memory - i #To calculate how much larger the Base Case memory is from the memory we're asked to delete 

    #Fill the rest of the table
    for j in range (intBaseCase, maxMem):
        #First, search the existing apps for one with that cost 
        for i in range (0, numofApps):
            if Apps[i].memory == DelTable[j][0]: 
                if DelTable[j][3] == 0: #If this is the first app with this memory size found 
                    DelTable[j][1].append(Apps[i].number)
                    DelTable[j][2] = Apps[i].memory
                    DelTable[j][3] = Apps[i].cost 
                    DelTable[j][4] = 0 #Because it is an exact match 
                else: 
                    if Apps[i].cost < DelTable[j][3]: #If the cost of the new app is samller, replace the data
                        DelTable[j][1] = [] #Clear Table 
                        DelTable[j][1].append(Apps[intBaseCase].number)
                        DelTable[j][2] = Apps[i].memory
                        DelTable[j][3] = Apps[i].cost
                        DelTable[j][4] = 0 #Because it is an exact match 
        #If no exact match can be found, use the base case 
        while (DelTable[j][4] < 0): #This will keep going until a set of apps deletes enough memory 
            if DelTable[j][2] == 0 and i not in DelTable[j][1]:
                #Insert Base Case 
                DelTable[j][1].append(Apps[intBaseCase].number)
                DelTable[j][2] = Apps[intBaseCase].memory
                DelTable[j][3] = Apps[intBaseCase].cost
                DelTable[j][4] += Apps[intBaseCase].memory

                #Look for another app to finish it up 
            for i in range (0, numofApps): 
                if (Apps[i].memory >= DelTable[j][4]) and i not in DelTable[j][1]: #This probably won't get the optimal solution, but it should make it work enough for testing... 
                    DelTable[j][1].append(Apps[i].number)
                    DelTable[j][2] += Apps[i].memory
                    DelTable[j][3] += Apps[i].cost
                    DelTable[j][4] += Apps[i].memory

    Goals = int(round(MemoryGoal))
    
    Answer = (DelTable[Goals][1], DelTable[Goals][3], DelTable[Goals][2]) 

    return Answer

def GreedKnap(Phone, MemGoal):

    Solution = []
    Solution.append(Phone[0].number)
    FreeMem = Phone[0].memory
    SolutionCost = Phone[0].cost
    i = 1

    while (FreeMem < MemGoal and i < len(Phone)):
        Solution.append(Phone[i].number)
        FreeMem += Phone[i].memory
        SolutionCost += Phone[i].cost
        i += 1
    Answer = (Solution, SolutionCost, FreeMem)
    return Answer

def PrintOut(Alg, inputsize, Answer, Time, MemGoal):

    if isinstance(Answer[0][0], App):
        thingy=[]
        for i in range(0, len(Answer[0])):
            thingy.append(Answer[0][i].number)
        a = str(thingy)
    else:
        a = str(Answer[0])

    b = str(Answer[1])
    c = str(Answer[2])
    d = str(Time)

    g = open('SolutionSets.txt', 'a')   #Writing Solution Sets to file
    g.write("Input size: {0}\n".format(inputsize))

    if (Alg == 1):
        g.write("Brute Force Solution:\n")
    elif (Alg == 2):
        g.write("Dynamic Programming Solution:\n")
    elif (Alg == 3):
        g.write("Greedy Solution:\n")

    g.write("{}\n".format(a))
    g.close()

    f = open('output.txt', 'a')         #Writing data to file
    f.write("Input size: {0}\tMemory to be Freed: {1}\n\n".format(inputsize, MemGoal))
    if (Alg == 1):
        f.write("Brute Force Solution:\n")
    elif (Alg == 2):
        f.write("Dynamic Programming Solution:\n")
    elif (Alg == 3):
        f.write("Greedy Solution:\n")
    f.write("Cost of Solution: {0} Freed Memory: {1} Average Time: {2}\n\n".format(b, c, d))
    f.close()

baseinput = 5, 10, 15, 25
n=-1
while (True):
    n += 1
    for i in baseinput:
        inputsize = int(i*pow(10,n))
        print "Input size:", inputsize
        Smartphone = []
        Time = []
        TotalMem = 0
        for i in range(inputsize):              #Creating 'array' of Apps
            Smartphone.append(App(i))
            Smartphone[i].getratio()
            TotalMem += Smartphone[i].memory
        MemGoal = TotalMem * .2

    #Sorting by ratio
        Smartphone.sort(key=lambda x: x.ratio)
        if (inputsize < 50):
            for i in range(10):
                t0 = time.clock()
                data = bruteForce(Smartphone, MemGoal)
                elapsed = time.clock() - t0
                Time.append(elapsed)
            averagetime = sum(Time)/len(Time)
            PrintOut(1, inputsize, data, averagetime, MemGoal)

        for i in range(10):
            t0 = time.clock()
            data = DelTable(Smartphone, MemGoal)
            elapsed = time.clock() - t0
            Time.append(elapsed)
        averagetime = sum(Time)/len(Time)
        PrintOut(2, inputsize, data, averagetime, MemGoal)

        for i in range(10):
            t0 = time.clock()
            data = GreedKnap(Smartphone, MemGoal)
            elapsed = time.clock() - t0
            Time.append(elapsed)
        averagetime = sum(Time)/len(Time)
        PrintOut(3, inputsize, data, averagetime, MemGoal)
