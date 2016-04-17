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

const std::string WORKOUT_TABLE_NAME_ATTRIBUTE = "WORKOUT";
const std::string WORKOUT_INTENSITY_CALORIES_BURNED = "caloriesBurned";
const std::string WORKOUT_INTESITY = "intensity";

const std::string GROUP_TABLE_NAME_ATTRIBUTE = "GROUP";
const std::string GROUP_TITLE_ATTRIBUTE = "title";
const std::string GROUP_DATE_ATTRIBUTE = "startDate";

const std::string SEPERATOR = ", ";

const int GROUPS_NAME_TO_GO_TO = 1000;

const int GROUP_COUNT = 1000;
const int WORKOUT_COUNT = 1000;

const int CURRENT_YEAR = 2016;
const int START_YEAR = 1900;
const int MONTHS_IN_YEAR = 12;

const int TAB_LENGTH = 4;
const char DELIMITER = '-';

const int WORKOUT_MAX_HOURS = 2;
const int WORKOUT_MAX_MINS = 60;

const int INTENSITY_MAX = 10;

const int MINUTES_IN_HOUR = 60;

const double WORKOUT_ERROR = .15;
const double WORKOUTS_CALORIES_PER_MINUTE = 1.5;

#endif /* Constants_h */
