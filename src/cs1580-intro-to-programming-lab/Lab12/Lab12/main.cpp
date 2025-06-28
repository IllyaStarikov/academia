// Programmer: Illya Starikov
// Section: 3E
// File: main.cpp
// Description: Driver

#include <iostream>

#include "Time.h"

using namespace std;

int main()
{
  Time mainTime;
  bool goAgain;
  char inputCharacter;

  do
  {
    mainTime.readIn();
    mainTime.printOut();
    mainTime.nextSecond();
    mainTime.previousSecond();

    cout << endl << "Again (Y/N): ";
    cin >> inputCharacter;
    goAgain = (toupper(inputCharacter) == 'Y') ? true : false;
    cout << endl;
  } while (goAgain == true);

  cout << endl << "Bye ..." << endl;
  return 0;
}
