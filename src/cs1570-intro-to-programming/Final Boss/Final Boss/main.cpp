// Programmers: Illya Starikov and Alex Androff        Date: 04/17/15
// File: main.cpp                                      Class: CS1570A
// Purpose: To write the driver of the program (main), and to do
// unit testing.

/*
 To clear any confusion, the directory is m_named Final Boss.

 So for #ifndef guards, the prefix is my directory.
 */

#include <iostream>

// Random Function Libraries
#include <stdio.h>    // NULL
#include <stdlib.h>   // srand, rand
#include <time.h>     // time

#include "Resident.h"
#include "CrimeRoom.h"
#include "Judicial.h"
#include "Agent.h"
#include "Functions.h"

using namespace std;

/*
 /--------------------Optionals--------------------/
 - There is an introduction and conclusion to set the scene.
 - The judge gets announced when going into court.
 - The residents have weapons found within the classroom.
 - Mr. Price is invincible to attacks. He automatically kills anyone trying to
 attack him.
 - There is a huge suprise at the end of the output.

 - Those names, though. That was optional all in itself.
 */

int main()
{
  srand(static_cast<unsigned>(time(NULL)));

  CrimeRoom pricesOffice;
  Resident pricesStudents[NUMBER_OF_RESIDENTS];

  int studentsRemaining = NUMBER_OF_RESIDENTS;
  int residentOne, residentTwo;
  int timeCounter = FIRST_DAY_DEFAULT, day = 0;

  bool murderOccurred;

  setTheScene();

  do
  {
    timeManagement(timeCounter, day, murderOccurred);
    twoRandomNumbers(residentOne, residentTwo, 0, studentsRemaining - 1);

    pricesOffice.meeting(pricesStudents[residentOne],
               pricesStudents[residentTwo]);
    murderOccurred = pricesOffice.checkRoom();
    meetingResults(pricesOffice, MEETING_TIMES[timeCounter],
             murderOccurred,
             pricesStudents[residentOne],
             pricesStudents[residentTwo]);

    if (murderOccurred)
    {
      takeOutVictim(pricesStudents, pricesOffice, studentsRemaining,
              residentOne, residentTwo);
      csiAgent mainAgent;
      investigation(mainAgent, pricesStudents, studentsRemaining,
              pricesOffice);
    }
  } while (studentsRemaining > 1);

  closingStatement(pricesStudents[0], studentsRemaining);
  return 0;
}