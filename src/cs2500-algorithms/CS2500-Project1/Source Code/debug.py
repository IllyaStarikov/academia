from __future__ import division
import random
from math import pow
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
    numofApps = len(Apps)
    maxMem = 0
    for i in range(0,numofApps):
        maxMem += Apps[i].memory

    DelTable = [[0 for j in range(5)] for i in range(maxMem)]
    #label rows
    for j in range(0, maxMem):
        DelTable[j][0] = j

    for j in range(0, maxMem):
        DelTable[j][3] = []
        
    DelTable[0][0] = 0
    DelTable[0][1] = 0
    DelTable[0][2] = 0
    DelTable[0][4] = 0

    #base case
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

    #FIll up to the base case line
    illyaisawesome = int(round(BaseCase))
    for i in range(1, illyaisawesome):
        DelTable[i][1] = Apps[illyaisawesome].memory
        DelTable[i][2] = BaseCost # ILLYA CHANGED THIS
        DelTable[i][3].append(Apps[i].number)
        
    #Fill the rest of the table
    for j in range (illyaisawesome, maxMem):
        for i in range(0, numofApps):
            if(Apps[i].memory == j and Apps[i].cost < DelTable[j-1][2] + DelTable[illyaisawesome][2]):
                DelTable[j][1] = Apps[i].memory
                DelTable[j][2] = Apps[i].cost
                DelTable[j][3].append(Apps[i]) # ILLYA CHANGED THIS
                DelTable[j][4] = 0
            else:
                DelTable[j][1] = DelTable[j-1][1]+1
                PlaceHolder = j - BaseCost
                claireisawesome = int(round(PlaceHolder))
                Sum1 = DelTable[claireisawesome][2]
                Sum2 = DelTable[illyaisawesome][2]
                DelTable[j][2] = Sum1 + Sum2
                DelTable[j][3].append(Apps[i]) # ILLYA CHANGED THIS
                
    Goals = int(round(MemoryGoal))
    
    sumOf = 0 
    for app in DelTable[Goals][3]:
        sumOf += app.cost
        
#    DelTable[Goals][2]    
    Answer = DelTable 
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

def MakeArray(inputsize):
    Smartphone = []
    TotalMem = 0
    for i in range(inputsize):              #Creating 'array' of Apps
        Smartphone.append(App(i))
        Smartphone[i].getratio()
        TotalMem += Smartphone[i].memory
    MemGoal = TotalMem * .2
    #Sorting by ratio
    Smartphone.sort(key=lambda x: x.ratio)
    return Smartphone

def getMemGoal(array):
    goal = []
    for i in range(0,len(array)):
        goal.append(array[i].memory)
        memgoal = sum(goal)*.2
    return memgoal
