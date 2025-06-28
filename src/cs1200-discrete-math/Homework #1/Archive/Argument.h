//
//  Arguement.h
//  Homework 1
//
//  Created by Illya Starikov on 9/6/15.
//  Copyright (c) 2015 Illya Starikov. All rights reserved.
//

#ifndef __Homework_1__Arguement__
#define __Homework_1__Arguement__

#include <stdio.h>
#include <iostream>

using namespace std;
const int PLACEHOLDER = NULL;

class argument {
public:
    argument();
    void setUpTheClass(const string argumentStack[], const int sizeOfArgumentStack);
    void determineNumberOfVariables();
    bool uniqueVariableFound(const char characterThatWasFound);
    void createTruthTable();
    
private:
    string *premise = nullptr;
    string conclusion;

    char *variableLetters = nullptr;

    int numberOfVariables;
    int linesOfLogic;
    
    bool argumentIsValid;
    
};

#endif /* defined(__Homework_1__Arguement__) */
