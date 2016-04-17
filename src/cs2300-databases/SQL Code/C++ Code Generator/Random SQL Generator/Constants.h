//
//  Constants.h
//  Random SQL Generator
//
//  Created by Illya Starikov on 4/10/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#ifndef Constants_h
#define Constants_h

#include <iostream>

const std::string GROUPS_FILENAME = "groups.txt";

const std::string GROUP_TABLE_NAME_ATTRIBUTE = "GROUP";
const std::string GROUP_TITLE_ATTRIBUTE = "title";
const std::string GROUP_DATE_ATTRIBUTE = "startDate";

const int GROUPS_NAME_TO_GO_TO = 1000;
const int GROUP_COUNT = 1000;

const int CURRENT_YEAR = 2016;
const int START_YEAR = 1900;
const int MONTHS_IN_YEAR = 12;

const int TAB_LENGTH = 4;
const char DELIMITER = '-';

#endif /* Constants_h */
