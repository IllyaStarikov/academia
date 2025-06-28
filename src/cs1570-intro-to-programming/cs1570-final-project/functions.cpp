//
//  functions.cpp
//  homework-10
//
//  Created by Illya Starikov on 4/13/17.
//  Copyright © 2017 Illya Starikov. All rights reserved.
//

#include "functions.hpp"

// Return true or false depending on a certain probability of returning true
bool randomChoiceBasedOnProbability(const int probability) {
    return randomArbitrary(1, 100) < probability;
}
