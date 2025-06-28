// Programmer: Illya Starikov 18083141
// Section: 3E
// File: lab5.cpp
// Description: to calculate average sum total of cotes

#include <iostream>

using namespace std;
int main(int argc, char *argv[]) {
  int intTotal_Apple_A = 0, intTotal_Lenovo_B = 0, intTotal_Dell_C = 0, intTotal_HP_D = 0; // totals for respective options
  int intTotal_Wasted = 0;

  const int cTOTAL = 10;
  
  char charMenuOption; // recyclable menu option
  
  // main menu
  cout <<
  "~ ~ ~ Welcome to E-Voting System ~ ~ ~" <<
  "Here are Laptop brands"
  "\nA. Apple" <<
  "\nB. Lenovo" <<
  "\nC. Dell" <<
  "\nD. HP";// buffer clear before cin
  for (int i = 0; i != cTOTAL; i++) // do cTotal Times
  {
  cout << endl << "*character* Menu Option: ";
  cin >> charMenuOption;
  
  switch (charMenuOption) {
    case ('A'):
    case ('a'): // Apple
      ++intTotal_Apple_A;
      cout << "You voted for Apple";
      break;
      
    case ('B'):
    case ('b'): // Lenovo
      ++intTotal_Lenovo_B;
      cout << "You voted for Lenovo";
      break;
      
    case ('C'):
    case ('c'): // Dell
      ++intTotal_Dell_C;
      cout << "You voted for Dell";
      break;
      
    case ('D'):
    case ('d'): // HP
      ++intTotal_HP_D;
      cout << "You voted for HP";
      break;
      
    default:
      cout << "You wasted your vote";
      ++intTotal_Wasted;
      
  }
  }

  cout << "* ~ * Here is the E-Voting Summary * ~ *" <<
  "\nLaptops     " <<  "Votes"     << "   " << "percentages (%)" <<
  "\nApple       " << intTotal_Apple_A   << "       " << static_cast<float>(intTotal_Apple_A) / cTOTAL  <<
  "\nLenovo      " << intTotal_Lenovo_B  << "       " << static_cast<float>(intTotal_Lenovo_B) / cTOTAL <<
  "\nDell        " << intTotal_Dell_C  << "       " << static_cast<float>(intTotal_Dell_C) / cTOTAL   <<
  "\nHP        " << intTotal_HP_D    << "       " << static_cast<float>(intTotal_HP_D) / cTOTAL   <<
  "\nWasted Votes    " << intTotal_Wasted  << "       " << static_cast<float>(intTotal_Wasted) / cTOTAL   <<
  "\n\nThanks for using the E-Voting system" <<
  "\nHave a Nice Day!" << endl << endl;
  
  return 0;
}