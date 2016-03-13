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
            optimalSolution.append(smartphone[i])
            totalCost += smartphone[i].cost
            totalMemory += smartphone[i].memory
    
    return (optimalSolution, totalCost, totalMemory)

def GreedKnap(Phone, MemGoal):
    Solution = []
    Solution.append(Phone[0].number)
    FreeMem = Phone[0].memory
    FreeMem = Phone[0].cost
    i = 1
    while (FreeMem < MemGoal and i < len(Phone)):
        Solution.append(Phone[i].number)
        FreeMem += Phone[i].memory
        SolutionCost = Phone[i].cost
        i += 1
    Answer = (Solution, SolutionCost, FreeMem)
    return Answer

def PrintOut(Alg, inputsize, Answer, Time, MemGoal):
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

baseinput = 10, 25, 50
n=-1
# while (True):
n+=1
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

##        #Outputting array for testing purposes
##        for j in Smartphone:
##            print j, " "

    for i in range(10):
        t0 = time.clock()
        data = bruteForce(Smartphone, MemGoal)
        elapsed = time.clock() - t0
        Time.append(elapsed)
    averagetime = sum(Time)/len(Time)
    PrintOut(1, inputsize, data, averagetime, MemGoal)

    for i in range(10):
        t0 = time.clock()
        data = GreedKnap(Smartphone, MemGoal)
        elapsed = time.clock() - t0
        Time.append(elapsed)
    averagetime = sum(Time)/len(Time)
    PrintOut(3, inputsize, data, averagetime, MemGoal)
#    sys.exit("Finished") Illya's Debugging
    
