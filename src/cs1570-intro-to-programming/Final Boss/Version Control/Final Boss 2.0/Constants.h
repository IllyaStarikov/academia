// Programmers: Illya Starikov and Alex Androff           Date: 04/17/15
// File: Constants.h                                      Class: CS1570A
// Purpose: Specify constants for the entire program

#ifndef Final_Boss_Constants_h
#define Final_Boss_Constants_h

const char NULL_TERMINATING_CHAR = '\0';


/*--------------------MAIN/FUNCTIONS--------------------*/
const int NUMBER_OF_RESIDENTS = 25;
const int MEETINGS_PER_DAY = 4;
const std::string MEETING_TIMES[MEETINGS_PER_DAY] = {
  " 9:30 AM", "12:00 PM", " 3:00 PM", " 7:30 PM"
};
const int RESIDENTS_PER_MEETING = 2;

const int MAX_NUMBER_OF_ROOM_SEARCHES = 10;
const int FIRST_DAY_DEFAULT = 4;

/*--------------------Resident--------------------*/
// Constructors
const int DEFAULT_ISALIVE = true;
const int DEFAULT_ISMURDERER = false;

const int HAIR_MIN = 0;
const int HAIR_MAX = 10;

// DNA Random Assignment
const int NUMBER_OF_DNA_MEMBERS = 4;
const char DNA_MEMBERS[NUMBER_OF_DNA_MEMBERS] = {'C','T','G','A'}; // MUST MATCH DECLARATION LENGTH
const float DNA_PERCENTAGES[NUMBER_OF_DNA_MEMBERS] = { .30, .20, .15, .35}; // MUST ADD UP TO 1.0


/*--------------------Crime Room--------------------*/
const float CHANCE_OF_MURDER = .1; // Out of 1, 0 < x <= 1.00


/*--------------------Forensic Data--------------------*/
const int LENGTH_OF_DNA = 128;
const int LENGTH_OF_FINGERPRINT_ARRAY = 8;
const int HEIGHT_OF_FINGERPRINT_ARRAY = 8;

const int FINGERPRINT_SIZE = LENGTH_OF_FINGERPRINT_ARRAY * HEIGHT_OF_FINGERPRINT_ARRAY; // Simple and intuitive but useful.

const int NUMBER_OF_FINGERPRINT_MEMBERS = 2; // Falls apart past two, keep that in mind.
const char FINGERPRINT_MEMBERS[NUMBER_OF_FINGERPRINT_MEMBERS] = {' ', '*'};
const int NUMBER_OF_STARS = 40; // THIS SHOULD BE LESS THAN LENGTH * WIDTH
const float CHANCE_OF_ASSIGNMENT = .25; // longer loop, but better distibution.

const int LOOPS_MIN = 0;
const int ARCHES_MIN = 0;
const int WHIRLES_MIN = 0;

const int LOOPS_MAX = 5;
const int ARCHES_MAX = 5;
const int WHIRLES_MAX = 5;

/*--------------------CSI Agent--------------------*/
const std::string CSI_AGENT_NAME = "Who Dunnit";

// Corruptions
const int MIN_HAIR_CORRUPTION = -2;
const int MAX_HAIR_CORRUPTION = 2;

const int DNA_CORRUPTION_LENGTH = 15;
const char DNA_CORRUPTION_CHAR = '-';

const int FINGERPRINT_CORRUPTION_LENGTH = 5;
// loops, arches, whirls;
const int LOOP_MIN_CORRUPTION = -1;
const int LOOP_MAX_CORRUPTION = 1;

const int ARCH_MIN_CORRUPTION = -1;
const int ARCH_MAX_CORRUPTION = 1;

const int WHIRL_MIN_CORRUPTION = -1;
const int WHIRL_MAX_CORRUPTION = 1;

const float PERP_SEARCH_SUCCESS = .90;

// OVERALL SCORE FORMULA
const float DNA_SCORE_MULTIPLIER = .60;
const float FINGERPRINT_SCORE_MULTIPLIER = 0.30;
const float HAIR_SCORE_MULTIPLIER = .10;

// Fingerprint Score
const float MATCHING_STARS_MULTIPLIER = .70;

const float LOOPS_COMPARISON_ADDER = .1;
const int LOOPS_COMPARISON_MARGIN = 1;

const float ARCHES_COMPARISON_ADDER = .1;
const int ARCHES_COMPARISON_MARGIN = 1;

const float WHIRLES_COMPARISON_ADDER = .1;
const int WHIRLES_COMPARISON_MARGIN = 1;

// Hair Score
const float HAIR_IDENTICAL = .8;
const float HAIR_OFF_BY_ONE = .6;
const float HAIR_OFF_BY_TWO = .5;
const float HAIR_OFF_BY_THREE_OR_MORE = 0.0; // I know this seems redundant, but..
// For some strange reason i feel like Price is going to change all of the constants
// at the last minute.. so i'm not taking any chances.


/*--------------------Judicial Class--------------------*/
// Illya Starikov created these consants.
// All punishment should be dealt to him.
const std::string DEFAULT_JUDGE = "Adam Bowers"; // The judge, the jury, and the executioner.
const int DEFAULT_CONVICTION_RATE = 95; // Ironically, about the average on my homework.


#endif
