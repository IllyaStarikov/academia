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

class StrengthWorkout : Workout {
    std::string exercise, targetZone;
    
public:
    StrengthWorkout() {
        
    }
};

#endif /* Strength_hpp */
