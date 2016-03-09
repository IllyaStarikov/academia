from __future__ import division
import random

class App:
    memory = -1
    cost = -1
    ratio = -1
    number = -1
    def getratio(self):
        self.ratio = self.cost/self.memory  #Function to find ratio for greedy

    def __init__(self, num):                #Constructor for App
        self.memory = random.randrange(32, 1029)
        self.cost = self.memory * random.range(.2, .5)
        self.number = num                   #To make identifying Apps easier

def GreedKnap(Phone, Solution, MemGoal):
    Solution.append(Phone[0])
    FreeMem = Phone[0].memory
    i = 1
    while (FreeMem < MemGoal and i < len(Phone)):
        Solution.append(Phone[i])
        FreeMem += Phone[i].memory
        i += 1

def PrintOut(Array):
    for App in Array:
        print "App #{0}: Memory: {1} Cost: {2} Ratio: {3}".format(App.number, App.memory,
                                                                  App.cost, App.ratio)
baseinput = 10, 25, 50     

Smartphone = []
SolutionSet = []

inputsize = int(input("Enter an input size: "))
for i in range(inputsize):                  #Creating 'array' of Apps
    Smartphone.append(App(i))
    Smartphone[i].getratio()

#Sorting by ratio                                                              
Smartphone.sort(key=lambda x: x.ratio,)

MemGoal = int(input("Enter a desired amount of memory to free: "))
GreedKnap(Smartphone, SolutionSet, MemGoal)
PrintOut(SolutionSet)
