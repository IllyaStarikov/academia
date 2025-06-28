// Programmer: Illya Starikov                Date: 04/17/15
// File: Resident.cpp                    Class: CS1570A
// Purpose: To write the driver of the program (main), and to do
// unit testing.

/*
 To clear any confusion, the directory is named Final Boss.

 So for #ifndef gaurds, the prefix is my directory.
 */


#include <iostream>

// Random Function Libraries
#include <stdio.h>    // NULL
#include <stdlib.h>   // srand, rand
#include <time.h>     // time

#include "Resident.h"
#include "CrimeRoom.h"

#include "Functions.h"

using namespace std;

int main()
{
  srand(static_cast<unsigned>(time(NULL)));
  /*--------------------Unit Testing--------------------*/

  const int NUMBER_OF_RESIDENTS = 5;
  const int TEST_RESIDENT = 3; // Nice, median number.

  Resident mainResidents[NUMBER_OF_RESIDENTS];

  for (int i = 0; i < NUMBER_OF_RESIDENTS; i++)
  {
    cout << mainResidents[i];
  }

  cout << endl;
  cout << mainResidents[TEST_RESIDENT].getHair() << endl;
  cout << mainResidents[TEST_RESIDENT].getResidentName();
  cout << endl << endl;

  // This changes member data for the rest for a different,
  // that could possibly change this data again.
  // I left it commented in to show I tested all member functions,
  // acessors *and mutators*
  /*
  cout << mainResidents[TEST_RESIDENT];
  mainResidents[TEST_RESIDENT].setResidentIsMurderer(true);
  mainResidents[TEST_RESIDENT].killMe();
  // i do not have a mutator for the hair because up to this point,
  // it is unneccary
  cout << mainResidents[TEST_RESIDENT];
  */

  CrimeRoom mainCrimeRoom;
  for (int i = 0; i < NUMBER_OF_RESIDENTS - 1; i++)
  {
    mainCrimeRoom.meeting(mainResidents[i], mainResidents[i+1]);
    mainCrimeRoom.checkRoom();

    mainResidents[i].setResidentIsMurderer(false);
    mainResidents[i+1].setResidentIsMurderer(false);
    // resets to make sure a resident isn't sent to a meeting
    // while he's already a murderer
  }

  /*--------------------Unit Testing End--------------------*/

  return 0;
}
