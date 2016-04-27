//
//  Cardio.hpp
//  Random SQL Generator
//
//  Created by Illya Starikov on 4/24/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#ifndef Cardio_hpp
#define Cardio_hpp

#include <stdio.h>

#include "Workout.hpp"
#include "Constants.h"


class CardioWorkout : Workout {
    int averageHeartRate, averageSpeed, distanceCovered;
    
public:
    CardioWorkout();
    void printInsert();
    void printAttributes(bool isLastPrint);
    
};

#endif /* Cardio_hpp */
