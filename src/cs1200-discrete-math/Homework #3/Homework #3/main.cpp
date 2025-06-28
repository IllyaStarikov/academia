//  Illya Starikov: COMP SCI 1200 Section B FS2015 3
//
//  main.cpp
//  Homework #3
//
//  Created by Illya Starikov on 10/6/15.
//  Copyright © 2015 Illya Starikov. All rights reserved.
//

#include <iostream>
#include <string>

#include "Factorial.h"

using namespace std;

int main() {
    unsigned numberToFactor;
    bool createLatexOuput;
    char inputToEvaluate;
    
    cout << "Number: ";
    cin >> numberToFactor;
    
    cout << "Latex Output (Y / N)? ";
    cin >> inputToEvaluate;
    
    createLatexOuput = (toupper(inputToEvaluate) == 'Y');
    
    FactorialModel someFactorial(numberToFactor, createLatexOuput);
    someFactorial.indexFactors();
    someFactorial.printFactorialModelOut();
}
