//
//  Functions.hpp
//  Random SQL Generator
//
//  Created by Illya Starikov on 4/10/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#ifndef Functions_hpp
#define Functions_hpp

#include "Constants.h"

#include <iostream>
#include <fstream>
#include <sstream>

template <typename T>
void printInsertAndAttributes(T relation[], int size) {
    relation[0].printInsert();
    for (int i = 0; i < size; i++) {
        relation[i].printAttributes(i == size - 1);
    }
    
    std::cout << std::endl;
}


std::string importFromFile(const std::string filename, const int lineNumber);
std::string sqlDate();
std::string sqlDate(int syear, int cyear);
std::string sqlTime(); 

int daysInMonth(const int year, const int month);
int randomArbitrary(const int floor, const int ceiling);

char randomLetter(bool uppercase);

#endif /* Functions_hpp */
