//
//  Workout.hpp
//  Random SQL Generator
//
//  Created by Illya Starikov on 4/17/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#ifndef Workout_hpp
#define Workout_hpp

#include <iostream>
#include <iomanip>

#include "Constants.h"
#include "Functions.hpp"
#include "Duration.hpp"

class Workout {
protected:
    Duration duration;
    int intensity, workoutID, userID;
    double caloriesBurned;
    std::string title;
    
public:
    Workout();
    void printInsert();
    void printAttributes(bool isLastPrint);
    int generateID();
};

#endif /* Workout_hpp */
