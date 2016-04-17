//
//  Functions.hpp
//  Random SQL Generator
//
//  Created by Illya Starikov on 4/10/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#ifndef Functions_hpp
#define Functions_hpp

#include <iostream>
#include <fstream>
#include <sstream>

std::string importFromFile(const std::string filename, const int lineNumber);
std::string sqlDate();

int daysInMonth(const int year, const int month);
int randomArbitrary(const int floor, const int ceiling);

#endif /* Functions_hpp */
