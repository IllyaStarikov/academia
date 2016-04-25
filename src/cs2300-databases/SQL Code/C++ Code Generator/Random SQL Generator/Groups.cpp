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

const std::string GROUP_MODERATOR = "Moderator";
Group::Group() {
    const int numberToGetNameFrom = randomArbitrary(0, GROUPS_NAME_TO_GO_TO);
    title = importFromFile(GROUPS_FILENAME, numberToGetNameFrom);
    startDate = sqlDate();
    groupID = generateID();
    moderatorID = randomArbitrary(1, USER_COUNT);
}

void Group::printInsert() {
    std::cout << "INSERT INTO " << GROUP_TABLE_NAME_ATTRIBUTE << "(" << GROUP_ID << SEPERATOR << GROUP_MODERATOR << SEPERATOR << GROUP_TITLE_ATTRIBUTE << SEPERATOR << GROUP_DATE_ATTRIBUTE  << ") VALUES" << std::endl;
}

void Group::printAttributes(bool isLastPrint) {
    std::cout << std::setw(TAB_LENGTH) << "(" << groupID << SEPERATOR << moderatorID << SEPERATOR << title << SEPERATOR << startDate << ")";
    isLastPrint ? std::cout << ";"  << std::endl : std::cout << "," << std::endl;
}

int Group::generateID() {
    static int ID = 0;
    return ++ID;
}