//  COMP SCI 1200 Section B FS2015 Assignment 4
//
//  Functions.hpp
//  Homework 4
//
//  Created by Illya Starikov on 11/8/15.
//  Copyright © 2015 Illya Starikov. All rights reserved.
//
#include <iostream>

using namespace::std;

#ifndef Functions_hpp
#define Functions_hpp

/*--------------------Conversion Functions--------------------*/
int lengthOfBinaryArray(int x);
void integerToBinary(unsigned integerToConvert, unsigned binary[], int size);
string arrayOfIntToString(unsigned array[], int size);
void reverseArray(unsigned array[], int size);
string integerToGray( const unsigned value );
int calculateHammingDistance(string binaryOne, string binaryTwo);

 /*--------------------I/O--------------------*/
int getIntegerInput();
void displayColumnBreak(const string title);
void displayBinaryConversion(const int integerOne, const int integerTwo);
void displayGrayConversion(const int integerOne, const int integerTwo);
void displayBreak();


#endif /* Functions_hpp */
