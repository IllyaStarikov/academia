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
        self.memory = random.randrange(32, 129)
        self.cost = self.memory // 5
        self.number = num                   #To make identifying Apps easier

def PrintOut(Array):
    for App in Array:
        print "App #{0}: Memory: {1} Cost: {2} Ratio: {3}".format(App.number, App.memory,
                                                                  App.cost, App.ratio)

Smartphone = []
SolutionSet = []
inputsize = int(input("Enter an input size: "))
for i in range(inputsize):                  #Creating 'array' of Apps
    Smartphone.append(App(i))
    Smartphone[i].getratio()

#Printing the array
PrintOut(Smartphone)
#Sorting by ratio                                                              
Smartphone.sort(key=lambda x: x.ratio,)

#Printing again for check
print "\nNew Array: "
PrintOut(Smartphone)