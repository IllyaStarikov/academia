from math import pow

import App Class

def bruteForce(smartphone, memoryGoal):
    # Make the minimum the sum of all, just for an initial value
    for Apps in smartphone:
        minimum += cost

    # Iterate over the 2^n subsets
    for i in range(0, pow(2,len(smartphone))):
        subset = bin(i) # A binary representation of the binary

        totalMemory = 0
        totalCost = 0

        for i in range(len(subset)):
            totalMemory += smartphone[i].memory * ord(subset[i])
            totalCost += smartphone[i].weight * ord(subset[i])

        if totalMemory >= memoryGoal && totalCost < minumum
            minumum = totalCost
            greatestSubset = i

    subset = bin(greatestSubset)

    totalCost = 0
    totalMemory = 0

    for i in range(len(subset))
        if subset[i] == '1':
            optimalSolution.append(smartphone[i])
            totalCost += smartphone[i].cost
            totalMemory += smartphone[i].memory


    return (optimalSolution, totalCost, totalMemory)