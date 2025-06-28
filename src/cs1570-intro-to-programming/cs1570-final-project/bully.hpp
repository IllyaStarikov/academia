//
//  bully.hpp
//  homework-10
//
//  Created by Illya Starikov on 4/13/17.
//  Copyright © 2017 Illya Starikov. All rights reserved.
//


#ifndef bully_hpp
#define bully_hpp

#include <iostream>

#include "tailor.hpp"
#include "location.hpp"
#include "constants.h"

class Tailor;

class Bully {
    string name;
    short punchPower, punchProbability;
    Point location;

public:
    Bully();

    void punch(Tailor& tailor, Town& town) const;
    void wittyMessage() const;
};

#endif /* bully_hpp */
