//
//  Arguement.cpp
//  Homework 1
//
//  Created by Illya Starikov on 9/6/15.
//  Copyright (c) 2015 Illya Starikov. All rights reserved.
//

#include "Argument.h"
#include "Functions.h"

argument::argument() {
    linesOfLogic = 0;
    numberOfVariables = 0;
}

void argument::setUpTheClass(const string argumentStack[], const int sizeOfArgumentStack) {
    premise = new (nothrow) string[sizeOfArgumentStack];
    if (premise == nullptr) { cannotAllocateMemoryWarning(); }

    
    for (int i = 0; i < sizeOfArgumentStack - 1; i++) {
        premise[i] = argumentStack[i];
        cout << argumentStack[i] << endl;
    }
    
    linesOfLogic = sizeOfArgumentStack;
    conclusion = argumentStack[sizeOfArgumentStack - 1];
    
    determineNumberOfVariables();
    createTruthTable();
}

void argument::determineNumberOfVariables() {
    for (int i = 0; i < linesOfLogic; i++) { // walk down the lines of logic
        cout << "Premise Length: " << premise[i].length() << endl;
        for (int j = 0; j < premise[i].length(); j++) { // walk across the premise to look for variables
            if (isalnum(premise[i].c_str()[j])) {
                uniqueVariableFound(premise[i].c_str()[j]);
            }
        }
    }
}


bool argument::uniqueVariableFound(const char characterThatWasFound) {
    bool variableWasFound = false;
    int i = 0;
    
    do {
        if (characterThatWasFound != variableLetters[i]) {
            numberOfVariables++;
        
            variableLetters = new (nothrow) char[numberOfVariables];
            if (variableLetters == nullptr) { cannotAllocateMemoryWarning(); }
            
            variableWasFound = true;
        }
        
        i++;
    } while (i < numberOfVariables && variableWasFound);
    
    return variableWasFound;
}

void argument::createTruthTable() {
    cout << "| ";
    for (int i = 0; i < numberOfVariables; i++) {
        cout << variableLetters[i] << " "; 
    }
}
