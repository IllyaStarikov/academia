//
//  constants.h
//  homework-10
//
//  Created by Illya Starikov on 4/13/17.
//  Copyright © 2017 Illya Starikov. All rights reserved.
//

#ifndef constants_h
#define constants_h

// MARK: Constants that probably will change
const int TOWN_SIZE = 25;
const int MIN_TOWN_SIZE = 4;

const int BULLY_ARRAY_COUNT = 10;
const int HOUSE_COUNT = 70;
const int PERCENT_HOUSE_CLUMP = 50;

const int BULLY_PUNCH_MAX = 50;
const int BULLY_PUNCH_MIN = 30;

const int BULLY_PROBABILITY_MAX = 80;

const int MAX_STEPS = 1000;
const int BULLY_COUNT = 10;
const int PHANTOM_PANTS_COUNT = 3;

const int HEALTH_LOST_PER_PUNCH = 10;

const int TAILOR_START_PANTS = 50;
const int TAILOR_MONEY_GAIN = 10;

// MARK: Constants that probably won't change
const int EMPTY_SPACE = ' ';
const char WALL_CHAR = 'W';
const char HOUSE_CHAR = 'H';
const char BULLY_CHAR = 'B';
const char PANTS_CHAR = 'P';
const char TAILOR_CHAR = 'M';

const int TAILOR_START_HEALTH = 100;

const int TAILOR_START_X = -1;
const int TAILOR_START_Y = -1;

const int PROBABILITY_OF_PANTS_EXCHANGE = 70;

const int MIN_TAILOR_MONEY = 20;
const int MAX_TAILOR_MONEY = 40;

// MARK: Constants just for readbility
const int MAX_TOWN_SIZE = TOWN_SIZE;

#endif /* constants_h */
