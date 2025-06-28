//
//  main.cpp
//  lab9
//
//  Created by Illya Starikov on 3/18/15.
//  Copyright (c) 2015 Illya Starikov. All rights reserved.
//

#include <iostream>
#include "lab9.h"

using namespace std;

int main()
{
  srand(static_cast<int>(time((NULL))));

  int intMainArray[cARRAY_LENGTH];
  bool boolDivisibleBy_2, boolDivisibleBy_3, boolDivisibleBy_4,
  boolDivisibleBy_5, boolDivisibleBy_6;

  funcGreetUser();
  funcPrintNumber(intMainArray, cARRAY_LENGTH);
  boolDivisibleBy_2 = funcDivisibleBy2(intMainArray, cARRAY_LENGTH);
  boolDivisibleBy_3 = funcDivisibleBy3(intMainArray, cARRAY_LENGTH);
  boolDivisibleBy_4 = funcDivisibleBy4(intMainArray, cARRAY_LENGTH);
  boolDivisibleBy_5 = funcDivisibleBy5(intMainArray, cARRAY_LENGTH);
  boolDivisibleBy_6 = funcDivisibleBy6(intMainArray, cARRAY_LENGTH);

  funcPrintResult(boolDivisibleBy_2, 2);
  funcPrintResult(boolDivisibleBy_3, 3);
  funcPrintResult(boolDivisibleBy_4, 4);
  funcPrintResult(boolDivisibleBy_5, 5);
  funcPrintResult(boolDivisibleBy_6, 6);

  funcGoodbye();
}
