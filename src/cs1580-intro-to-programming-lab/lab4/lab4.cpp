// Programmer: Illya Starikov – 18083141
// Section: 3E
// File: lab3.cpp
// Description: to calculate average of 3s and 5s

#include <iostream>

using namespace::std;

int main() {
  int intUserInputNumber, intTotalOfUserInput = 0, intCounter = 0;
  float floAverageOfUserInput;
  string strTryAgain;
  
  cout << "Welcome to the Calculator Averager" << endl;
  
  do {
    cout << "Would you like to enter a number (y/n)? ";
    cin >> strTryAgain;
    if (strTryAgain == "Y" || strTryAgain == "y") {
      cout << "Enter your Number: ";
      cin >> intUserInputNumber;
      
      if ((intUserInputNumber >= 0 && intUserInputNumber <= 50) && ((intUserInputNumber % 5 == 0 || intUserInputNumber % 3 == 0))) {
        intTotalOfUserInput += intUserInputNumber;
        intCounter++;
      }
    }
  } while (strTryAgain == "Y" || strTryAgain == "y");
  
  // Calculuations
  floAverageOfUserInput = static_cast<float>(intTotalOfUserInput) / intCounter;
  
  //Print Out
  cout <<
  "The average is: " << floAverageOfUserInput <<
  "\nSigning Off Now";
  
  // Return Type (int)
  return 0;
}