//
//  lab9.cpp
//  lab9
//
//  Created by Illya Starikov on 3/18/15.
//  Copyright (c) 2015 Illya Starikov. All rights reserved.
//

#include "lab9.h"

#include <iostream>
using namespace std;


void funcGreetUser()
{
  cout << endl <<
  "Welcome to the Divisibility Test!!!" << endl;
}
void funcPrintNumber(int intArrayOfRandoms[], int intSize)
{
  int i = 0; //since the first number cannot be 0, have to brute force it
  intArrayOfRandoms[i] = funcRandomNumberGenerator(1, 9);

  do
  {
    intArrayOfRandoms[i] = funcRandomNumberGenerator(0, 9);
    i++;
  } while (i < intSize);

  cout << "The Generated Number is ";
  for (int i = 0; i < intSize; i++)
  {
    cout << intArrayOfRandoms[i];
  }
  cout << endl << endl;
  return;
}

bool funcDivisibleBy2(int intArrayOfRandoms[], int intSize)
{
  bool boolDivisible;

  // I could have made this boolDivisible = ternary
  // but for this case, there is enough going on, it's print it
  // as read
  // likewise for further ternaries
  ((intArrayOfRandoms[intSize - 1] % 2) == 0)?
  boolDivisible = true: boolDivisible = false;

  return boolDivisible;
}

bool funcDivisibleBy3(int intArrayOfRandoms[], int intSize)
{
  bool boolDivisible;
  int intTotal;

  for (int i = 0; i < intSize; i++)
  {
    intTotal += intArrayOfRandoms[i];
  }

  ((intTotal % 3) == 0)? boolDivisible = true: boolDivisible = false;

  return boolDivisible;
}

bool funcDivisibleBy4(int intArrayOfRandoms[], int intSize)
{
  bool boolDivisible;
  int intResult = 0;
  // intSize - 2 because array starts at zero, so the second to last is -2 of size
  // likeweise for intsize
  intResult = (intArrayOfRandoms[intSize - 2] * 10) + intArrayOfRandoms[intSize - 1];

  ((intResult % 4) == 0)? boolDivisible = true: boolDivisible = false;

  return boolDivisible;
}

bool funcDivisibleBy5(int intArrayOfRandoms[], int intSize)
{
  bool boolDivisible;

  ((intArrayOfRandoms[intSize - 1] % 5) == 0)? boolDivisible = true: boolDivisible = false;

  return boolDivisible;
}

bool funcDivisibleBy6(int intArrayOfRandoms[], int intSize)
{
  bool boolDivisible;
  int intResult = 0;

  for (int i=0; i < intSize; i++)
  {
    intResult = intResult* 10 + intArrayOfRandoms[i];
  }

  ((intResult % 6) == 0)? boolDivisible = true: boolDivisible = false;

  return boolDivisible;
}

void funcPrintResult(bool boolResultOfTest, int intDividend)
{
  // Due to my lengthy variable names, splitting this up
  // into a ternary would just be unreadable with the 80 column rule
  if (boolResultOfTest == true)
  {
    cout << "Divisible by " << intDividend;
  }
  else if (boolResultOfTest == false)
  {
    cout << "Not Divisible by " << intDividend;
  }
  cout << endl; // more inform to put this at the end

  return;
}

void funcGoodbye()
{
  cout << "Thanks for using our Test." << endl << endl;
}
// Utilities
int funcRandomNumberGenerator(int intFloor, int intCeiling)
{
  return (intFloor + (rand() % (intCeiling - intFloor + 1)));
}