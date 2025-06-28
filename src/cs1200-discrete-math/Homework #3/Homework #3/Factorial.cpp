//  Illya Starikov: COMP SCI 1200 Section B FS2015 3
//
//  Factorial Model.cpp
//  Homework #3
//
//  Created by Illya Starikov on 10/6/15.
//  Copyright © 2015 Illya Starikov. All rights reserved.
//

#include <iostream>
#include <string.h>

#include "Factorial.h"

using namespace std;

FactorialModel::FactorialModel(const unsigned integerToFactor, const bool latexOuput) {
    factorial = integerToFactor;
    outputIsRequestedInLatex = latexOuput;
}

void FactorialModel::indexFactors() {
    int counter = 2;
    unsigned currentNumber = factorial;
    
    do {
        if ((currentNumber % counter) == 0) {
            evaluateDigit(currentNumber, counter);
        }
        
        counter++;
    } while (currentNumber > 1);
}

void FactorialModel::evaluateDigit(unsigned &currentNumber, const int counter) {
    bool advance = false;
    int localCounter = 0;

    do {
        if (currentNumber % counter == 0) {
            currentNumber /= counter;
            localCounter++;
            advance = true;
        } else {
            advance = false;
        }
    } while (advance);
    
    appendToOutputString(counter, localCounter);
}

void FactorialModel::appendToOutputString(const int number, const int exponent) {
    outputString.append(to_string(number));
    outputString.append("^");
    outputString.append(to_string(exponent));
    outputIsRequestedInLatex ? outputString.append(" \\times ") : outputString.append(" * ");
}

void FactorialModel::printFactorialModelOut() {
    cout << endl;
    
    /* String Hacking.
     Because I append the * symbol and the \times for latex output after every iteration,
     They are still at the end of the output string when I am about to output them.
    
     So I had to hack them using string functions (Could have done with C-Strings,
     But I would still need to import the string header. So this was the simpler of the two.)
     
     Tricky part: These functions do not work with unicode. Also, erase doesn't work with
     the "\" because it's assuming "\" is a manipulator. pop_back doesn't, it pull directly off the string
     stack.
    */
    
    if (outputIsRequestedInLatex) {
        for (int i = 0; i < 8; i++) {
            outputString.pop_back();
        }
        
        cout << "$$ " << factorial << " = " << outputString << " $$";
    } else {
        outputString.erase(outputString.end() - 2);
        cout << factorial << " = " << outputString;
    }
    
    cout << endl;
}