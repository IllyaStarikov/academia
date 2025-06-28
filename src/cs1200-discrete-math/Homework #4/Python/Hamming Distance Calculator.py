#!/usr/bin/python
from types import IntType

def integerToBinary( integerToConvert ):
	if integerToConvert == 0: return "0"
	binaryConversion = ''
		
	while integerToConvert != 0:
		if integerToConvert % 2 == 1:
			binaryConversion = "1" + binaryConversion
		else:
			binaryConversion = "0" + binaryConversion
		integerToConvert /= 2
	return binaryConversion

def binaryToGray( binaryToConvert, lengthOfBinary ):
	counter = 0
	shift = 0
	base = []
	
	grayCode = ''
	
	while (counter < lengthOfBinary):
		base.append(binaryToConvert % 2)
		binaryToConvert /= 2
		counter += 1
		
	while (counter > 0):
		counter -= 1
		grayCode = grayCode + str((base[counter] + shift) % 2)
		shift = shift + 2 - grayCode[counter]
	
	return grayCode

def hammingDistance( binaryStringOne, binaryStringTwo ):
	if binaryStringOne == binaryStringTwo: return True

	maxLength = len(binaryStringOne) if len(binaryStringOne) > len(binaryStringTwo) else len(binaryStringTwo)
	counter = 0
	
	for i in range(0, maxLength):
		if binaryStringOne[i] != binaryStringTwo[i]: counter += 1
		
	return counter

binaryStringOne = int(input("User Input One: "))
binaryStringTwo = int(input("User Input Two: "))

binaryStringOne = integerToBinary( binaryStringOne )
binaryStringTwo = integerToBinary( binaryStringTwo )

print "\nBinary Code One: %s" % binaryStringOne
print "Binary Code Two: %s" % binaryStringTwo
print "\nHamming Distance Of Binary: %s " % hammingDistance(binaryStringOne, binaryStringTwo)

grayCodeOne = binaryToGray(int(binaryStringOne), len(binaryStringOne))
grayCodeTwo = binaryToGray(int(binaryStringTwo), len(binaryStringTwo))

print "\nGray Code One: %s" % grayCodeOne
print "Gray Code Two: %s" % grayCodeTwo
print "\nHamming Distance Of Binary: %s " % hammingDistance(str(grayCodeOne), str(grayCodeTwo))
