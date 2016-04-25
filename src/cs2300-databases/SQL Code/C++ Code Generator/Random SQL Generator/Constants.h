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

const std::string GROUPS_FILENAME = "data/groups.txt";
const std::string USER_USERNAME_FILENAME = "data/usernames.txt";
const std::string USER_FFIRSTNAME_FILENAME = "data/FFName.txt";
const std::string USER_MFIRSTNAME_FILENAME = "data/MFname.txt";
const std::string USER_LNAME_FILENAME = "data/LName.txt";
const std::string CARDIO_FILENAME = "data/cardio.txt";

const std::string WORKOUT_TABLE_NAME_ATTRIBUTE = "WORKOUT";
const std::string WORKOUT_INTENSITY_CALORIES_BURNED = "CaloriesBurned";
const std::string WORKOUT_INTESITY = "Intensity";
const std::string WORKOUT_ID = "WiD";
const std::string WORKOUT_DURATION = "Duration";
const std::string WORKOUT_TITLE = "Title";

const std::string CARDIO_TABLE_NAME_ATTRIBUTE = "CARDIO";
const std::string CARDIO_HEARTRATE = "AverageHeartRate";
const std::string CARDIO_AVERAGE_SPEED = "AverageSpeed";
const std::string CARDIO_DISTANCE_COVERED = "DistanceCovered";

const std::string STRENGTH_TABLE_NAME_ATTRIBUTE = "STRENGTH";

const std::string GROUP_TABLE_NAME_ATTRIBUTE = "GROUPS";
const std::string GROUP_TITLE_ATTRIBUTE = "title";
const std::string GROUP_DATE_ATTRIBUTE = "startDate";
const std::string GROUP_ID = "GiD";

const std::string USER_TABLE_NAME_ATTRIBUTE = "USERS";
const std::string USER_UID_ATTRIBUTE = "UiD"; 
const std::string USER_USERNAME_ATTRIBUTE = "Username"; 
const std::string USER_HEIGHT_FEET_ATTRIBUTE = "HeightFeet";
const std::string USER_HEIGTH_INCHES_ATTRIBUTE = "HeightInches";
const std::string USER_BIRTHDATE_ATTRIBUTE = "Birthdate"; 
const std::string USER_STARTING_WEIGHT_ATTRIBUTE = "Weight"; 
const std::string USER_GOAL_WEIGHT_ATTRIBUTE = "Goal"; 
const std::string USER_PASSWORD_ATTRIBUTE = "Password"; 
const std::string USER_JOINDATE_ATTRIBUTE = "JoinDate"; 
const std::string USER_GENDER_ATTRIBUTE = "Gender";
const std::string USER_FNAME_ATTRIBUTE = "FName";
const std::string USER_MINIT_ATTRIBUTE = "MInti";
const std::string USER_LNAME_ATTRIBUTE = "LName";

const std::string MEASUREMENT_WEIGHT_TABLE_NAME = "WEIGHT";
const std::string MEASUREMENT_ARM_TABLE_NAME = "ARM"; 
const std::string MEASUREMENT_CHEST_TABLE_NAME = "CHEST"; 
const std::string MEASUREMENT_UID_ATTRIBUTE = "UiD";
const std::string MEASUREMENT_DATE_ATTRIBUTE = "Date";  
const std::string MEASUREMENT_TIME_ATTRIBUTE = "Time"; 
const std::string MEASUREMENT_WEIGHT_ATTRIBUTE = "Weight"; 
const std::string MEASURMENT_ARM_ATTRIBUTE = "Arm"; 
const std::string MEASURMENT_CHEST_ATTRIBUTE = "Chest"; 

const std::string SEPERATOR = ", ";

const int GROUPS_NAME_TO_GO_TO = 1000;
const int USERS_USERNAME_TO_GO_TO = 60;
const int USERS_FFIRST_NAME_TO_GO_TO = 2000;
const int USERS_MFIRST_NAME_TO_GO_TO = 2000;
const int USERS_LNAME_TO_GO_TO = 720;  

const int MAX_WEIGHT = 300; 
const int MIN_WEIGHT = 90; 
const int MAX_ARM = 29; 
const int MIN_ARM = 21;
const int MAX_CHEST = 42;
const int MIN_CHEST = 36;

const int GROUP_COUNT = 5;
const int WORKOUT_COUNT = 5;
const int USER_COUNT = 5;
const int WEIGHT_COUNT = 5;
const int ARM_COUNT = 5;
const int CHEST_COUNT = 5;

const int CURRENT_YEAR = 2016;
const int START_YEAR = 1900; 
const int MONTHS_IN_YEAR = 12;

const int TAB_LENGTH = 4;
const char DELIMITER = '-';

const int WORKOUT_MAX_HOURS = 2;
const int WORKOUT_MAX_MINS = 59;

const int INTENSITY_MAX = 10;

const int MINUTES_IN_HOUR = 60;

const double WORKOUT_ERROR = .15;
const double WORKOUTS_CALORIES_PER_MINUTE = 1.5;

const int STRENGTH_NAME_TO_GO_TO = 20;

const int HEARTRATE_MIN = 50;
const int HEARTRATE_MAX = 200;
const int MAX_SPEED = 20;
const int MAX_DISTANCE_COVERED = 26;

const int CARDIO_NAME_TO_GO_TO = 5;

const std::string STRENGTH_FILENAME_PREFIX = "data/strength/";
const std::string FILENAME_EXTENSION = ".txt";
const int NUMBER_OF_STRENGTH_FILES = 3;
const std::string STRENGTH_FILES[NUMBER_OF_STRENGTH_FILES] = { "Arms", "Legs", "Back" };

const std::string GROUP_MODERATOR = "Moderator";
const std::string DELIMETER = "'";

#endif /* Constants_h */
