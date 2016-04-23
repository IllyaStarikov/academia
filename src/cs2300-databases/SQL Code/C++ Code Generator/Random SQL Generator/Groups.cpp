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
    groupID = generateID();
}

void Group::printInsert() {
    std::cout << "INSERT INTO " << GROUP_TABLE_NAME_ATTRIBUTE << "(" << GROUP_TITLE_ATTRIBUTE << SEPERATOR << GROUP_DATE_ATTRIBUTE  << SEPERATOR << GROUP_ID << ") VALUES" << std::endl;
}

void Group::printAttributes(bool isLastPrint) {
    std::cout << std::setw(TAB_LENGTH) << "(" << groupID << SEPERATOR << title << SEPERATOR << startDate << ")";
    isLastPrint ? std::cout << ";"  << std::endl : std::cout << "," << std::endl;
}

int Group::generateID() {
    static int ID = 0;
    return ++ID;
}