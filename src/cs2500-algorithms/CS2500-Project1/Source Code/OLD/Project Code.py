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
    Answer = (DelTable[Goals][3], sumOf, DelTable[Goals][1]) 
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
