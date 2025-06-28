//  Illya Starikov: COMP SCI 1200 Section B FS2015 3
//
//  Factorial Model.hpp
//  Homework #3
//
//  Created by Illya Starikov on 10/6/15.
//  Copyright © 2015 Illya Starikov. All rights reserved.
//

#ifndef Factorial_Model_hpp
#define Factorial_Model_hpp

class FactorialModel {
    unsigned factorial;
    bool outputIsRequestedInLatex;
    
    std::string outputString;
    
public:
    FactorialModel(const unsigned integerToFactor, const bool latexOuput);
    
    void indexFactors();
    void evaluateDigit(unsigned &currentNumber, const int counter);
    
    void appendToOutputString(const int number, const int exponent);
    void printFactorialModelOut();
};

#endif /* Factorial_Model_hpp */
