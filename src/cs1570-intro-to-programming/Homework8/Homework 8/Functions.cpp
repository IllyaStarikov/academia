//Programmers: ALEX ANDROFF & ILLYA STARIKOV  DATE: 3/21/15
//Class: CS1570                               Section: A
//Filename: functions.h
//Purpose: Use different tests to determine the identity of a missing cow.

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include "Functions.h"
#include "Constants.h"

using namespace std;

void funcGreetUser()
{
  cout << endl << endl <<
  "Welcome To Cowculator, The Premier Cow Matcher"
  << endl << endl;
  return;
}

void funcNameAssignment(SMissingCow scowMissingCowToName[], string strNames[],
  const int intSizeOfArray) {
    for (int i = 0; i < intSizeOfArray; i++)
    {
    scowMissingCowToName[i].m_strName = strNames[i];
    }
    return;
}

bool funcFirstTest(SMatchingCow scowToMatch,
                   const int intSizeOfMatchingCowDNA,
                   SMissingCow scowMissingCows[],
                   const int intSizeOfMissingCows,
                   const int intSizeOfMissingCowDNA,
                   int intGreatestMatchingCow)
{

  bool boolMatch;
  int intResults[cMISSING_COWS];
  float floGreatestPercentage;

  char charMissingCow_TempArray[cDNA_MISSINGCOWSLENGTH];
  int intLargestAccuracyOfSingleArrayItem, intAccuracyCounter;

  /*
   Three counters, two for counters and one do while'
   For Counters:
   j = Array Counter
   i = Array Cells

   A charTempArray is created to be the comparison and throwaway C-String.
   It is used for manipulation.

   To ensure to not walk off the array,
   the two the values are subtracted from each other.
   Absolute valued *abs()* to ensure a comparison would still happen,
   no matter which value is greater.

   If the scowToMatch passes the NULL Test
   (evaluates if there are any NULLs in the C-String member),
   it evaluates the array to check for possible matches.
   If not, the entire array returns NULL characters (0s).

   The evaluation process is as follows:
   - First, check to see if the scowToMatch's C-String matches the
   charTempArray to a specified length. Starts with 0, increments by one.
   - Second, ternary. Match Found = increment the counter. Match *not* Found:
   keep the accuracy. It's more of an indicator more than anything else.
   - Third, check to see if the counter is larger than the largest
   the counter has *ever reached. If so, the current counter is assigned
   to the largest accuracy.

   When no match is found, the temporary regresses by a single character.
   This is the most efficient away of ensuring the strncmp works,
   since you cannot call the function from a certain letter of a specified
   string.

   Stores the values, and returns if there has been a match after the
   specified number of iterations.
   */

  for (int j = 0; j < intSizeOfMissingCows; j++)
  {
    intLargestAccuracyOfSingleArrayItem = 0;
    if (funcFirstTest_NULLTest(scowToMatch, intSizeOfMatchingCowDNA) ==
      false)
    {
      intAccuracyCounter = 0;
    }
    else
    {

      strncpy(charMissingCow_TempArray, scowMissingCows[j].m_charDNA,
          intSizeOfMissingCowDNA);
      for (int i = 0; i < funcAbs(intSizeOfMissingCowDNA -
                  intSizeOfMatchingCowDNA); i++)
      {
        intAccuracyCounter = 0;
        do
        {
          boolMatch = (strncmp(scowToMatch.m_charDNA,
                     charMissingCow_TempArray,
                     intAccuracyCounter)) == 0 ?
          true : false;
          boolMatch ? ++intAccuracyCounter : intAccuracyCounter;
          intLargestAccuracyOfSingleArrayItem = (intAccuracyCounter >
                    intLargestAccuracyOfSingleArrayItem) ?
          intAccuracyCounter : intLargestAccuracyOfSingleArrayItem;
        } while (boolMatch == true);
        funcFirstTest_RegressCharacters(charMissingCow_TempArray,
                        intSizeOfMissingCowDNA);
      }
    }
    intResults[j] = intLargestAccuracyOfSingleArrayItem;
  }

  intGreatestMatchingCow = funcFirstTest_HighestPercentageCow(intResults,
                            intSizeOfMissingCows);
  floGreatestPercentage = (static_cast<float>
  (intResults[intGreatestMatchingCow]) / intSizeOfMatchingCowDNA) * 100.0;
  return (floGreatestPercentage > cFIRSTTEST_SUCCESSPERCENT);
}

int funcAbs(const int x) {
  return (x < 0) ? - x : x;
}

bool funcFirstTest_NULLTest(SMatchingCow scowToMatch,
              const int intSizeOfMatchingCowDNA)
{
  bool boolNULLTest;
  int i = 0;
  do
  {
    boolNULLTest = (scowToMatch.m_charDNA[i] == cNULL_CHAR) ? false : true;
    i++;
  } while (i < intSizeOfMatchingCowDNA && boolNULLTest == true);

  return boolNULLTest;
}

