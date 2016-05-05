//
//  Cardio.cpp
//  Random SQL Generator
//
//  Created by Illya Starikov on 4/24/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#include "Cardio.hpp"
#include "Functions.hpp"


CardioWorkout::CardioWorkout() {
    averageHeartRate = randomArbitrary(HEARTRATE_MIN, HEARTRATE_MAX);
    averageSpeed = randomArbitrary(1, MAX_SPEED);
    distanceCovered = randomArbitrary(1, MAX_DISTANCE_COVERED);
    title = importFromFile(CARDIO_FILENAME, CARDIO_NAME_TO_GO_TO);
}

void CardioWorkout::printInsert() {
    std::cout << "INSERT INTO " << CARDIO_TABLE_NAME_ATTRIBUTE << "(" << WORKOUT_ID << SEPERATOR << CARDIO_HEARTRATE << SEPERATOR << CARDIO_AVERAGE_SPEED << SEPERATOR << CARDIO_DISTANCE_COVERED << ") VALUES" << std::endl;
}

void CardioWorkout::printAttributes(bool isLastPrint) {
    std::cout << std::setw(TAB_LENGTH) << "(" << workoutID << SEPERATOR << averageHeartRate << SEPERATOR << averageSpeed << SEPERATOR << distanceCovered << ")";
    isLastPrint ? std::cout << ";"  << std::endl : std::cout << "," << std::endl;
}


void CardioWorkout::printInsertWorkout() {
    std::cout << "INSERT INTO " << WORKOUT_TABLE_NAME_ATTRIBUTE << "(" << WORKOUT_ID <<  SEPERATOR << WORKOUT_DURATION << SEPERATOR << WORKOUT_TITLE << SEPERATOR << WORKOUT_INTESITY << SEPERATOR << WORKOUT_INTENSITY_CALORIES_BURNED << SEPERATOR  << USER_UID_ATTRIBUTE << ") VALUES" << std::endl;
}

void CardioWorkout::printAttributesWorkout(bool isLastPrint) {
    std::cout << std::setw(TAB_LENGTH) << "(" << workoutID << SEPERATOR << DELIMETER << duration << DELIMETER << SEPERATOR  << DELIMETER << title << DELIMETER << SEPERATOR << intensity << SEPERATOR << caloriesBurned << SEPERATOR << userID << ")";
    isLastPrint ? std::cout << ";"  << std::endl : std::cout << "," << std::endl;
}