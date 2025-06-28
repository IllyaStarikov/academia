// Programmer: Illya Starikov                                Date: 03/06/15
// File: WavelengthCalculator5001_functions.cpp              Class: CS1570A
// Purpose: To find the wavelengths of.. very, very strange matter.

#include <iostream>
#include "WavelengthCalculator5001.h"

using namespace std;

void funcGreetingMessage()
{
  cout << "Welcome to the Wavelength Calculator 5001"               << endl
       << "Let's get started with Wavelength Calculating goodness!" << endl;

  return;
}

void funcPresentMenu_GetInput(char & charMenuOption)
{
  char charMenuOption_FunctionScope;

  cout << endl
       << "Main Menu"                                   << endl
       << "1. Hair"                                     << endl
       << "2. Saliva and Hair"                          << endl
       << "3. Chicken-Noodle Soup and Saliva and Hair"  << endl
       << "4. Green Goo"                                << endl
       << "5. Exit"                                     << endl
       << "Enter Option: ";
  cin >> charMenuOption_FunctionScope;
  charMenuOption = charMenuOption_FunctionScope;

  return;
}

void funcMainMenu(const char charMenuOption, int & intWavelength,
                                             bool & boolPresentResults)
{
  // the funcMainMenu acts as a middleman between the input function,
  // and the overloaded funcCalculateWavelength.
  // You really don't want an ugly switch case in your main(), do you?

  //  Main Menu
  //  1. Hair
  //  2. Saliva and Hair
  //  3. Chicken-Noodle Soup and Saliva and Hair
  //  4. Green Goo
  //  5. Exit
  float floWavelength = 0.0, floHairIndex;
  int intPrecision, intGooGrade, intAlienHeight;
  bool boolSoupIsHomemade;

  switch (charMenuOption)
  {
    case '1':
      floHairIndex  = funcGetHairIndex();
      floWavelength = funcCalculateWavelength(floHairIndex);

      boolPresentResults = true;
      break;

    case '2':
      intPrecision  = funcGetPrecision();
      floHairIndex  = funcGetHairIndex();
      floWavelength = funcCalculateWavelength(floHairIndex, intPrecision);

      boolPresentResults = true;
      break;

    case '3':
      intPrecision       = funcGetPrecision();
      boolSoupIsHomemade = funcSoupIsHomemade();
      floWavelength      = funcCalculateWavelength(intPrecision,
                                                   boolSoupIsHomemade);

      boolPresentResults = true;
      break;

    case '4':
      intGooGrade    = funcGetGooGrade();
      intAlienHeight = funcGetAlienHeight();
      floWavelength  = funcCalculateWavelength(intGooGrade, intAlienHeight);

      boolPresentResults = true;
      break;

    case '5':
      boolPresentResults = false;

      break;

    default:
        funcErrorMessage();
        boolPresentResults = false;
  }
  // Rounding
  intWavelength = funcFloatToIntegerAndRounding(floWavelength);

  return;
}

// [SWITCH CASE FUNCTIONS]
float funcGetHairIndex()
{
  char charMenuOption_HairIndex;
  float floHairIndex_FunctionScope = 0;

  cout << endl << "Hair Index, Please Choose Appropriatly." << endl
       << "1. Blonde" << endl
       << "2. Brown" << endl
       << "3. Black" << endl;

  do
  {
    cout << "Enter Option: ";
    cin >> charMenuOption_HairIndex;

    switch (charMenuOption_HairIndex)
    {
      case '1':
        floHairIndex_FunctionScope = cHAIRINDEX_BLONDE;
        break;

      case '2':
        floHairIndex_FunctionScope = cHAIRINDEX_BROWN;
        break;

      case '3':
        floHairIndex_FunctionScope = cHAIRINDEX_BLACK;
        break;

      default:
        funcErrorMessage();
        break;
    }
  } while (floHairIndex_FunctionScope == 0);

  return floHairIndex_FunctionScope;
}

int funcGetPrecision()
{
  bool boolLoopKick = false;
  int intPrecision_FunctionScope;
  cout << endl << "We have to get a precision before we can proceed." << endl
       << "Please enter a number between zero and eight.";

  do
  {
    cout << endl << "Enter Value: ";
    cin >> intPrecision_FunctionScope;
    if ((intPrecision_FunctionScope < cMAX_PRECISION) &&
        (intPrecision_FunctionScope > cMIN_PRECISION))
    {
      boolLoopKick = true;
    }
    else
    {
      funcErrorMessage();
    }

  } while (boolLoopKick == false);

  return intPrecision_FunctionScope;
}

bool funcSoupIsHomemade()
{
  char charMenuOption_HomemadeSoup;
  bool boolSoupIsHomemade = false, boolLoopKick = false;
  // boolSoupIsHomemade is intitalized because of if statement fall through

  cout << "Is The Soup Homemade (Y/N): ";
  cin >> charMenuOption_HomemadeSoup;
  do
  {
    if (charMenuOption_HomemadeSoup == 'Y' ||
      charMenuOption_HomemadeSoup == 'y')
    {
      boolSoupIsHomemade = true;
      boolLoopKick = true;
    }
    else if (charMenuOption_HomemadeSoup == 'N' ||
         charMenuOption_HomemadeSoup == 'n')
    {
      boolSoupIsHomemade = false;
      boolLoopKick = true;
    }
    else
    {
      funcErrorMessage();
      boolLoopKick = false;
    }
  } while (boolLoopKick == false);

  return boolSoupIsHomemade;
}

