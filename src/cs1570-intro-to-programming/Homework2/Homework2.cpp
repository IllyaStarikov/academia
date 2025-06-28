// @file Homework2.cpp
// @author Illya Starikov - Section 1A 
// @brief Calculuation of GGPA

// Include libraries, headers, etc.
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
  // Variable Decleration
  const int constALIEN_SPLATTER_SPREAD = 1;

    
  int intHeight, intLength, intWidth;
  float floGamma;

    
  float floAlpha, floBeta;
  float floResultX, floResultY;

    
  // Welcome Message and User Input
  cout << "Welcome!" << endl << "You are running, the GGPA Program" << endl << endl << 
          "First, what is the height from the floor of the green "
          "goo spatter." << endl << 
          "Enter Whole Inches: ";
  cin >> intHeight;
 
  cout << "Second, what is the width of the spatter in inches." << endl << 
          "Enter Whole Numbers: ";
  cin >> intWidth;
    
  cout << "Third, what is the length of the spatter in inches." << endl <<
          "Whole Numbers: ";
  cin >> intLength;
  
  cout << "Lastly, what is the angle (in radians)." << endl <<
          "Please Exclude π: ";
  cin >> floGamma;

    
  floAlpha = asin(static_cast<float>(intWidth - constALIEN_SPLATTER_SPREAD)
                    / (intLength - constALIEN_SPLATTER_SPREAD));
  floBeta = atan(tan(floAlpha) / sin(floGamma));

  floResultY = (intHeight) * tan(floAlpha);
  floResultX = floResultY * tan(floBeta);

  cout << "The original coordinates are:" << endl <<
  "x = " << fixed << setprecision(2) << floResultX << endl <<
  "y = " << floResultY << endl << endl << endl;
    
  // return function return type
  return 0;

} // END OF MAIN