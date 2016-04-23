//
//  Workout.cpp
//  Random SQL Generator
//
//  Created by Illya Starikov on 4/17/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#include "Workout.hpp"
#include "Constants.h"

Workout::Workout() {
    duration = duration.randomDuration();
    intensity = randomArbitrary(0, INTENSITY_MAX);
    caloriesBurned = static_cast<double>(duration.totalMinutes()) * WORKOUTS_CALORIES_PER_MINUTE;
    workoutID = generateID();
}

void Workout::printInsert() {
    std::cout << "INSERT INTO " << WORKOUT_TABLE_NAME_ATTRIBUTE << "(" << workoutID << SEPERATOR << title << SEPERATOR << duration << SEPERATOR << intensity << SEPERATOR << caloriesBurned << ") VALUES" << std::endl;
}

void Workout::printAttributes(bool isLastPrint) {
    std::cout << std::setw(TAB_LENGTH) << "(" << title << SEPERATOR << duration << SEPERATOR << intensity << SEPERATOR << caloriesBurned << ")";
    isLastPrint ? std::cout << ";"  << std::endl : std::cout << "," << std::endl;
}

int Workout::generateID() {
    static int ID = 0;
    return ++ID;
}