void funcFirstTest_RegressCharacters(char charTempArray[],
  const int intSizeOfArray)
{
  for (int i = 0; i < intSizeOfArray; i++)
  {
    charTempArray[i] = charTempArray[i+1];
  }

  return;
}

int funcFirstTest_HighestPercentageCow(const int intAccuracy[],
  const int intSizeOfArray)
{
  int intGreatest = 0, intGreatestAccuracy = 0;
  for (int i = 0; i < intSizeOfArray; i++)
  {
    // to ensure not walking off the array
    intGreatest = (intAccuracy[i] > intGreatestAccuracy) ? i : intGreatest;
    intGreatestAccuracy = (intAccuracy[i] > intGreatestAccuracy) ?
    intAccuracy[i] : intGreatestAccuracy;
  }

  return intGreatest;
}

void funcFirstTest_RandomArrayAssignment_MissingCows(
                                                     SMissingCow scowToPass[],
                                                     const int intSizeOfArray,
                                                     const
                                                     int intSizeOfDNAMembers)
{
  int intPositionCounter = 0, intPositionPlaceholder = 0;
  /*
   Three seeded for loops to assign values to the array, DNA, and cells.
   As such:
   j = Array Counter
   i = DNA Member Counter (C, T, G, etc.)
   q = Array Cell

   The intPlaceholder acts a way to ensure the loop doesn't start back at
   zero when looping.
   Need a way to keep walking down the array, so insert a place holder,
   adding respectively.

   To ensure random assignment, every increment of the array number passes
   the assigned values to be algorithmically sorted.
   */
  for (int j = 0; j < intSizeOfArray; j++)
  {

    intPositionPlaceholder = 0;
    for (int i = 0; i < cDNA_LENGTH; i++)
    {

      intPositionCounter = 0;
      for (int q = intPositionPlaceholder; q <
         (cDNA_LENGTHOFMEMBERS_MISSINGCOW[i] + intPositionPlaceholder);
         q++)
      {

        scowToPass[j].m_charDNA[q] = cDNA_MEMBERS[i];
        intPositionCounter++;
      }
      intPositionPlaceholder += intPositionCounter;
    }
    funcDNA_RandomSort(scowToPass[j], intSizeOfDNAMembers);
    funcEnsureLastCharTerminatingCharacter(scowToPass[j].m_charDNA,
                         intSizeOfDNAMembers);
  }

  return;
}


void funcFirstTest_RandomArrayAssignment_FoundCow(
                          SMatchingCow &
                          scowToPass,
                          const int intSizeOfMembers)
{

  int intNULLPlace;
  int intArrayCounter = 0, intPositionPlaceholder = 0;
  int intNULL = static_cast<int>(cCHANCE_OF_NULL * 100);
  /*
   An equivelant of funcFirstTest_RandomArrayAssignment_MissingCows,
   with a few tweaks.

   - First, since this being passed a single struct instead of an array,
   there are two loops.
   i = DNA Member Counter (C, T, G, etc.)
   q = Array Cell
   Same format as the Missing Cow, just taking out the array counter.

   - Second, formatted to check for possibility of a NULL (missing data).
   Pseudo rundown of code:
   2% chance, so 2 in a 100 chance.
   Random generated number = 1 - 2, NULL is activated.
   Random generated number = 3 - 100, proceeds with original functions.
   The ternary evaluates this, and assigns as such.
   */

  for (int i = 0; i < cDNA_LENGTH; i++)
  {
    intArrayCounter = 0;
    for (int q = intPositionPlaceholder; q <
       (cDNA_LENGTHOFMEMBERS_MATCHINGCOW[i] + intPositionPlaceholder);
       q++
       )
    {

      intNULLPlace = funcRandomNumberGenerator(1, 100);
      scowToPass.m_charDNA[q] = (intNULLPlace <= intNULL) ? cNULL_CHAR :
      cDNA_MEMBERS[i];
      intArrayCounter++;
    }
    intPositionPlaceholder += intArrayCounter;
  }
  funcDNA_RandomSort(scowToPass, intSizeOfMembers);
  funcEnsureLastCharTerminatingCharacter(scowToPass.m_charDNA,
                       intSizeOfMembers);

  return;
}

bool funcSecondTest(const SMatchingCow scowToMatch,
                    const SMissingCow scowMissingCows[],
                    const int intSizeOfArray,
                    const int intDentalSize,
                    int intLocationOfFoundCow)
{
  bool boolResults[cMISSING_COWS];

  for(int i = 0; i < intSizeOfArray; i++)
  {

    boolResults[i] = (strncmp(scowMissingCows[i].m_charDental,
                  scowToMatch.m_charDental, intDentalSize) == 0)
    ? true: false;
  }

  intLocationOfFoundCow = funcSecondTest_LocationOfMatchingCow(boolResults,
                              intSizeOfArray);
  return funcReturnResults(boolResults, intSizeOfArray);
}

