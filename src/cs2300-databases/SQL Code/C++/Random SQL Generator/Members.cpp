//
//  Members.cpp
//  Random SQL Generator
//
//  Created by Illya Starikov on 4/26/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#include "Members.hpp"
#include "Functions.hpp"

#include <iomanip>
#include <iostream>


Members::Members() {
    groupID = randomArbitrary(1, GROUP_COUNT);
    userID = getUserID();
}

const std::string MEMBERS_TABLE_NAME = "MEMBERS";
const std::string MEMBERS_USER_ID_NAME = "UiD";
const std::string MEMBERS_GROUP_ID_NAME = "GiD";
//const std::string MEMBERS_ = "";


void Members::printInsert() {
    std::cout << "INSERT INTO " << MEMBERS_TABLE_NAME << "(" << MEMBERS_USER_ID_NAME << SEPERATOR << MEMBERS_GROUP_ID_NAME << ") VALUES" << std::endl;
}

void Members::printAttributes(bool isLastPrint) {
    std::cout << std::setw(TAB_LENGTH) << "(" << userID << SEPERATOR << groupID << ")";
    isLastPrint ? std::cout << ";"  << std::endl : std::cout << "," << std::endl;
}

int Members::getUserID() {
    static int id = 0;
    return ++id;
}