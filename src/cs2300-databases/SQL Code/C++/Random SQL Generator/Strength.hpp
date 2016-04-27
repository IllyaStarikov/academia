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
    void printInsert();
    void printAttributes(bool isLastPrint);
};

#endif /* Strength_hpp */
