#!/usr/bin/python
class MontyHallGame:
	numberOfDoors = 0
	numberOfGamesToSimulate = 0
	doorStack = {}
	
	def __init__(self):
		numberOfDoors = input("Number of Doors: ")
		numberOfGamesToSimulate = input("Number of Games To Simulate: ") 
		doorStack[numberOfDoors] = 'x'
		
		
game = MontyHallGame()
