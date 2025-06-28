//  COMP SCI 1200 Section B FS2015 Assignment
//
//  MontyHall.hpp
//  Homework #5
//
//  Created by Illya Starikov on 11/14/15.
//  Copyright © 2015 Illya Starikov. All rights reserved.
//

/*
-------------------- Constructor --------------------
Simply gets user input for the number of games and number of doors
*/

/*
-------------------- Play --------------------
Simulates the game based on the input given
*/

/*
-------------------- Report The Results --------------------
Prints out a statement, takes the results as parameters
*/

/*
-------------------- Random Arbitrary --------------------
Returns a random integer based on the floor (minimum) and ceiling (maximum.)
Takes two integers.
*/

/*
-------------------- Round --------------------
Takes a float, and rounds to integer.
*/

/*
-------------------- Calculate Percentage --------------------
Returns an integer percentage based on two integer.
*/


#ifndef MontyHall_hpp
#define MontyHall_hpp

#include <iostream>

using namespace std;

class MontyHallGame {
    int numberOfGames, numberOfDoors;

public:
    MontyHallGame();
    void play();
    void reportTheResults(const int switchCounter, const int stayCounter);

    int getInput(const string descriptionOfInput);

    // Maintenace Functions
    int randomArbitrary(const int floor, const int ceiling);
    int round(const float toRound);
    int calculatePercentage(const int lhs, const int rhs);
};

#endif /* MontyHall_hpp */
