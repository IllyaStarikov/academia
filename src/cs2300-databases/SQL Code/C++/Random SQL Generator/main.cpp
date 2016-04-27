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
#include "Strength.hpp"
#include "Cardio.hpp"
#include "Members.hpp"

#include "Functions.hpp"
#include "Constants.h"

int main(int argc, const char * argv[]) {
    srand(static_cast<int>(time(NULL)));
    
    Group groups[GROUP_COUNT];
    CardioWorkout cardio[WORKOUT_COUNT];
    StrengthWorkout strength[WORKOUT_COUNT];
    Users users[USER_COUNT];
	Weight weight[WEIGHT_COUNT];
	Arm arm[ARM_COUNT];
	Chest chest[CHEST_COUNT];
    Members members[MEMBERS_COUNT];
    
    printInsertAndAttributes(users, USER_COUNT);
    printInsertAndAttributes(groups, GROUP_COUNT);
    printInsertAndAttributes(members, MEMBERS_COUNT);
    printInsertAndAttributes(cardio, WORKOUT_COUNT);
    printInsertAndAttributes(strength, WORKOUT_COUNT);
    printInsertAndAttributes(weight, WEIGHT_COUNT);
    printInsertAndAttributes(arm, ARM_COUNT);
    printInsertAndAttributes(chest,CHEST_COUNT);
}
