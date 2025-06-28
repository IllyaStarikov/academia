//
//  town.hpp
//  homework-10
//
//  Created by Illya Starikov on 4/13/17.
//  Copyright © 2017 Illya Starikov. All rights reserved.
//

#ifndef town_hpp
#define town_hpp

#include "constants.h"
#include "functions.hpp"
#include "location.hpp"

#include <iostream>

using namespace std;

class Town {
    Location grid[TOWN_SIZE][TOWN_SIZE];

    short size;
    short numberOfHouses;
    short numberOfBullies;

    void insertHorizontalWall(const int startX, const int finishX, const int y);
    void insertVerticalWall(const int startY, const int finishY, const int x);
    bool inBoundsOfArray(const int x, const int y) const;
    Point getLocationOfChar(const char character) const;

public:
    Town();
    Town(const short size, const short numberOfHouses, const short numberOfBullies);

    void clear();
    void build(const short numberOfHouses, const short numberOfBullies);

    Point findRandomEmptySpot() const;
    void exchangePants(const int row, const int column);

    int numberOfPants() const;

    friend ostream& operator<<(ostream & os, const Town& town);


    // MARK: Getters/Setters
    short getSize() const { return size; }
    short getNumberOfBullies() const { return numberOfHouses; }

    char getElement(const int row, const int column) const {
        // If in bounds, return the element, if not.. just return empty
        return inBoundsOfArray(column, row) ? grid[row][column].cell : 'X';
    }

    void setElement(const int row, const int column, const char element) {
        if (inBoundsOfArray(column, row)) {
            grid[row][column].cell = element;
        }
    }

};


#endif /* town_hpp */
