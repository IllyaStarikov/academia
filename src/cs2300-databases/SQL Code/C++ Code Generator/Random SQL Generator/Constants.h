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
const std::string USER_USERNAME_FILENAME = "usernames.txt";
const std::string USER_FFIRSTNAME_FILENAME = "FFName.txt";
const std::string USER_MFIRSTNAME_FILENAME = "MFname.txt";
const std::string USER_LNAME_FILENAME = "LName.txt";

const std::string WORKOUT_TABLE_NAME_ATTRIBUTE = "WORKOUT";
const std::string WORKOUT_INTENSITY_CALORIES_BURNED = "caloriesBurned";
const std::string WORKOUT_INTESITY = "intensity";

const std::string GROUP_TABLE_NAME_ATTRIBUTE = "GROUP";
const std::string GROUP_TITLE_ATTRIBUTE = "title";
const std::string GROUP_DATE_ATTRIBUTE = "startDate";

const std::string USER_TABLE_NAME_ATTRIBUTE = "USERS";
const std::string USER_UID_ATTRIBUTE = "UiD"; 
const std::string USER_USERNAME_ATTRIBUTE = "Username"; 
const std::string USER_HEIGHT_ATTRIBUTE = "Height";
const std::string USER_BIRTHDATE_ATTRIBUTE = "Birthdate"; 
const std::string USER_STARTING_WEIGHT_ATTRIBUTE = "Weight"; 
const std::string USER_GOAL_WEIGHT_ATTRIBUTE = "Goal"; 
const std::string USER_PASSWORD_ATTRIBUTE = "Password"; 
const std::string USER_JOINDATE_ATTRIBUTE = "JoinDate"; 
const std::string USER_GENDER_ATTRIBUTE = "Gender";
const std::string USER_FNAME_ATTRIBUTE = "FName";
const std::string USER_MINIT_ATTRIBUTE = "MInti";
const std::string USER_LNAME_ATTRIBUTE = "LName";

const std::string SEPERATOR = ", ";

const int GROUPS_NAME_TO_GO_TO = 1000;
const int USERS_USERNAME_TO_GO_TO = 58;
const int USERS_FFIRST_NAME_TO_GO_TO = 17650;
const int USERS_MFIRST_NAME_TO_GO_TO = 12100;
const int USERS_LNAME_TO_GO_TO = 720;  

const int GROUP_COUNT = 1000;
const int WORKOUT_COUNT = 1000;
const int USER_COUNT = 1000; 

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
