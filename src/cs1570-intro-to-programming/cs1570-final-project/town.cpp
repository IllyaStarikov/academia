//
//  town.cpp
//  homework-10
//
//  Created by Illya Starikov on 4/13/17.
//  Copyright © 2017 Illya Starikov. All rights reserved.
//

#include "town.hpp"

// MARK: Constructors
Town::Town() {
    size = 0;
    numberOfHouses = 0;
    numberOfBullies = 0;
}

Town::Town(const short size, const short numberOfHouses, const short numberOfBullies) {
    this -> size = size;
    this -> numberOfHouses = numberOfHouses;
    this -> numberOfBullies = numberOfBullies;

    clear();
    build(numberOfHouses, numberOfBullies);
}

// MARK: Private Methods
// Probably just used for maintenance and stuff

void Town::insertHorizontalWall(const int startX, const int finishX, const int y) {
    // Check to see if the points are in bounds. If they're not, prematurely return.
    if (!inBoundsOfArray(startX, y) || !inBoundsOfArray(finishX, y)) {
        return;
    }

    for (int i = startX; i <= finishX; i++) {
        grid[y][i].cell = WALL_CHAR;
    }
}

// Refer to the other insertion for documentation
void Town::insertVerticalWall(const int startY, const int finishY, const int x) {
    if (!inBoundsOfArray(x, startY) || !inBoundsOfArray(x, finishY)) {
        return;
    }

    for (int i = startY; i <= finishY; i++) {
        grid[i][x].cell = WALL_CHAR;
    }
}

bool Town::inBoundsOfArray(const int x, const int y) const {
    bool xInBounds = x >= 0 && x <= size - 1;
    bool yInBounds = y >= 0 && y <= size - 1;

    return xInBounds && yInBounds;
}


Point Town::getLocationOfChar(const char character) const {
    // Define 1 because % 0 is undefined
    const int offsetI = randomArbitrary(4, size - 1), offsetJ = randomArbitrary(4, size - 1);
    for (int i = offsetI + 1; i != offsetI;  i++) {
        for (int j = offsetJ + 1; j != offsetJ ; j++) {
            if (grid[i][j].cell == character) {
                cout << "X " << i%offsetI << "Y " << j%offsetJ <<endl ;
                return Point(j, i);
            }

            if (i == size - 1) {
                i = 0;
            }

            if (j == size - 1) {
                j = 0;
            }
        }
    }

    return Point(-1, -1);
}

// MARK: Public Methods
void Town::clear() {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            grid[i][j].cell = EMPTY_SPACE;
            grid[i][j].exchangedPants = false;
        }
    }
}

void Town::build(const short numberOfHouses, const short numberOfBullies) {
    short x, y;
    bool housePlaced;

    // Build the walls
    insertHorizontalWall(0, size - 1, 0);
    insertHorizontalWall(0, size - 1, size - 1);

    insertVerticalWall(0, size - 1, 0);
    insertVerticalWall(0, size - 1, size - 1);

    // Distribute the houses

    Point location;
    for (int i = 0; i < numberOfHouses*(100-PERCENT_HOUSE_CLUMP)*.01; i++) {
        Point houseLocation = findRandomEmptySpot();
        grid[houseLocation.y][houseLocation.x].cell = HOUSE_CHAR;
    }

    for (int i = 0; i < numberOfHouses*PERCENT_HOUSE_CLUMP*.01; i++) {
        do {
            location = getLocationOfChar(HOUSE_CHAR);

            if (grid[location.y + 1][location.x].cell == EMPTY_SPACE) {
                grid[location.y + 1][location.x].cell = HOUSE_CHAR;
                housePlaced = true;
            } else if (grid[location.y - 1][location.x].cell == EMPTY_SPACE) {
                grid[location.y - 1][location.x].cell = HOUSE_CHAR;
                housePlaced = true;
            } else if (grid[location.y][location.x + 1].cell == EMPTY_SPACE) {
                grid[location.y][location.x + 1].cell = HOUSE_CHAR;
                housePlaced = true;
            } else if (grid[location.y][location.x - 1].cell == EMPTY_SPACE) {
                grid[location.y][location.x - 1].cell = HOUSE_CHAR;
                housePlaced = true;
            } else {
                housePlaced = false;
            }
        } while (!housePlaced);
    }

    for (int i = 0; i < numberOfBullies; i++) {
        Point bullyLocation = findRandomEmptySpot();
        grid[bullyLocation.y][bullyLocation.x].cell = BULLY_CHAR;
    }
}

Point Town::findRandomEmptySpot() const {
    Point point;

    do {
        point.x = randomArbitrary(0, size - 1);
        point.y = randomArbitrary(0, size - 1);
    } while (grid[point.y][point.x].cell != EMPTY_SPACE);

    return point;
}

void Town::exchangePants(const int row, const int column) {
    if (grid[row][column].cell == HOUSE_CHAR && !grid[row][column].exchangedPants) {
        cout << "Pants got exchanged!\n";
        grid[row][column].exchangedPants = true;
    }
}

int Town::numberOfPants() const {
    int pantsCount = 0;

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (grid[i][j].cell == PANTS_CHAR) {
                pantsCount++;
            }
        }
    }

    return pantsCount;
}

ostream& operator<<(ostream & os, const Town& town) {
    for (int i = 0; i < town.getSize(); i++)
        os << "----";

    os << "--\n";
    for (int i = 0; i < town.getSize(); i++) {

        for (int j = 0; j < town.getSize(); j++) {
            char object = town.getElement(i, j);
            os << "| ";
            switch (object) {
                case HOUSE_CHAR:
                    os << "\e[93m" << object << "\e[0m";
                    break;

                case BULLY_CHAR:
                    os << "\e[1;31m" << object << "\e[0m";
                    break;

                case WALL_CHAR:
                    os << "\e[1;34m" << object << "\e[0m";
                    break;

                case 'P':
                    os << "\e[0;32m" << object << "\e[0m";
                    break;

                default:
                    os << object;

            }
            os << " ";
        }
        os << "|"  << endl;
        for (int i = 0; i < town.getSize(); i++)
            os << "----";

        os << "--\n";
    }

    return os;
}
