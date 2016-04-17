//
//  Functions.cpp
//  Random SQL Generator
//
//  Created by Illya Starikov on 4/10/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#include "Functions.hpp"
#include "Constants.h"


std::string importFromFile(const std::string filename, const int lineNumber) {
    std::ifstream readin;
    readin.open(filename.c_str());
    
    std::string toReturn;
    
    for (int i = 0; i < lineNumber; i++) {
        if (readin.eof() == true) {
            readin.clear();
            readin.seekg(0, std::ios::beg);
        } else {
            getline(readin, toReturn);
        }
    }
    
    readin.close();
    return toReturn;
}

std::string sqlDate() {
    std::ostringstream ss;
    int year = randomArbitrary(START_YEAR, CURRENT_YEAR),
    month = randomArbitrary(1, MONTHS_IN_YEAR);
    
    ss << year;
    ss << DELIMITER;
    
    ss << month;
    ss << DELIMITER;
    
    ss << daysInMonth(year, month);
    
    return ss.str();
}

int daysInMonth(const int year, const int month) {
    int numberOfDays = 0;
    
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        numberOfDays = 30;
    } else if (month == 2) {
        bool isLeapYear = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (isLeapYear) {
            numberOfDays = 29;
        } else {
            numberOfDays = 28;
        }
    }
    else {
        numberOfDays = 31;
    }
    
    return numberOfDays;
}

int randomArbitrary(const int floor, const int ceiling) {
    return floor + rand() % (ceiling - floor + 1);
}
