//
//  pants.hpp
//  homework-10
//
//  Created by Illya Starikov on 4/13/17.
//  Copyright © 2017 Illya Starikov. All rights reserved.
//

#ifndef pants_hpp
#define pants_hpp

#include "tailor.hpp"
#include "location.hpp"
#include "constants.h"

#include <iostream>
using namespace std;

class Tailor;

class Pants {
    Point location;

public:
    Pants();

    void placeMe(Town& placeMe);
    void chase(Tailor& tailor, Town& town);
    void kill(Tailor& tailor) const;

    int getX() const { return location.x; }
    int getY() const { return location.y; }
};

#endif /* pants_hpp */
