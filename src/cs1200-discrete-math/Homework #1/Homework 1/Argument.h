//
//  Argument.h
//  Homework 1
//
//  Created by Illya Starikov on 9/9/15.
//  Copyright (c) 2015 Illya Starikov. All rights reserved.
//

#ifndef homeworkOne
#define homeworkOne

#include <iostream>


/*
 --------------------Constructor--------------------
 Description:     Makes a valid arbitrary argument, specified by the creator of the program.
 Pre-Condition:   There must be a valid calling object.
 Post-Condition:  A valid argument is made.
*/

/*
 --------------------create Truth Table--------------------
 Description:     Creates a truth table with values.
 Pre-Condition:   Nothing.
 Post-Condition:  A truth table array is made.
 */

/*
 --------------------determine Validity--------------------
 Description:     Determines the validity of the argument.
 Pre-Condition:   Nothing.
 Post-Condition:  The validity cahnges, determined by if the argument is valid.
 */

/*
 --------------------print Out Argument, Truth Table, Validity, Argument Form--------------------
 Description:     Prints out the arguments.
 Pre-Condition:   Nothing.
 Post-Condition:  Side effects, cout statements.
 */

const int defaultNumberOfPremises = 3;
const int defaultNumberOfVariables = 2;

const int heightOfTruthTable = 4; // For the number of rows, 2^(number of variables)
const int widthOfTruthTable = defaultNumberOfVariables + defaultNumberOfPremises + 1; // The intilization rows plus lines of premises

const int locationOfP = 0;
const int locationOfQ = 1;

using namespace std;

class arbitraryArgument {
public:
    arbitraryArgument();
    void createTruthTable();
    void determineValidity();
    
    void printOutArgument();
    void printOutTruthTable();
    void printOutValididty();
    
    void printOutArgumentForm();
    
private:
    char variables[defaultNumberOfVariables];
    
    string premises[3] =  {"p → q", "~p", "p ∧ (q ∨ p)"};
    string conculsion =  "p";
    
    bool truthTable[4][6];
    bool argumentFormIsValid;
};


#endif /* defined(__Homework_1__Argument__) */