bool funcReturnResults(const bool boolResults[], const int intSize)
{
  bool boolMatchFound = false;
  int i = 0;
  do
  {
    boolMatchFound = boolResults[i];
    i++;
  } while (boolMatchFound == false && i < intSize);
  return boolMatchFound;
}

int funcSecondTest_LocationOfMatchingCow(const bool boolResults[],
                                         const int intSizeOfResults)

{
  int intLocationOfFoundCow, i = 0;
  bool boolMatchFound;

  do
  {
    boolMatchFound = boolResults[i] ? true : false;
    i++;
  } while (boolMatchFound == false && i < intSizeOfResults);

  intLocationOfFoundCow = i;

  return intLocationOfFoundCow;
}

void funcFirstTestResults(bool boolTestResults,
                          const SMatchingCow scowToMatch,
                          const SMissingCow scowMissingCows[],
                          const int intGreatestCowLocation)
{
  if (boolTestResults == false)
  {
    cout
    << "No Match For DNA Test," << endl
    << "Trying Dental Test..." << endl << endl;
  }
  else
  {
    cout
    << "MATCH FOUND!" << endl
    << "The Found Cow Is: "
    << scowMissingCows[intGreatestCowLocation].m_strName << endl
    << "Found Cow DNA: "
    << scowToMatch.m_charDNA << endl
    << "Missing Cow DNA: "
    << scowMissingCows[intGreatestCowLocation].m_charDNA << endl << endl;
  }

  return;
}

void funcSecondTest_RandomArrayAssignment_MissingCows(
                                                      SMissingCow scowToPass[],
                                                      const int intSizeOfArray,
                                                      const
                                                      int
                                                      intSizeOfDentalMembers)
{
  int intPositionCounter = 0, intPositionPlaceholder = 0;;
  for (int j = 0; j < intSizeOfArray; j++)
  {
    intPositionPlaceholder = 0;
    for (int i = 0; i < cDENTAL_LENGTH; i++)
    {
      intPositionCounter = 0;
      for (int q = intPositionPlaceholder; q <
         (cDENTAL_LENGTHOFMEMBERS_COW[i] + intPositionPlaceholder);
         q++)
      {
        scowToPass[j].m_charDental[q] = cDENTAL_MEMBERS[i];
        intPositionCounter++;
      }
      intPositionPlaceholder += intPositionCounter;
    }
    funcDental_RandomSort(scowToPass[j], intSizeOfDentalMembers);
    funcEnsureLastCharTerminatingCharacter(scowToPass[j].m_charDental,
                         intSizeOfDentalMembers);
  }

  return;
}

void funcSecondTest_RandomArrayAssignment_FoundCow(
                                                   SMatchingCow & scowToPass,
                                                   const int intSizeOfArray)
{

  int intPositionCounter = 0, intPositionPlaceholder = 0;

  intPositionPlaceholder = 0;
  for (int i = 0; i < cDENTAL_LENGTH; i++)
  {
    intPositionCounter = 0;
    for (int q = intPositionPlaceholder; q <
       (cDENTAL_LENGTHOFMEMBERS_COW[i] + intPositionPlaceholder); q++)
    {

      scowToPass.m_charDental[q] = cDENTAL_MEMBERS[i];
      intPositionCounter++;
    }
    intPositionPlaceholder += intPositionCounter;
  }
  funcDental_RandomSort(scowToPass, intSizeOfArray);
  funcEnsureLastCharTerminatingCharacter(scowToPass.m_charDental,
                       intSizeOfArray);

  return;
}

void funcSecondTestResults(bool boolTestResults,
                           const SMatchingCow scowToMatch,
                           const SMissingCow scowMissingCows[],
                           const int intGreatestCowLocation)
{
  if (boolTestResults == false)
  {
    cout
    << "No Match For Dental Test" << endl << endl;
  }
  else
  {
    cout
    << "MATCH FOUND!" << endl
    << "The Found Cow Is: "
    << scowMissingCows[intGreatestCowLocation].m_strName << endl
    << "Found Cow Dental Information: "
    << scowToMatch.m_charDental << endl
    << "Missing Cow Dental Information: " <<
    scowMissingCows[intGreatestCowLocation].m_charDental << endl << endl;
  }

  return;
}

void funcFarewells()
{
  cout
  << "Thank you for using Cowculator," << endl
  << "Come back for moooo-re" << endl;

  return;
}

void funcEnsureLastCharTerminatingCharacter(char cString[],
                      const int intLASTCellInArray)
{
  cString[intLASTCellInArray] = cNTC;

  return;
}

int funcRandomNumberGenerator(const int intFloor, const int intCeiling)
{
  return (intFloor + (rand() % (intCeiling - intFloor + 1)));
}



