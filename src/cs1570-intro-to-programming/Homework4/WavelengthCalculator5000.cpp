// Programmer: Illya Starikov        Date: 2/19/2015
// File: WavelengthCalculator5000    Class: CS1570 A
// Purpose to make it easy to determine what the wavelength
// of a specified substance is. Very scientific.

#include <iostream>

using namespace std;
int main()
{
  // constants
  const int cWAVELENGTH_HAIR = 400;
  
  // constant adders
  const int cGREENGOO_BASEWAVELENGTH = 200;
  const int cADDER_GREENGOOGRADE_1 = 43, cADDER_GREENGOOGRADE_2 = 17;
  const int cADDER_GREENGOOGRADE_3 = 23, cADDER_GREENGOOGRADE_4 = 77;
  const int cADDER_GREENGOOGRADE_5 = 55, cADDER_GREENGOOGRADE_6 = 35;
  
  
  float floTotal = 0; // reuseable total
  
  int intMenu;
  int intOutputWavelength, intDenominator;
  int intGooGrade, intPowerFunction; // Declare recyclables
  bool boolProgramQuit = false, boolLoopKick = false; // Loop management
  
  do
  {
    cout << 
    "1.  Hair"                                      << 
    "\n2.  Saliva and Hair"                         << 
    "\n3.  Chicken-noodle Soup, Saliva and Hair"    << 
    "\n4.  Green Goo"                               << 
    "\n5.  Exit"                                    << 
    "\nMenu Option: ";
    cin >> intMenu;
    
    switch (intMenu)
    {
      case 1: // Hair
        intOutputWavelength = cWAVELENGTH_HAIR; // keep consistency by outputting same variable via assignment
        
        cout <<
        "Hair: " << intOutputWavelength << "nm." << endl << endl;
        break;
        
      case 2: // Saliva and Hair
        cout << endl <<
        "We have to get a precision before we can proceed." << endl <<
        "Please enter a number between zero and eight.";
        
        do
        {
          
          cout << endl << "Enter Value: ";
          cin >> intDenominator;
          if ((intDenominator < 8) && (intDenominator > 0))
          {
            boolLoopKick = true;
          } else
          {
            cout << endl << "Error – Please Try Again.";
          }
          
        } while (boolLoopKick == false);
        
        for (int i = 1; i != (intDenominator+1); i++)
        { // push everything up by one to prevent division by zero
          floTotal+= (1/static_cast<float>(i));
        }
        floTotal *= 100; // i have no idea what this is for, can't think of a constant name
        
        intOutputWavelength = static_cast<float>(floTotal); // requested output be an integer
        cout << "Saliva and Hair: " << intOutputWavelength << "nm." << endl << endl;
        
        break;
        
      case 3: // Chicken-noodle Soup, Saliva and Hair
        cout << endl <<
        "We have to get a precision before we can proceed." << endl <<
        "Please enter a number between zero and eight.";
        
        do
        {
          
          cout << endl << "Enter Value: ";
          cin >> intDenominator;
          if ((intDenominator < 8) && (intDenominator > 0))
          {
            boolLoopKick = true;
          } else
          {
            cout << endl << "Error [Invalid Option] – Please Try Again.";
          }
          
        } while (boolLoopKick == false);
        
        intPowerFunction = 1; // initialize prior to loop, resets for next case execution
        
        for (int i = 0; i != (intDenominator+1); i++)
        { // needs one more iteration to compensate for the beginning 1
          floTotal+= 1/(static_cast<float>(intPowerFunction));
          intPowerFunction *= 2;
        }
        floTotal *= 100; // i have no idea what this is for, can't think of a constant name
        
        intOutputWavelength = static_cast<int>(floTotal); // requested output be an integer
        cout << "Chicken-noodle Soup, Saliva and Hair: " << intOutputWavelength << 
        "nm." << endl << endl;
        break;
        
      case 4:
        cout <<
        "Please enter the Goo Grade.";
        do
        {
          cout << endl << "Enter Value: ";
          cin >> intGooGrade;
          
          if (intGooGrade <= 6 && intGooGrade >= 0)
          {
            boolLoopKick = true;
          } else
          {
            cout << endl << "Error [Invalid Option] – Please Try Again.";
          }
        } while (boolLoopKick == false);
        
        // switch case fall through. watch the magic
        switch (intGooGrade)
      {
        case 6:
          floTotal += cADDER_GREENGOOGRADE_6;
        case 5:
          floTotal += cADDER_GREENGOOGRADE_5;
        case 4:
          floTotal += cADDER_GREENGOOGRADE_4;
        case 3:
          floTotal += cADDER_GREENGOOGRADE_3;
        case 2:
          floTotal += cADDER_GREENGOOGRADE_2;
        case 1:
          floTotal += cADDER_GREENGOOGRADE_1;
        case 0:
          floTotal += cGREENGOO_BASEWAVELENGTH;
      }
        intOutputWavelength = static_cast<int>(floTotal); // requested output be an integer
        
        cout << "Green Goo: " << intOutputWavelength << "nm." << endl << endl;
        
        break;
        
      case 5: // Program Quit
        boolProgramQuit = true;
        break;
        
      default:
        cout << "Error [Invalid Option] – Please Try Again" << endl << endl;
        break;
    }
    boolLoopKick = false; // Reset the loop manager for next iteration
    floTotal = 0;   // clear for the next iteration
  } while (boolProgramQuit == false);
  
  cout <<
  "Thank you for using Wavelength Calculator 5000" << endl <<
  "Signing off now..";
  
  return 0; // because
}