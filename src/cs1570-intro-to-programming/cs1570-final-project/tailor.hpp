//
//  tailor.hpp
//  homework-10
//
//  Created by Illya Starikov on 4/13/17.
//  Copyright © 2017 Illya Starikov. All rights reserved.
//

#ifndef tailor_hpp
#define tailor_hpp

#include "constants.h"
#include "location.hpp"
#include "town.hpp"
#include "functions.hpp"
#include "bully.hpp"
#include "pants.hpp"

#include <iostream>

using namespace std;

class Bully;

class Tailor {
    string name;
    char representationInTown;
    Point location;

    long money;
    short health, pantsCount;

public:
    Tailor(const string name, const char representationInTown);

    void placeMe(Town& town);
    bool randomWalk(Town& town, Bully& bully);

    void getPunched(const int punchPower, Town& town);
    void exchangePants() {
        pantsCount--;
    }

    bool inRangeOf(const Town &town, const char characterToFind) const;
    Point getClosestChar(const Town &town, const char characterToFind) const;

    friend ostream& operator<<(ostream & os, const Tailor& tailor);

    bool isAlive() const { return health > 0; }
    bool allPantsAreTraded() const { return pantsCount <= 0; }
    bool isBroke() const { return money <= 0; }

    string getName() const { return name; }
    int getMoney() const { return money; }
    Point getLocation() const { return location; }
    short getPantsCount() const { return pantsCount; }
    char getRepresentation() const { return representationInTown; }

    short getHealth() const { return health; }
    void kill() { health = 0; }

};


#endif /* tailor_hpp */
