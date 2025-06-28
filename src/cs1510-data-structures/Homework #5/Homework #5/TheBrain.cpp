// Programmer: Illya Starikov                                Date: 11/08/15
// File: The Brain.cpp                                       Class: CS1510A
//
//  TheBrain.cpp
//  Homework #5
//
//  Created by Illya Starikov on 11/8/15.
//  Copyright © 2015 Illya Starikov. All rights reserved.
//

#include "TheBrain.h"

TheBrain::TheBrain() {
    max = 2;
    topOfStack = 0;
    
    data = new int [2];
}

bool TheBrain::isEmpty() const {
    return (topOfStack == 0);
}

const int& TheBrain::top() const throw ( Oops ) {
    
    try {
        if (topOfStack == 0) {
            Oops emptyStack("Empty Stack");
            throw emptyStack;
        }
    }
    
    catch (Oops errorObject) {
        cout << errorObject.getMsg() << endl;
    }
    
    if (topOfStack == 0) { return 0; }
    return data[topOfStack - 1];
}

void TheBrain::push(const int& x) {
    if (topOfStack == max) {
        if (max == 0) { max = 2; }
        
        max *= 2;
        int *temp = new int [max];
        
        for (int i = 0; i < max; i++) {
            temp[i] = data[i];
        }
        
        delete []data;
        data = NULL;
        
        data = temp;
    }
    
    data[topOfStack] = x;
    topOfStack++;
}

void TheBrain::pop() {
    if (!isEmpty()) {
        topOfStack--;
    }
}

int TheBrain::popAndReturn() {
    int returnValue = top();
    pop();
    
    return returnValue;
}


void TheBrain::clear() {
    topOfStack = 0;
}

void TheBrain::print() {
    const char space = ' ';
    std::cout << "[ ";
    
    for (int i = topOfStack - 1; i >= 0; i--) {
        std::cout << data[i] << space;
    }
    
    std::cout << "]" << endl;
}

void TheBrain::sum() {
    int sum = 0;
    
    for (int i = 0; i < topOfStack; i ++) {
        sum += data[i];
    }
    
    data[0] = sum;
    topOfStack = 1;
}

void TheBrain::product() {
    int product = 1;
    
    for (int i = 0; i < topOfStack; i ++) {
        product *= data[i];
    }
    
    data[0] = product;
    topOfStack = 1;
}

TheBrain::~TheBrain() {
    delete[] data;
    data = NULL;
}