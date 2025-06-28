//Programmers: ALEX ANDROFF & ILLYA STARIKOV  DATE: 3/21/15
//Class: CS1570                               Section: A
//Filename: main.cpp
//Purpose: Use different tests to determine the identity of a missing cow.

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "Functions.h"
#include "Constants.h"
using namespace std;

int main()
{
    for (int i = 0; i < 20000000; i ++) {
  srand(static_cast<int>(time(NULL)));

  int intLocationOfMatchingCow;
  bool boolMatchFound;

  SMissingCow mainMissingCow[cMISSING_COWS];
  SMatchingCow mainFoundCow;

  string strNameOfCows[cMISSING_COWS] =
  {
      "Bouncing_Betty",
      "Ole_Bessy",
      "Chicken_Little",
      "Spot",
      "SeaBriscuit"
  };

  funcNameAssignment(mainMissingCow, strNameOfCows, cMISSING_COWS);

  funcFirstTest_RandomArrayAssignment_MissingCows(mainMissingCow,
                          cMISSING_COWS,
                          cDNA_MISSINGCOWSLENGTH);
  funcSecondTest_RandomArrayAssignment_MissingCows(mainMissingCow,
                           cMISSING_COWS,
                           cNUMBER_OF_TEETH);

  funcGreetUser();

  for (int i = 0; i < cMAIN_ITERATIONS; i++)
  {

    funcFirstTest_RandomArrayAssignment_FoundCow(mainFoundCow,
                           cDNA_MATCHINGCOWLENGTH);
    funcSecondTest_RandomArrayAssignment_FoundCow(mainFoundCow,
                            cNUMBER_OF_TEETH);
    boolMatchFound = funcFirstTest(mainFoundCow,
                    cDNA_MATCHINGCOWLENGTH,
                     mainMissingCow,
                    cMISSING_COWS,
                     cDNA_MISSINGCOWSLENGTH,
                     intLocationOfMatchingCow);
    funcFirstTestResults(boolMatchFound, mainFoundCow, mainMissingCow,
                         intLocationOfMatchingCow);

    if (boolMatchFound == false)
    {

      boolMatchFound = funcSecondTest(mainFoundCow, mainMissingCow,
                      cMISSING_COWS, cNUMBER_OF_TEETH,
                      intLocationOfMatchingCow);
      funcSecondTestResults(boolMatchFound, mainFoundCow, mainMissingCow,
                            intLocationOfMatchingCow);
    }
  }

  funcFarewells();
    }
  return 0;
}

