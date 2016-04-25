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