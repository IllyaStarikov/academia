//
//  bully.cpp
//  homework-10
//
//  Created by Illya Starikov on 4/13/17.
//  Copyright © 2017 Illya Starikov. All rights reserved.
//

#include "bully.hpp"

Bully::Bully() {
    name = "Price";

    punchPower = randomArbitrary(BULLY_PUNCH_MIN, BULLY_PUNCH_MAX);
    punchProbability = BULLY_PROBABILITY_MAX;
}

void Bully::punch(Tailor& tailor, Town& town) const {
    if (randomChoiceBasedOnProbability(punchProbability)) {
        tailor.getPunched(punchPower, town);
    } else {
        wittyMessage();
    }
}

void Bully::wittyMessage() const {
    cout << name << " yells \"Get back here you shit\" as you flee!";
}
