// Programmer: Illya Starikov                                Date: 11/08/15
// File: braincalc.cpp                                       Class: CS1510A
//
//  braincalc.cpp
//  Homework #5
//
//  Created by Illya Starikov on 11/5/15.
//  Copyright © 2015 Illya Starikov. All rights reserved.
//

#include "TheBrain.h"

#include <iostream>
#include <cstdlib>
#include <string>

using namespace::std;

const char endOfProgram = '$';

int main() {
    for (int i = 0; i < 10000; i++) {
    TheBrain bigBrain;
    string input;
    
    int x, y;
    
    do {
        cin >> input;
        
        if (isdigit(*input.c_str())) {
            bigBrain.push(atoi(input.c_str()));
        } else {
            switch (*input.c_str()) {
                
                case 'X':
                    bigBrain.print();
                    break;
                    
                case 'C':
                    bigBrain.clear();
                    break;
                
                case 'S':
                    bigBrain.sum();
                    break;
                    
                case 'P':
                    bigBrain.product();
                    break;
                    
                case '*':
                    bigBrain.push( bigBrain.popAndReturn() * bigBrain.popAndReturn() );
                    break;
                    
                case '+':
                    bigBrain.push( bigBrain.popAndReturn() + bigBrain.popAndReturn() );
                    break;
                    
                case '-':
                    x = bigBrain.popAndReturn();
                    y =  bigBrain.popAndReturn();
                    bigBrain.push( y - x );
                    break;
                    
                case '/':
                    x = bigBrain.popAndReturn();
                    y =  bigBrain.popAndReturn();
                    bigBrain.push( y / x );
                    break;
                    
                case '!':
                    bigBrain.push(-bigBrain.popAndReturn());
                    break;
                    
            }
        }
    } while (*input.c_str() != endOfProgram);
    }
}