//
//  main.cpp
//  homework-10
//
//  Created by Illya Starikov on 4/13/17.
//  Copyright © 2017 Illya Starikov. All rights reserved.
//

#include <iostream>
#include <unistd.h>

#include "tailor.hpp"
#include "location.hpp"
#include "town.hpp"
#include "pants.hpp"
#include "bully.hpp"

const string TABS = "\t\t\t";

int main(int argc, const char * argv[]) {
    srand(time(NULL));

    Town springfield = Town(MAX_TOWN_SIZE, HOUSE_COUNT, BULLY_COUNT);
    Tailor milhouse = Tailor("Milhouse", 'M');

    Bully bullies[BULLY_COUNT];
    Pants phantomPants[PHANTOM_PANTS_COUNT];

    int steps = 0, numberOfPants = 0;
    bool milhouseGotPunched = false, killedByPants = false;

    milhouse.placeMe(springfield);

    do {
        milhouseGotPunched = milhouse.randomWalk(springfield, bullies[0]);

        if (milhouseGotPunched && numberOfPants < PHANTOM_PANTS_COUNT) {
            phantomPants[numberOfPants].placeMe(springfield);
            numberOfPants++;
        }

        for (int i = 0; i < numberOfPants && milhouse.isAlive(); i++) {
            if (milhouse.inRangeOf(springfield, 'P')) {
                phantomPants[i].kill(milhouse);
                killedByPants = true;
            } else {
                phantomPants[i].chase(milhouse, springfield);
            }
        }
        cout << springfield;

        steps++;
        usleep(100000);
    } while (milhouse.isAlive() && steps < MAX_STEPS && !milhouse.allPantsAreTraded() && !milhouse.isBroke());

    cout << "\n\n";
    cout << ".----------------.  .----------------.  .-----------------.\n";
    cout << "| .--------------. || .--------------. || .--------------. |\n";
    cout << "| |  _________   | || |     _____    | || | ____  _____  | |\n";
    cout << "| | |_   ___  |  | || |    |_   _|   | || ||_   \\|_   _| | |\n";
    cout << "| |   | |_  \\_|  | || |      | |     | || |  |   \\ | |   | |\n";
    cout << "| |   |  _|      | || |      | |     | || |  | |\\ \\| |   | |\n";
    cout << "| |  _| |_       | || |     _| |_    | || | _| |_\\   |_  | |\n";
    cout << "| | |_____|      | || |    |_____|   | || ||_____|\\____| | |\n";
    cout << "| |              | || |              | || |              | |\n";
    cout << "| '--------------' || '--------------' || '--------------' |\n";
    cout << "'----------------'  '----------------'  '----------------' \n";


    cout << "/************************************************************************/\n\n";
    if (steps >= MAX_STEPS || milhouse.allPantsAreTraded()) {
        cout << TABS << "VICTORY!\n";
    } else {
        cout << TABS << "DEATH BY ";
        if (killedByPants) {
            cout << "PANTS!";
        } else if (milhouse.isBroke()) {
            cout << "STARVATION (LOST MONEY)";
        } else {
            cout << "BULLIED TO DEATH";
        }
        cout << "\n";
    }


    cout << TABS << "Damage Report\n\n";
    cout << TABS << milhouse.getName() << " survived:\n";
    cout << TABS << steps << " Steps\n";
    cout << TABS << numberOfPants << " Number Of Pants\n\n";

    cout << TABS << "Final Money Count: " << milhouse.getMoney() << "\n";
    cout << TABS << "Final Health: " << milhouse.getHealth() << "\n";
    cout << "/************************************************************************/\n\n";
}
