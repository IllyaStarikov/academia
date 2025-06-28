//
//  Functions.cpp
//  Homework 1
//
//  Created by Illya Starikov on 9/5/15.
//  Copyright (c) 2015 Illya Starikov. All rights reserved.
//

#include "Functions.h"

using namespace std;

/*--------------------Main Functions--------------------*/
void printOutWelcome() {
    cout <<
    "Homework #1." << endl <<
    "Dr. Tauritz. CS1200. Lecture 1B." << endl <<
    "Copyright (c) 2015 Illya Starikov. All rights reserved." << endl << endl;
}

void getUserInputForArgument(argument &argumentDataIsNeededFor) {
    string *argumentStack = nullptr;
    int sizeOfStack;
    
    cout <<
    "Please enter your argument." << endl <<
    "Everything before the conclusion will be considered a premise" << endl << endl;
    
    cout << "How many statements (including conclusion)? " << endl;
    cin >> sizeOfStack;
    
    cout << endl << "Please enter the statments." << endl;
    
    
    argumentStack = new (nothrow) string[sizeOfStack + 1];
    if (argumentStack == nullptr) { cannotAllocateMemoryWarning(); }
    
    for (int i = 0; i <= sizeOfStack; i++) {
        if (i == sizeOfStack) { cout << "∴ "; }
        getline(cin, argumentStack[sizeOfStack - 1]);
    }
    
    argumentDataIsNeededFor.setUpTheClass(argumentStack, sizeOfStack);
    
    delete[] argumentStack;
    argumentStack = nullptr;
}

/*--------------------Maintenance Functions--------------------*/
void cannotAllocateMemoryWarning() {
    cerr << "Memory cannot be allocated. Terminating." << endl;
}


