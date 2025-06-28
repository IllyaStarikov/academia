//
//  Argument.cpp
//  Homework 1
//
//  Created by Illya Starikov on 9/9/15.
//  Copyright (c) 2015 Illya Starikov. All rights reserved.
//

#include "Argument.h"

arbitraryArgument::arbitraryArgument() {
    argumentFormIsValid = NULL; // better to be safe than sorry
    
    char startingLetter = 'p';
    for (int i = 0; i < defaultNumberOfVariables; ++i) {
        variables[i] = startingLetter + i;
    }
    
    createTruthTable();
    determineValidity();
}

void arbitraryArgument::createTruthTable() {
    bool assignmentValue = false;
    // This was the simplest and most intuitive way i could
    // think of to intilize the truth table
    
    // p
    for (int p = 0; p < heightOfTruthTable; ++p) {
        if (p % 2 == 0) {
            assignmentValue = !assignmentValue;
        }
        truthTable[0][p] = assignmentValue;
    }
    
    assignmentValue = true;
    
    for (int q = 0; q < heightOfTruthTable; ++q) {
        truthTable[1][q] = assignmentValue;
        
        if (q % 1 == 0) {
            assignmentValue = !assignmentValue;
        }
    }

    // p → q
    for (int i = 0; i < heightOfTruthTable; ++i) {
        if ((truthTable[0][i] == true) && (truthTable[1][i] == false)) {
            truthTable[defaultNumberOfVariables][i] = false;
        } else {
            truthTable[defaultNumberOfVariables][i] = true;
        }
        
        //cout << truthTable[defaultNumberOfVariables][i];
    }
  
    // ~p
    for (int i = 0; i < heightOfTruthTable; ++i) {
        truthTable[defaultNumberOfVariables + 1][i] = !truthTable[locationOfP][i];
    }
    
    // p ∧ (q ∨ p)
    for (int i = 0; i < heightOfTruthTable; ++i) {
        truthTable[defaultNumberOfVariables + 2][i] = truthTable[locationOfP][i] || (truthTable[locationOfQ][i] && truthTable[locationOfP][i]);
    }
    
    // conculusion
    for (int i = 0; i < heightOfTruthTable; ++i) {
        truthTable[defaultNumberOfVariables + 3][i] = truthTable[locationOfP][i];
    }
}

void arbitraryArgument::determineValidity() {
    bool counterExampleFound = false;
    
    
    // walk down the individual rows,
    // if all the columns a true and the premise is false,
    // form is invalid. all else, argument form is true.
    for (int i = heightOfTruthTable; i < defaultNumberOfPremises + 1; ++i) {
        for (int j = defaultNumberOfVariables; j < defaultNumberOfPremises + 1; ++j) {
            do {
                if (j == defaultNumberOfVariables + 3 && truthTable[defaultNumberOfVariables + 3][j]) {
                    counterExampleFound = true;
                }
            } while (truthTable[i][j]);
        }
    }
    
    // if there is not counter argument,
    // then the argument form is valid.
    argumentFormIsValid = !counterExampleFound;
}

void arbitraryArgument::printOutArgument() {
    for (int i = 0; i < defaultNumberOfPremises; ++i) {
        cout << premises[i] << endl;
    }
    
    cout << "∴ " << conculsion << endl;
}
void arbitraryArgument::printOutTruthTable() {
    const char gutter = '|';
    const char space = ' ';
    
    cout << " _______________________ " << endl;
    for (int i = 0; i < heightOfTruthTable; ++i) {
        for (int j = 0; j < widthOfTruthTable; ++j) {
            cout << gutter << space << truthTable[j][i] << space;
        }
        cout << gutter << endl;
    }
    cout << " ----------------------- " << endl;
}

void arbitraryArgument::printOutValididty() {
    cout << "Argument Is: ";
    argumentFormIsValid ? cout << "Valid" : cout << "Invalid";
    cout << "." << endl;
}

void arbitraryArgument::printOutArgumentForm() {
    printOutArgument();
    printOutTruthTable();
    printOutValididty();
}