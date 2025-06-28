//
//  tailor.cpp
//  homework-10
//
//  Created by Illya Starikov on 4/13/17.
//  Copyright © 2017 Illya Starikov. All rights reserved.
//

#include "tailor.hpp"

Tailor::Tailor(const string name, const char representationInTown) {
    this -> name = name;
    this -> representationInTown = representationInTown;

    money = randomArbitrary(MIN_TAILOR_MONEY, MAX_TAILOR_MONEY);
    health = TAILOR_START_HEALTH;

    location.x = TAILOR_START_X;
    location.y = TAILOR_START_Y;

    pantsCount = TAILOR_START_PANTS;
}

void Tailor::placeMe(Town& town) {
    Point emptySpace = town.findRandomEmptySpot();
    town.setElement(emptySpace.y, emptySpace.x, TAILOR_CHAR);

    location.x = emptySpace.x;
    location.y = emptySpace.y;
}

bool Tailor::randomWalk(Town& town, Bully& bully) {
    char result, directions[4] = { 'N', 'S', 'E', 'W' };
    int numberOfChoices = 4, choice;

    bool validPositionFound;

    Point randomPosition;
    // There's no eloquent solution to this, so this is the best I could come up with

    do {
        choice = randomArbitrary(0, 3); // 0..3, the four cardinal directions
        short north = 0, east = 0;

        switch (directions[choice]) {
            case 'N':
                north = 1;
                break;

            case 'S':
                north = -1;
                break;

            case 'E':
                east = 1;
                break;

            case 'W':
                east = -1;
                break;

            // This usually just handles X case
            default:
                break;
        }

        randomPosition.x = east + location.x;
        randomPosition.y = north + location.y;

        if (directions[choice] == 'X') {
            // Just stall.
        } else if (town.getElement(randomPosition.y, randomPosition.x) == EMPTY_SPACE) {
            validPositionFound = true;
        } else {
            numberOfChoices--;
            directions[choice] = 'X';
        }

    } while (!validPositionFound && numberOfChoices != 0);

    if (validPositionFound) {
        town.setElement(randomPosition.y, randomPosition.x, TAILOR_CHAR);
        town.setElement(location.y, location.x, EMPTY_SPACE);

        location = randomPosition;

        if (inRangeOf(town, HOUSE_CHAR) && randomChoiceBasedOnProbability(PROBABILITY_OF_PANTS_EXCHANGE)) {
            Point closestHouse = getClosestChar(town, HOUSE_CHAR);

            town.exchangePants(closestHouse.y, closestHouse.x);

            pantsCount--;
            money += TAILOR_MONEY_GAIN;
        }

        if (inRangeOf(town, BULLY_CHAR)) {
            bully.punch(*this, town);
            return true;
        }
    }

    return false;
}

void Tailor::getPunched(const int punchPower, Town& town) {
    money -= money*punchPower*0.01;
    health -= HEALTH_LOST_PER_PUNCH;

    // Goes flying
    town.setElement(location.y, location.x, ' ');
    placeMe(town);
}

bool Tailor::inRangeOf(const Town &town, const char characterToFind) const {
    const int x = location.x, y = location.y;

    // Gross but best I could do
    if (
        town.getElement(y + 1, x) == characterToFind ||  // North
        town.getElement(y - 1, x) == characterToFind || // South
        town.getElement(y, x + 1) == characterToFind || // East
        town.getElement(y, x - 1) == characterToFind // West
    ) {
        return true;
    }
    return false;
}

Point Tailor::getClosestChar(const Town &town, const char characterToFind) const {
    const int x = location.x, y = location.y;

    if (town.getElement(y + 1, x) == characterToFind) {
        return Point(x, y + 1);
    } else if (town.getElement(y - 1, x) == characterToFind) {
        return Point(x, y - 1);
    } else if (town.getElement(y, x + 1) == characterToFind) {
        return Point(x + 1, y);
    } else if (town.getElement(y, x - 1) == characterToFind) {
        return Point(x - 1, y);
    }

    return Point(-1, -1);
}

ostream& operator<<(ostream & os, const Tailor& tailor) {
    os << tailor.getName() << " is " << (tailor.isAlive() ? "alive" : "not alive") << " at (" << tailor.getLocation().x << ", " << tailor.getLocation().y << " with $" << tailor.getMoney() << ", " << tailor.getPantsCount() << " pant(s), and " << tailor.getHealth() << " health" << endl;

    return os;
}
