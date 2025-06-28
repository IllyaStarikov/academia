// Programmer: Illya Starikov                                Date: 03/06/15
// File: WavelengthCalculator5001.cpp                        Class: CS1570A
// Purpose: To find the wavelengths of.. very, very strange matter.

#include "WavelengthCalculator5001.h"

int main()
{
  char charMenuOption;
  int intWavelength;
  bool boolPresentResults = true;

  funcGreetingMessage();

  do
  {
    funcPresentMenu_GetInput(charMenuOption);
    funcMainMenu(charMenuOption, intWavelength, boolPresentResults);

    if (boolPresentResults == true)
    {
      funcPresentResults(intWavelength);
    }
  } while (charMenuOption != '5');

  funcClosingMessage();

  return 0;
}
