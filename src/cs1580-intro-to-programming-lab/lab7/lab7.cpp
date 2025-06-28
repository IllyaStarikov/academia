// Programmer: Illya Starikov
// Section: 3E
// File: lab7.cpp
// Description: To calculate random numbers
#include <iostream>
#include <ctime>


// FUNCTIONS
// FUNCTION DESCRIPTION: Greets the users
// PRE CONDITION: none
// POST CONDITION: cout statement, side effect
void funcGreetUser();

// FUNCTION DESCRIPTION: Greets the users
// PRE CONDITION: none
// POST CONDITION: getting the upper and lower limit
void funcReadNumber(int & intNumber_1, int & intNumber2);

// FUNCTION DESCRIPTION: Greets the users
// PRE CONDITION: none
// POST CONDITION: passing limits, calculating random numbers, outputting
void funcRandomNumberGenerator(int intNumber_1, int intNumber_2);

// FUNCTION DESCRIPTION: Greets the users
// PRE CONDITION: none
// POST CONDITION: cout statement, side effect
void funcSignOff();

// CONSTS
// NAMESPACES
using namespace std;

int main()
{
  int intLowerLimit, intUpperLimit, intRandomNumbers;
  
  funcGreetUser();
  
  funcReadNumber(intLowerLimit, intUpperLimit);
  funcRandomNumberGenerator(intLowerLimit, intUpperLimit);
  
  funcSignOff();
  
  return 0;
}

void funcGreetUser()
{
  cout <<
  "~ * ~ Welcome to Random Number Generator ~ * ~" << endl;
  
  return;
}

void funcReadNumber(int & intNumber_1, int & intNumber_2)
{
  bool boolLoopKick = false; // loop management
  
  // Lower Limit
  do {
    cout << "Enter the lower limit [>0]: ";
    cin >> intNumber_1;
    
    if (intNumber_1 > 0)
    {
      boolLoopKick = true;
    }
    else
    {
      boolLoopKick = false;
    }
  } while (boolLoopKick == false);
  
  boolLoopKick = false; // in case else clause doesn't catch error
  cout << endl; // to make the two do while similar
  
  // Upper Limit
  do {
    cout << "Enter the upper limit [>9]: ";
    cin >> intNumber_2;
    
    if (intNumber_2 > 9 && (intNumber_2 >= (intNumber_1 * 2)))
    {
      boolLoopKick = true;
    }
    else
    {
      boolLoopKick = false;
    }
  } while (boolLoopKick == false);
  
  return;
}

void funcRandomNumberGenerator(int intNumber_1, int intNumber_2)
{
  int intRandomNumber;
  srand(time(NULL)); // seed random with time

  for (int i = 0; i < 5; i++)
  {
      intRandomNumber = (rand() % (intNumber_2 - intNumber_1 ))+intNumber_1;
    cout << "Random Number between " << intNumber_1 << " and " << intNumber_2 << ", inclusively, is " << intRandomNumber << endl;
  }
  
  return;
}

void funcSignOff()
{
  cout <<
  "Have a Good Day!" << endl;
  
  return;
}