float funcCalculateWavelength(float const floHairIndex)
{ // hair
  float floWavelength_FunctionScope;

  // Could have simplified to a simple return statement, but less readable IMO
  floWavelength_FunctionScope = floHairIndex * cHAIRINDEX_MULTIPLIER;

  return floWavelength_FunctionScope;
}

int funcGetGooGrade()
{
  int intGooGrade_FunctionScope;
  bool boolLoopKick = false;

  cout << endl << "Please enter the Goo Grade.";
  do

  {
    cout << endl << "Enter Value: ";
    cin >> intGooGrade_FunctionScope;

    if (intGooGrade_FunctionScope <= cMAX_GOOGRADE &&
        intGooGrade_FunctionScope >= cMIN_GOOGRADE)
    {
      boolLoopKick = true;
    }
    else
    {
      funcErrorMessage();
      boolLoopKick = true;
    }
  } while (boolLoopKick == false);

  return intGooGrade_FunctionScope;
}

int funcGetAlienHeight()
{
  int intAlienHeight = 0;
  char charMenuOption_AlienHeight;
  bool boolLoopKick;

  cout << "Please Select, What You Believe, The Alien Height Is." << endl
       << "1. 1 Foot" << endl
       << "2. 2 Feet" << endl
       << "3. 3 Feet" << endl;
  do
  {
    cout << "Enter Option: ";
    cin >> charMenuOption_AlienHeight;

    switch (charMenuOption_AlienHeight)
    {
      case '1':
        intAlienHeight = 1;
        boolLoopKick = true;
        break;

      case '2':
        intAlienHeight = 2;
        boolLoopKick = true;
        break;

      case '3':
        intAlienHeight = 3;
        boolLoopKick = true;
        break;

      default:
        boolLoopKick = false;
        funcErrorMessage();

    }
  } while (boolLoopKick == false);

  return intAlienHeight;
}


float funcCalculateWavelength(float const floHairIndex, int const intPrecision)
{ // Saliva and Hair
  float floWavelength_FunctionScope;

  for (int i = 1; i != (intPrecision+1); i++)

  { // push everything up by one to prevent division by zero
    floWavelength_FunctionScope+= (1/static_cast<float>(i));
  }
  floWavelength_FunctionScope *= (100 * floHairIndex);

  return floWavelength_FunctionScope;
}

float funcCalculateWavelength(int const intPrecision,
                              bool const boolSoupIsHomemade)
{
  float floWavelength_FunctionScope;

  int intPowerFunction = 1; // initialize prior to loop,
  // resets for next case execution

  for (int i = 0; i != (intPrecision+1); i++)
  { // needs one more iteration to compensate for the beginning 1
    floWavelength_FunctionScope+= 1/(static_cast<float>(intPowerFunction));
    intPowerFunction *= 2;
  }
  floWavelength_FunctionScope *= 100;

  if (boolSoupIsHomemade == true)
  {
    floWavelength_FunctionScope += cHOMEMADESOUP_ADDER;
  }

  return floWavelength_FunctionScope;
}

float funcCalculateWavelength(const int intGooGrade, const int intAlienHeight)
{
  float floWavelength_FunctionScope = 0;

  switch (intGooGrade)

  {
    case 6:
      floWavelength_FunctionScope += cADDER_GREENGOOGRADE_6;
    case 5:
      floWavelength_FunctionScope += cADDER_GREENGOOGRADE_5;
    case 4:
      floWavelength_FunctionScope += cADDER_GREENGOOGRADE_4;
    case 3:
      floWavelength_FunctionScope += cADDER_GREENGOOGRADE_3;
    case 2:
      floWavelength_FunctionScope += cADDER_GREENGOOGRADE_2;
    case 1:
      floWavelength_FunctionScope += cADDER_GREENGOOGRADE_1;
    case 0:
      floWavelength_FunctionScope += cGREENGOO_BASEWAVELENGTH;
  }

  floWavelength_FunctionScope *= intAlienHeight;

  return floWavelength_FunctionScope;
}

void funcPresentResults(const int intWavelength)
{
  cout << endl << "Wavelength: "
       << intWavelength << " nm." << endl;

  return;

}
// [CLOSING MESSAGE]
void funcClosingMessage()
{
  cout << endl << "Thank you for using Wavelength Calculator 5001" << endl
       << "Have a pleasant day!" << endl << endl;

  return;
}
// [MAINTENANCE FUNCTIONS]
int funcFloatToIntegerAndRounding(const float floNumberToRound)
{
  int intReturningNumber;

  intReturningNumber = static_cast<int>((floNumberToRound + .5));

  return intReturningNumber;
}

void funcErrorMessage()
{
  cout << endl << "Error, Invalid Option. Please Try Again."
       << endl;

  return;
}