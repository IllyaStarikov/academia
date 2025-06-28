//
//  lab9.h
//  lab9
//
//  Created by Illya Starikov on 3/18/15.
//  Copyright (c) 2015 Illya Starikov. All rights reserved.
//

#ifndef lab9__lab9
#define lab9__lab9

#include <iostream>
using namespace std;

// Consts
const int cARRAY_LENGTH = 5;

// Functions
/*
Description:    Greet the user
Pre-Condition:    None.
Post-Condition:   Side effects, cout statements.
*/
void funcGreetUser();
void funcPrintNumber(int intArrayOfRandoms[], int intSize);

/*
Description:    To check the divisibility of a number, by 2.
Pre-Condition:    intArrayOfRandoms must be intitilized as with intSize.
Post-Condition:   Return of a boolean value indicating if true ro false.
*/
bool funcDivisibleBy2(int intArrayOfRandoms[], int intSize);

/*
Description:    To check the divisibility of a number, by 3.
Pre-Condition:    intArrayOfRandoms must be intitilized as with intSize.
Post-Condition:   Return of a boolean value indicating if true ro false.
*/
bool funcDivisibleBy3(int intArrayOfRandoms[], int intSize);

/*
Description:    To check the divisibility of a number, by 4.
Pre-Condition:    intArrayOfRandoms must be intitilized as with intSize.
Post-Condition:   Return of a boolean value indicating if true ro false.
*/
bool funcDivisibleBy4(int intArrayOfRandoms[], int intSize);

/*
Description:    To check the divisibility of a number, by 5.
Pre-Condition:    intArrayOfRandoms must be intitilized as with intSize.
Post-Condition:   Return of a boolean value indicating if true ro false.
*/
bool funcDivisibleBy5(int intArrayOfRandoms[], int intSize);

/*
Description:    To check the divisibility of a number, by 6.
Pre-Condition:    intArrayOfRandoms must be intitilized as with intSize.
Post-Condition:   Return of a boolean value indicating if true ro false.
*/
bool funcDivisibleBy6(int intArrayOfRandoms[], int intSize);

/*
Description:    Greet the user
Pre-Condition:    Results and Dividend is valid.
Post-Condition:   Side effects, cout statements.
*/
void funcPrintResult(bool boolResultOfTest, int intDividend);

/*
Description:    Greet the user
Pre-Condition:    None.
Post-Condition:   Side effects, cout statements.
*/
void funcGoodbye();

// Utilities
/*
Description:     generate a random number.
Pre-Condition:    intFloor and intCeiling must be valid ints.
Post-Condition:   return of an int at random.
*/
int funcRandomNumberGenerator(int intFloor, int intCeiling);

#endif /* defined(__lab9__lab9__) */
