// Programmers: Illya Starikov and Alex Androff          Date: 04/17/15
// File: Functions.cpp                                   Class: CS1570A
// Purpose: Define general functions.

#include <iostream>
#include <fstream>

#include "Functions.h"
#include "Judicial.h"

/*--------------------srand/rand C++ 98 Header--------------------*/
#include <stdio.h>          // NULL
#include <stdlib.h>         // srand, rand
#include <time.h>           // time

using namespace std;

void setTheScene()
{
  cout
  << endl << endl
  << "/*-------------------- The Beginning --------------------*/" << endl;
  string storySegment;
  ifstream fin;
  fin.open("Backstory.dat");

  while (!fin.eof())
  {
    getline(fin, storySegment);
    cout << storySegment;
    cout << endl;
  }
  cout << endl << endl;
  fin.close();

  return;
}

void meetingResults(const CrimeRoom roomOfCrime, const string meetingTime,
          const bool murderOccured, const Resident residentOne,
          const Resident residentTwo)
{
  cout << meetingTime << "\t|\t";
  if (murderOccured)
  {
    cout << roomOfCrime.getDeadResident() << " is dead!"
    << " They have been murdered!";
  }
  else if (!murderOccured)
  {
    cout << residentOne.getResidentName() << " and "
    << residentTwo.getResidentName() << " meet." << endl;
  }

  return;
}

void takeOutVictim(Resident mainResidents[], CrimeRoom roomOfCrime,
          int & SizeOfArray, const int locationOfFirstResident,
           const int locationOfSecondResident)
{
  if (roomOfCrime.getDeadResident() ==
    mainResidents[locationOfFirstResident].getResidentName())
  {
    removeResidentFromArray(mainResidents, SizeOfArray,
                locationOfFirstResident);
  }
  else
  {
    removeResidentFromArray(mainResidents, SizeOfArray,
                locationOfSecondResident);
  }

  return;
}

void investigation(csiAgent agentForInvestigation,
           Resident residentsToSearch[], int & sizeOfResidents,
           CrimeRoom roomToSearch)
{
  bool matchFound;
  int residentPlace, roomVisits = 0;

  do
  {
    agentForInvestigation.gatherInformation(roomToSearch);
    residentPlace = - 1; // Immediate increment.

    do
    {
      ++residentPlace;
      matchFound = agentForInvestigation.perpSearch(residentsToSearch
                              [residentPlace]);
    } while (!matchFound && residentPlace < sizeOfResidents);

    ++roomVisits;
  } while (!matchFound && roomVisits < MAX_NUMBER_OF_ROOM_SEARCHES);

  matchFound ?
  cout
  << endl << endl
  << "Match Found! After " << roomVisits
  << " visits it was identified to be "
  << residentsToSearch[residentPlace].getResidentName()
  << " with " << residentsToSearch[residentPlace].getWeapon()
  << "!" << endl << endl :
  cout
  << endl << endl << "No match found:(" << endl
  << "Better luck next time..." << endl << endl;

  if (matchFound)
  {
    judgementDay(residentsToSearch, sizeOfResidents, residentPlace);
  }

  return;
}

void judgementDay(Resident residentArray[], int & sizeOfArray,
          int locationOfJudgingResident)
{
  Judicial theJudge(DEFAULT_JUDGE, DEFAULT_CONVICTION_RATE);

  bool conviction =
  theJudge.judgement(residentArray[locationOfJudgingResident].
             getResidentName());
  if (conviction)
  {
    removeResidentFromArray(residentArray, sizeOfArray,
                locationOfJudgingResident);
  }

  return;
}

void removeResidentFromArray(Resident residentArray[],
               int & sizeOfArray, const int residentToRemove)
{

  Resident temp = residentArray[residentToRemove];
  residentArray[residentToRemove] = residentArray[sizeOfArray - 1];
  residentArray[sizeOfArray - 1] = temp;
  -- sizeOfArray;

  return;
}

void closingStatement(const Resident residentZero, const bool someoneDidWin)
{
  cout
  << endl << endl << "/*-------------------- The End --------------------*/"
  << endl;
  cout << endl
  << "It's the end of the semester, and everyone is dead. " <<
  "All have been killed, turned to be murders, sent to jail, " <<
  "free to walk the streets." << endl << endl;
  cout << "All except you";
  if (someoneDidWin)
  {
    cout << " and " << residentZero.getResidentName()
    << ", who is now in permanant psychiatric evaluation";
  }
  cout << "." << endl << endl;

  string storySegment;
  ifstream fin;
  fin.open("Conclusion.dat");

  while (!fin.eof())
  {
    getline(fin, storySegment);
    cout << storySegment;
    cout << endl;
  }
  fin.close();

  cout << endl
    <<" .----------------.  .----------------.  .-----------------." << endl
    <<"| .--------------. || .--------------. || .--------------. |" << endl
    <<"| |  _________   | || |     _____    | || | ____  _____  | |" << endl
    <<"| | |_   ___  |  | || |    |_   _|   | || ||_   \\|_   _| | |" << endl
    <<"| |   | |_  \\_|  | || |      | |     | || |  |   \\ | |   | |" << endl
    <<"| |   |  _|      | || |      | |     | || |  | |\\ \\| |   | |" << endl
    <<"| |  _| |_       | || |     _| |_    | || | _| |_\\   |_  | |" << endl
    <<"| | |_____|      | || |    |_____|   | || ||_____|\\____| | |" << endl
    <<"| |              | || |              | || |              | |" << endl
    <<"| '--------------' || '--------------' || '--------------' |" << endl
    <<" '----------------'  '----------------'  '----------------' " << endl;
}

void twoRandomNumbers(int & numberOne, int & numberTwo,
            const int floor, const int ceiling)
{
  numberOne = randomArbitrary(floor, ceiling);

  do
  {
    numberTwo = randomArbitrary(floor, ceiling);
  } while (numberOne == numberTwo);

  return;
}

void timeManagement(int & timeOfDay, int & theDay,
          const bool isMurderOccuring)
{
  if (timeOfDay >= MEETINGS_PER_DAY - 1 || isMurderOccuring)
  {
    timeOfDay = 0;
    theDay++;
    cout<< endl << "/*-------------------- Day " << theDay
    << " --------------------*/" << endl;
  }
  else
  {
    ++timeOfDay;
  }
  return;

}

int randomArbitrary(const int floor, const int ceiling)
{
  return (floor + rand() % (ceiling - floor + 1));
}

int round(const float numberToRound)
{
  return static_cast<int>(numberToRound+.5);
}

int absolute(const int numberToAbsolute)
{
  return (numberToAbsolute < 0 ) ? (numberToAbsolute * - 1) :
  numberToAbsolute;
}

void errorMessage(const int errorCode)
{
  // Error Codes
  // 1. Miscellaneous Error
  // 2. Error fStream
  // 3. End of file reached.
  switch (errorCode)
  {
    case 1:
      cout << endl << "ERROR. Please Try Again." << endl << endl;
      break;

    case 2:
      cout << endl << "ERROR. Unable To Open File." << endl << endl;
      break;

    case 3:
      cout << endl << "ERROR. End of File reached." << endl << endl;
      break;
  }

  return;
}