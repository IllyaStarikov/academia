from __future__ import division
import random
import math
import time

"""Stuff to do:
        implement loop to grow input size (math.pow(x,y))
        implement loop to add total memory of input
        MemGoal will be 20% of total memory (or higher)
        Create tuple with MemFreed, Cost, SolutionSet and return for Greedy
"""

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
    f = open('output.txt', 'a')
    f.write("Input size: {0}\tMemory to be Freed: {1}\n\n".format(inputsize, MemGoal))
    if (Alg == 1):
        f.write("Brute Force Solution:\n")
    elif (Alg == 2):
        f.write("Dynamic Programming Solution:\n")
    elif (Alg == 3):
        f.write("Greedy Solution:\n")
    f.write("""Solution Set: {0}\n
            Cost of Solution: {1} Freed Memory: {2}
            Average Time: {3}\n\n""".format(a, b, c, d))

def timed(f, x, y):
  start = time.time()
  ret = f(x, y)
  elapsed = time.time() - start
  return ret, elapsed
    
baseinput = 10, 25, 50
n=-1

while (True):
    n+=1
    for i in baseinput:
        inputsize = int(i*math.pow(10,n))
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
        Smartphone.sort(key=lambda x: x.ratio,)

        for i in range(10):
            t0 = time.clock()
            data = GreedKnap(Smartphone, MemGoal)
            elapsed = time.clock() - t0
            Time.append(elapsed)
        averagetime = sum(Time)/len(Time)
        #print "AvgTime:", averagetime
        PrintOut(3, inputsize, data, averagetime, MemGoal)
