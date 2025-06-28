// Programmer: Illya Starikov - 18083141
// Instructor: Armita Abedijaberi, 2/4/2014
// Calculation of Body Mass

// Include libraries, headers, etc.
#include <iostream>

using namespace std;

int main()
{
  // Constants
  const int constCONVERSIONFACTOR = 703;
  
  // Variables
  int intBodyMass_IBs, intBodyHeight_Inches;
  float floBMI;
  
  // Welcome Message
  cout <<
  "Welcome to the BMI calculator" << endl <<
  "Enter the Mass (IBs): ";
  cin >> intBodyMass_IBs; // get input
  
  cout <<
  "Enter the Height (inches): ";
  cin >> intBodyHeight_Inches;
  
  
  // make machine do math
  floBMI = static_cast<float>(intBodyMass_IBs * constCONVERSIONFACTOR) / (intBodyHeight_Inches * intBodyHeight_Inches);
  
  // enter statement to return values to user
  cout << "The BMI value for " << intBodyHeight_Inches << " inches and " << intBodyMass_IBs << " pounds is " << floBMI << ".";
  
  
  // return function return type
  return 0;
} // END OF MAIN
