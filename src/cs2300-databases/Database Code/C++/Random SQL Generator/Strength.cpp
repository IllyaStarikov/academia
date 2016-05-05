//
//  Strength.cpp
//  Random SQL Generator
//
//  Created by Illya Starikov on 4/18/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#include "Strength.hpp"

StrengthWorkout::StrengthWorkout() {
    std::string filename = STRENGTH_FILES[randomArbitrary(0, NUMBER_OF_STRENGTH_FILES - 1)];
    int nameToGoTo = randomArbitrary(0, STRENGTH_NAME_TO_GO_TO);
    
    title = importFromFile(STRENGTH_FILENAME_PREFIX + filename + FILENAME_EXTENSION, nameToGoTo);
    targetZone = filename; // Target zones are the next one
}

void StrengthWorkout::printInsertWorkout() {
    std::cout << "INSERT INTO " << WORKOUT_TABLE_NAME_ATTRIBUTE << "(" << WORKOUT_ID <<  SEPERATOR << WORKOUT_DURATION << SEPERATOR << WORKOUT_TITLE << SEPERATOR << WORKOUT_INTESITY << SEPERATOR << WORKOUT_INTENSITY_CALORIES_BURNED << SEPERATOR << USER_UID_ATTRIBUTE << ") VALUES" << std::endl;
}

void StrengthWorkout::printAttributesWorkout(bool isLastPrint) {
    std::cout << std::setw(TAB_LENGTH) << "(" << workoutID << SEPERATOR << DELIMETER << duration << DELIMETER << SEPERATOR  << DELIMETER << title << DELIMETER << SEPERATOR << intensity << SEPERATOR << caloriesBurned << SEPERATOR << userID << ")";
    isLastPrint ? std::cout << ";"  << std::endl : std::cout << "," << std::endl;
}

void StrengthWorkout::printInsert() {
    std::cout << "INSERT INTO " << STRENGTH_TABLE_NAME_ATTRIBUTE << "(" << WORKOUT_ID << SEPERATOR << STRENGTH_TARGET_ZONE << ") VALUES" << std::endl;
}

void StrengthWorkout::printAttributes(bool isLastPrint) {
    std::cout << std::setw(TAB_LENGTH) << "(" << workoutID << SEPERATOR << DELIMETER << targetZone << DELIMETER << ")";
    isLastPrint ? std::cout << ";"  << std::endl : std::cout << "," << std::endl;
}
