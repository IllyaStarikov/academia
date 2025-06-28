// Programmers: Illya Starikov and Alex Androff        Date: 04/17/15
// File: Functions.h                                   Class: CS1570A
// Purpose: Prototype general functions.

#ifndef Final_Boss__Functions
#define Final_Boss__Functions

#include "Resident.h"
#include "Agent.h"
#include "CrimeRoom.h"

/*
Description:   Sets the scence, gives backstory to the story.
Pre-Condition:   None.
Post-Condition:  Cout statements, side effects.
*/
void setTheScene();

/*
Description:    Shows the results of the meeting.
Pre-Condition:  All members must be passed, used in cout statements.
Post-Condition:   Cout statements, side effects.
*/
void meetingResults(const CrimeRoom roomOfCrime, const std::string
          meetingTime, const bool murderOccured,
          const Resident residentOne, const Resident residentTwo);

/*
Description:   Takes out the victim of the murder.
Pre-Condition:   Size of array *must be* right. All respective parameters must
be correct.
Post-Condition:  Size of the array is decreased.
*/
void takeOutVictim(Resident mainResidents[], CrimeRoom roomOfCrime,
           int & SizeOfArray, const int locationOfFirstResident,
           const int locationOfSecondResident);

/*
Description:  investigates to see if the perp can be caught.
Pre-Condition:  Respective members must be correct, and must have preceding
functions called (constructor, meetings, etc.)
Post-Condition: Checks to see if a match can be found based on a very
scientific formula.
*/
void investigation(csiAgent agentForInvestigation, Resident
           residentsToSearch[], int & sizeOfResidents,
           CrimeRoom roomToSearch);

/*
Description:  Judges to see if the murderer goes to jail.
Pre-Condition:  Respective members must be correct, and must have preceding
functions called (constructor, meetings, etc.)
Post-Condition: If guilty, the function takes the resident and removes him
from the array.
*/
void judgementDay(Resident residentArray[], int & sizeOfArray,
          int locationOfJudgingResident);

/*
Description:  A function to remove a resident from an array.
Pre-Condition:  Pass a residentArray that you want to remove him from an array,
the size of the array, and the location of the resident you want to remove.
Post-Condition: A resident is "removed", in other words, put in the back of the
array and the sizeOfTheArray is decreased.
*/
void removeResidentFromArray(Resident residentArray[],
               int & sizeOfArray,
               const int residentToRemove);

/*
Description:  The close the story off.
Pre-Condition:  The last resident is passed and a boolean to represent if
there is, in fact, a winner.
Post-Condition: Cout statements, side effects.
*/
void closingStatement(const Resident residentZero,
            const bool someoneDidWin);

/*
Description:  A timer to keep track of the days.
Pre-Condition:  The time of day and the day counters must be passed,
and if the murders have occured.
Post-Condition: Basically, the days are outputted.
*/
void timeManagement(int & timeOfDay, int & theDay,
          const bool isMurderOccuring);

/*
Description:  A function to manipulate two numbers to be random.
Pre-Condition:  two different number must be passed, and the margin in which
they can be located.
Post-Condition: The two numbers are changed to two different, random numbers.
*/
void twoRandomNumbers(int & numberOne, int & numberTwo,
            const int floor, const int ceiling);

/*
Description:  Random number generated.
Pre-Condition:  a floor and a ceiling must be passed.
Post-Condition: A random number within the floor and ceiling is returned.
*/
int randomArbitrary(const int floor, const int ceiling);

/*
Description:  Round a number.
Pre-Condition:  A number must be passed to round.
Post-Condition: A rounded int is returned based on he number passed.
*/
int round(const float numberToRound);

/*
Description:  gives back an absolute number. Basically, abs() but without
the library import.
Pre-Condition:  A number must be passed that you want the absolute number of.
Post-Condition: An absolute version of the number is returned.
*/
int absolute(const int numberToAbsolute);

/*
Description:  Error codes to output, in case such a thing happens. Which it
won't. Hopefully. Please don't happen.
Pre-Condition:  The error code that is respective to the code necessary must
be passed.
Post-Condition: cout statements, side effects.
*/
void errorMessage(const int errorCode);


#endif /* defined(Final_Boss__Functions) */