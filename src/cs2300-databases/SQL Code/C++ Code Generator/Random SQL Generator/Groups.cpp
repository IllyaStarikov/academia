//
//  Groups.cpp
//  Random SQL Generator
//
//  Created by Illya Starikov on 4/10/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#include "Groups.hpp"
#include "Functions.hpp"
#include "Constants.h"

#include <iomanip>
#include <iostream>

Group::Group() {
    const int numberToGetNameFrom = randomArbitrary(0, GROUPS_NAME_TO_GO_TO);
    title = importFromFile(GROUPS_FILENAME, numberToGetNameFrom);
    startDate = sqlDate();
}

void Group::printInsert() {
    std::cout << "INSERT INTO " << GROUP_TABLE_NAME_ATTRIBUTE << "(" << GROUP_TITLE_ATTRIBUTE << ", " << GROUP_DATE_ATTRIBUTE << ") VALUES" << std::endl;
}

void Group::printAttributes(bool isLastPrint) {
    std::cout << std::setw(TAB_LENGTH) << "(" << title << ", " << startDate << ")";
    isLastPrint ? std::cout << ";"  << std::endl : std::cout << "," << std::endl;
}