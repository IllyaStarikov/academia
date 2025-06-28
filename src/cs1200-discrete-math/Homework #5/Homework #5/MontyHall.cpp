//  COMP SCI 1200 Section B FS2015 Assignment
//
//  MontyHall.cpp
//  Homework #5
//
//  Created by Illya Starikov on 11/14/15.
//  Copyright © 2015 Illya Starikov. All rights reserved.
//

#include "MontyHall.hpp"
#include <stdlib.h> // srand, rand
#include <time.h>   // Time

MontyHallGame::MontyHallGame() {
    numberOfDoors = getInput("Number of Doors");
    numberOfGames = getInput("Number of Games");
}

void MontyHallGame::play() {
    int winningSpot, yourSpot, spotThatIsTakenAway;
    int switchCounter = 0, stayCounter = 0; // Winning counters

    for (int i = 0; i < numberOfGames; i++) {
        winningSpot = randomArbitrary(1, numberOfDoors);


        // Find A Spot To Take Away
        do {
            spotThatIsTakenAway = randomArbitrary(2, numberOfDoors);
        } while (spotThatIsTakenAway == winningSpot);

        // Find A Spot To Switch To That Isn't Taken Away
        do {
            yourSpot = randomArbitrary(2, numberOfDoors);
        } while (yourSpot == spotThatIsTakenAway);

        // Record The Results
        if (winningSpot == yourSpot) {
            switchCounter++;
        } else if (winningSpot == 1) {
            stayCounter++;
        }
    }

    reportTheResults(switchCounter, stayCounter);
}

void MontyHallGame::reportTheResults(const int switchCounter, const int stayCounter) {
    // Messy cout statements are as follows:
    // Output the wins, games, and percentage
    // Report which was most beneficial

    cout << "/--------------------Results--------------------/" << endl << endl;
    cout << "Switching Would Have Won: " << switchCounter << " / " << numberOfGames << " = " << calculatePercentage(switchCounter, numberOfGames) << "%" << endl;
    cout << "Staying Would Have Won: " << stayCounter << " / " << numberOfGames << " = " << calculatePercentage(stayCounter, numberOfGames) << "%" << endl;

    switchCounter > stayCounter ? cout << "Switching Was Most Beneficial!" : cout << "Staying Was Most Beneficial!";

    cout << endl << endl;

    cout << "/-----------------------------------------------/" << endl;
}

int MontyHallGame::getInput(const string descriptionOfInput) {
    int toReturn;

    cout << descriptionOfInput << ": ";
    cin >> toReturn;

    return toReturn;
}

int MontyHallGame::randomArbitrary(const int floor, const int ceiling) {
    return floor + rand() % (ceiling - floor + 1);
}

int MontyHallGame::round(const float toRound) {
    return static_cast<int>(toRound + .5);
}

int MontyHallGame::calculatePercentage(const int lhs, const int rhs) {
    return round((static_cast<float>(lhs) / rhs) * 100);
}