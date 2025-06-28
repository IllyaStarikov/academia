//  COMP SCI 1200 Section B FS2015 Assignment 4
//
//  main.cpp
//  Homework 4
//
//  Created by Illya Starikov on 11/8/15.
//  Copyright © 2015 Illya Starikov. All rights reserved.
//
#include "Functions.h"

int main() {
    unsigned inputOne = getIntegerInput(), inputTwo = getIntegerInput();
    
    displayBinaryConversion(inputOne, inputTwo);
    displayGrayConversion(inputOne, inputTwo);
    
    displayBreak();
}
