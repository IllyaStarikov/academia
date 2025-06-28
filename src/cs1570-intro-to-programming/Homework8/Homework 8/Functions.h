//Programmers: ALEX ANDROFF & ILLYA STARIKOV  DATE: 3/21/15
//Class: CS1570                               Section: A
//Filename: functions.h
//Purpose: Use different tests to determine the identity of a missing cow.

#ifndef Homework_8__Functions
#define Homework_8__Functions

#include <iostream>
#include "Constants.h"

using namespace std;

struct SMissingCow
{
  string m_strName;
  char m_charDNA[cDNA_MISSINGCOWSLENGTH + 1];
  char m_charDental[cNUMBER_OF_TEETH + 1];
};

struct SMatchingCow
{
  string m_strName;
  char m_charDNA[cDNA_MATCHINGCOWLENGTH + 1];
  char m_charDental[cNUMBER_OF_TEETH + 1];
};

//The GreetUser function will present a greeting message to the user of the
// program.
//Pre: Computer must be on and must be using a valid C++ compiler.
//Post: The function will present a greeting message to the user.
void funcGreetUser();

// Assign the names specified in main.cpp to the cows.
// Pre: cow names array must be intitlized and the names must be funny
// post: names are assigned
void funcNameAssignment(SMissingCow scowMissingCowToName[], string strNames[],
  const int intSizeOfArray);


// First Test Functions

//The FirstTest function uses the parameters passed to it in order to find a
//    match between the randomly generated missing cows and the matching cow.
//Pre: Structs must be initialized (preferably in main),
// passing size (intSizeOfMissingCow) MUST BE VALID.
//    The function depends on this to not walk off the array.
//Post: The function returns a value that represents whether or not a match was
//     found between the differently generated missing cows and the
//     matching cow that are being compared.
bool funcFirstTest(SMatchingCow scowToMatch,
           const int intSizeOfMatchingCowDNA,
           SMissingCow scowMissingCows[],
           const int intSizeOfMissingCows,
           const int intSizeOfMissingCowDNA,
           int intGreatestMatchingCow);

// To return absolute value.
// Pre: None.
// Post: returns an absolute integer of passed "x" value.
int funcAbs(const int x);

//The FirstTest_NULLTest function goes through the MatchingCow parameter passed
//  to it and searches for the null character that would make the cow invalid.
//Pre: The scowToMatch must go through random assignment.
//Post: The function searches the MatchingCow passed to it for the
// pre-determined null character. Whether or not the character is found is
// returned to the calling function.
bool funcFirstTest_NULLTest(SMatchingCow scowToMatch,
              const int intSizeOfMatchingCowDNA);

//The FirstTest_RegressCharacters function is used to scale a smaller array to
//  the size of a larger array which will allow the two arrays to be
// effectively compared.
//Pre: charTempArray[] must be valid and intSizeOfArray MUST BE CORRECT, or
// walking
//   the array will occur.
//Post: The function will scale the size of a smaller array to the size of
//    a larger array to allow for easier comparison between the two.
void funcFirstTest_RegressCharacters(char charTempArray[],
  const int intSizeOfArray);

//The FirstTest_GreatestIntAsPercent function takes the number of matches
//  found between the missing and matching cows and divides that number by
//  the total number of possible matches. That fraction is turned into a
//  percent and then returned to the calling function.
//Pre:all parameters must be correct.
// Especially intSizeOfDNAMembers
//Post: The function will turn fraction of matches found over the total
// possible matches into a percentage that will be returned
// to_char_type
// the calling function.
int funcFirstTest_HighestPercentageCow(const int intAccuracy[],
  const int intSizeOfArray);


// Second Test Functions

//The SecondTest function implements the dental test of the program and returns
//  a bool value of whether or not the test was successful.
//Pre: both structs must go through random assignment, intSizeOfDNA must be
// correct.
//Post: The different arrays that are passed to the function will be compared
// for the dental test and whether or not a match was found will be returned as
//  a boolean value.
bool funcSecondTest(const SMatchingCow scowToMatch,
          const SMissingCow scowMissingCows[], const int intSizeOfArray,
          const int intDentalSize, int intLocationOfFoundCow);

//The ReturnResults function returns a value that determines whether or not a
//  match has been made between the found cow and the list of missing cows.
//Pre: must have gone through all but the return in the second test function.
//Post: A bool value is returned which determines whether or not a match has
//    has been found.
bool funcReturnResults(const bool boolResults[], const int intSize);

//The SecondTest_RandomArraryAssingment_MissingCows function is used to
// randomly assign the respective values of the second test to the array
// that is passed to it.
//Pre: struct must be declared (in main, preferably), and intSizeOfArray must
//be valid, or walking off the array *will* occur.
//Post: Data for the array that is passed to the function will be randomly
//    generated and placed in the cells of the array.
void funcSecondTest_RandomArrayAssignment_MissingCows(
                        SMissingCow scowToPass[],
                        const int intSizeOfArray,
                        const int intSizeOfDentalMembers);

