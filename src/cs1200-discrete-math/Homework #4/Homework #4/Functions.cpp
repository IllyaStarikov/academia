//  COMP SCI 1200 Section B FS2015 Assignment 4
//
//  Functions.cpp
//  Homework 4
//
//  Created by Illya Starikov on 11/8/15.
//  Copyright © 2015 Illya Starikov. All rights reserved.
//

#include "Functions.h"

#include <iostream>
#include <string>
#include <sstream>

using namespace::std;

string intToString(const int toConvert) {
    // Sorry, I had to use streams :(
    // Had to convert to int somehow..
    ostringstream stringStream;
    stringStream.clear();
    stringStream << toConvert;
    return stringStream.str();
}

int lengthOfBinaryArray(int x) {
    unsigned count = 0;
    
    while (x != 0) {
        x /= 2;
        count++;
    }
    
    return static_cast<int>(count);
}

void integerToBinary(unsigned integerToConvert, unsigned binary[], int size) {
    if (integerToConvert == 0) { binary[0] = 0; return; } // exception, integer is already binary
    
    for (int i = size; i > 0; i--) {
        binary[i - 1] = integerToConvert % 2;
        integerToConvert  /= 2;
    }
}

string arrayOfIntToString(unsigned array[], int size) {
    std::string toReturn = "";
    
    for (int i = 0; i < size; i++) {
        toReturn.append(intToString(array[i]));
    }
    
    return toReturn;
}

string convertIntegerToBinary( unsigned integerToConvert ) {
    unsigned *binary = new unsigned [lengthOfBinaryArray(integerToConvert)];
    integerToBinary(integerToConvert, binary, lengthOfBinaryArray(integerToConvert));
    
    return arrayOfIntToString(binary, lengthOfBinaryArray(integerToConvert));
}


void reverseArray(unsigned array[], int size) {
    unsigned temp;
    
    for (int i = 0; i < size/2; i++) {
        temp = array[size - i - 1];
        array[size - i - 1] = array[i];
        array[i] = temp;
    }
    
}

string integerToGray( const unsigned value ) {
    const int length = lengthOfBinaryArray(value);
    unsigned *BRGC = new unsigned [length], *binary = new unsigned [length];
    unsigned counter = length - 1;
    
    integerToBinary(value, binary, length);
    reverseArray(binary, length); // I have no idea why, but i have to reverse it. Twice.
    
    BRGC[counter] = binary[counter];
  
    while (counter--) {
        BRGC[counter] = binary[counter + 1] ^ binary[counter];
    }
    
    reverseArray(BRGC, length);
    return arrayOfIntToString(BRGC, length);
}

int calculateHammingDistance(string binaryOne, string binaryTwo) {
    // In the cast of the binary strings being different sizes, this prevents me from using the [] accessor in invalid memory
    const unsigned long lengthOfSmallerBinary = binaryOne.length() > binaryTwo.length() ? binaryTwo.length() : binaryOne.length();
    int differenceCounter = 0;
    
    for (unsigned i = 0; i < lengthOfSmallerBinary ; i++) {
        if (binaryOne[i] != binaryTwo[i]) { differenceCounter++; };
    }
    
    return differenceCounter;
}

int getIntegerInput() {
    static int counter = 0, input;
    counter++;
    
    cout << "Integer #" << counter << ": ";
    cin >> input;
    
    return input;
}

void displayColumnBreak(const string title) {
    cout << endl << "/*--------------------" << title << "--------------------*/";
}

void displayBinaryConversion(const int integerOne, const int integerTwo) {
    displayColumnBreak("Binary Conversion");
    
    cout << endl << "Binary #1: " << convertIntegerToBinary(integerOne) << endl << "Binary #2: " << convertIntegerToBinary(integerTwo) << endl << "Hamming Distance: " << calculateHammingDistance(convertIntegerToBinary(integerOne), convertIntegerToBinary(integerTwo)) << endl;
}

void displayGrayConversion(const int integerOne, const int integerTwo) {
    displayColumnBreak("Gray Conversion"); // 50 Shades of Gray Conversions
    
    cout << endl << "Gray #1: " << integerToGray(integerOne) << endl << "Gray #2: " << integerToGray(integerTwo) << endl << "Hamming Distance: " << calculateHammingDistance(integerToGray(integerOne), integerToGray(integerTwo)) << endl;
}

void displayBreak() {
    cout << endl << endl;
}