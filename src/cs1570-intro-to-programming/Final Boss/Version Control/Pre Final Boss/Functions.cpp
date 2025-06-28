// Programmer: Illya Starikov                Date: 04/17/15
// File: Functions.h                      Class: CS1570A
// Purpose: Define general functions.

#include <iostream>
#include <limits>

#include <fstream>
#include <sstream>

#include "Functions.h"

/*--------------------srand/rand C++ 98 Header--------------------*/
#include <stdio.h>          // NULL
#include <stdlib.h>         // srand, rand
#include <time.h>           // time

using namespace std;

string fileNameParsor()
{
  // Not the most elegant solution, but it gets the job done

  static unsigned filePlaceholder = 1; // static, won't redefine every call.
  bool reachedEndOfFile = false;
  // Notice, this is a placeholder, not a positions. Does not start at 0;
  string nameFromFile;

  ifstream nameReadIn;
  nameReadIn.open("Names.dat");

  if (nameReadIn.is_open())
  {

    static unsigned fileLength = fileSize(nameReadIn);
    // one time call, negating the need to consistently call the function.
    // Unsigned because if this returns a negative number.
    // I don't know what will happen but I do not care to find out.
    // Small optimization but when unit testing in the thousands pays off

    for (unsigned int i = 0; i < filePlaceholder; i++)
    {
      if (i < fileLength)
      {
        getline(nameReadIn, nameFromFile);
      }
      else
      {
        nameFromFile = "NULL";
        reachedEndOfFile = true;
      }
    }
    if (reachedEndOfFile == true)
    {
      errorMessage(3);
    }

  }
  else
  {
    errorMessage(2);
  }

  filePlaceholder++;
  nameReadIn.close();
  return nameFromFile;
}

unsigned int fileSize(ifstream& fin)
{
  unsigned int fileLength = 0; // The unsigned integer to return

  do
  {
    fileLength++; // Incremment fileLength,
    fin.ignore(numeric_limits<streamsize>::max(), '\n');
    // while Ignoring the actual data,
  } while (!fin.eof()); // until it reaches the end of file marker

  fin.clear(); // clear the fail bit,
  fin.seekg(0,ios::beg); // and return the stream to the beginning
  // Since this stream is passed by reference, have to return stream
  // To original state. If not, you'll begin at the eof / failed bit

  return fileLength;
}


int randomArbitrary(const int floor, const int ceiling)
{
  return (floor + rand() % (ceiling - floor + 1));
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