//The SecondTest_RandomArraryAssignment_FoundCow function is used to randomly
// assign the respective values of the second test to the array that is passed
// to it.
//Pre: stuct must be valid and the size of the array must be valid,
// or walking off the array will occur.
//Post: Data for the array that is passed to the function will be randomly
//    generated and placed in the cells of the array.

void funcSecondTest_RandomArrayAssignment_FoundCow(
                        SMatchingCow & scowToPass,
                        const int intSizeOfArray);

//Locate the place where location in the array that the cow that had the match.
// Pre: Executed most of the loop to gather if there was a potential match,
// intSizeofResults must be valid.
// Post: Returns an integer to determine the location of the matching cow,
// if any exists.
int funcSecondTest_LocationOfMatchingCow(const bool boolResults[],
                     const int intSizeOfResults);

// Present the first test results
// Pre: Must have random assignment and must have gone through the first test.
//  must have gone through the first test.
// Post: Prints the results based on the boolTestResults being passed.
void funcFirstTestResults(bool boolTestResults,
              const SMatchingCow scowToMatch,
              const SMissingCow scowMissingCows[],
              const int intGreatestCowLocation);

// Present the second test results
// Pre: Must have random assignment and must have gone through the second test
// function.
// Post: Prints the results based on the boolTestResults being passed.
void funcSecondTestResults(bool boolTestResults,
               const SMatchingCow scowToMatch,
               const SMissingCow scowMissingCows[],
               const int intGreatestCowLocation);

//The Farewells function will present a goodbye message to the user.
//Pre: None.
//Post: A goodbye message will be presented to the user of the program.
void funcFarewells();



// Maintenance Functions

//The FirstTest_RandomArraryAssingment_MissingCows function is used to randomly
// assign
//  the respective values of the first test to the array that is passed to it.
//Pre: the array size and the DNA size must be correct, or walking off the
// array will occur.
//Post: Data for the array that is passed to the function will be randomly
//    generated and placed in the cells of the array.
void funcFirstTest_RandomArrayAssignment_MissingCows(
                       SMissingCow scowToPass[],
                       const int intSizeOfArray,
                       const int intSizeOfDNAMembers);

//The FirstTest_RandomArraryAssignment_FoundCow function is used to randomly
// assign the respective values of the first test to the array that is passed
// to it.
//Pre: The DNA members must be valid, the struct must be declared
// (preferably in main)
//Post: Data for the array that is passed to the function will be randomly
//    generated and placed in the cells of the array.
void funcFirstTest_RandomArrayAssignment_FoundCow(
                       SMatchingCow & scowToPass,
                       const int intSizeOfDNAMembers);

//The EnsureLastCharTerminatingCharacter function makes sure that the last cell
//  in the array that has been passed to the function is a null character.
//Pre: the last array cell must be the last cell in the array. If not, you'll
// be assigning an '/0' where it shouldn't be.
//Post: The function check to make sure that the last cell in the array is
//    indeed a null character.
void funcEnsureLastCharTerminatingCharacter(char cString[],
                      const int intLASTCellInArray);

//The RandomNumberGenerator function is used to randomly generate a number
//  that determines whether or not the predetermined null character ('-')
//  should be present.
//Pre: intCeiling must be greater than intFloor
//Post: A random number will be generated that is between the two passed values
//    and that number will determine whether or not '-' should be present.
int funcRandomNumberGenerator(const int intCeiling, const int intFloor);

// This is strictly for the use of cows, so more beneficial to have more
// descriptive typenames
// To randomly sort the members in the cow structs
// Pre: the cows must be valid, the size of members must be valid.
// Post: The member c-string will be randomly (in an algorithmic manner)
// sorted.
template<typename scow>
void funcDNA_RandomSort(scow & scowToSort, const int intSizeOfDNAMembers)
{

  char charTemp;
  int intArrayLocation;
  /*
   In a nut shell, a single seeded bubble sort, reverse engineered.

   Walks down the array, gets a random number to assign the value,
   increments cell.
   Parses data to scatter to random assignments.

   Everything subtracted by one because arrays start at 0.
   */
  for (int i = 0; i < (intSizeOfDNAMembers - 1); i++)
  {

    intArrayLocation = funcRandomNumberGenerator(0,
      intSizeOfDNAMembers - 1);
    charTemp = scowToSort.m_charDNA[intArrayLocation];
    scowToSort.m_charDNA[intArrayLocation] = scowToSort.m_charDNA[i];
    scowToSort.m_charDNA[i] = charTemp;
  }
}

template<typename scow>
void funcDental_RandomSort(scow & scowToSort, const int intSizeOfDNAMembers)
{

  char charTemp;
  int intArrayLocation;

  for (int i = 0; i < (intSizeOfDNAMembers - 1); i++)
  {

    intArrayLocation = funcRandomNumberGenerator(0,
      intSizeOfDNAMembers - 1);
    charTemp = scowToSort.m_charDental[intArrayLocation];
    scowToSort.m_charDental[intArrayLocation] = scowToSort.m_charDental[i];
    scowToSort.m_charDental[i] = charTemp;
  }
}

#endif /* defined(Homework_8__Functions) */
