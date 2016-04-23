//
//  main.cpp
//  Random SQL Generator
//
//  Created by Illya Starikov on 4/10/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#include <iostream>

#include "Groups.hpp"
#include "Workout.hpp"
#include "Users.hpp"
#include "Measurement.hpp"

#include "Functions.hpp"
#include "Constants.h"

int main(int argc, const char * argv[]) {
    Group groups[GROUP_COUNT];
    Workout workouts[WORKOUT_COUNT];
    Users users[USER_COUNT];
	Weight weight[WEIGHT_COUNT];
	Arm arm[ARM_COUNT];
	Chest chest[CHEST_COUNT];

    printInsertAndAttributes(groups, GROUP_COUNT);
    printInsertAndAttributes(workouts, WORKOUT_COUNT);
	printInsertAndAttributes(users, USER_COUNT);
}
