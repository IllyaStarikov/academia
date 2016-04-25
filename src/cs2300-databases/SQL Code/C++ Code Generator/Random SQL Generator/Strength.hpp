//
//  Strength.hpp
//  Random SQL Generator
//
//  Created by Illya Starikov on 4/18/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#ifndef Strength_hpp
#define Strength_hpp

#include <stdio.h>

#include "Workout.hpp"
#include "Constants.h"
#include "Functions.hpp"

const std::string STRENGTH_FILENAME = "data/strength.txt";
const std::string STRENGTH_TARGET_ZONE = "TargetZone";

class StrengthWorkout : Workout {
    std::string targetZone;
    
public:
    StrengthWorkout();
    void printInsert() {
        std::cout << "INSERT INTO " << STRENGTH_TABLE_NAME_ATTRIBUTE << "(" << WORKOUT_ID <<  SEPERATOR << WORKOUT_DURATION << SEPERATOR << WORKOUT_TITLE << SEPERATOR << WORKOUT_INTESITY << SEPERATOR << WORKOUT_INTENSITY_CALORIES_BURNED << SEPERATOR << USER_UID_ATTRIBUTE << SEPERATOR << SEPERATOR << STRENGTH_TARGET_ZONE << ") VALUES" << std::endl;
    }
    
    void printAttributes(bool isLastPrint) {
        std::cout << std::setw(TAB_LENGTH) << "(" << workoutID << SEPERATOR << duration << SEPERATOR  << title << SEPERATOR << intensity << SEPERATOR << caloriesBurned << SEPERATOR << userID << SEPERATOR << targetZone << ")";
        isLastPrint ? std::cout << ";"  << std::endl : std::cout << "," << std::endl;
    }
};

#endif /* Strength_hpp */
