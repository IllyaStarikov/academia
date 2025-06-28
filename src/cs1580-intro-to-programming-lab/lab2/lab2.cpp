// Programmer: Illya Starikov — 18083141
// Instructor: Armita   Section:<E>  09/02/2014
// Simple multipication of two variables.

//including the I/O stream library
#include <iostream>
using namespace std;

int main()
{
  int first; // a within formula c = a * b
  int second;  // b within formula c = a * b
  int product; // c within formula c = a * b
  string name;
        
  // welcome message
  cout << "Enter your name: ";
  cin >> name;
  cout << endl << "Welcome " << name << endl << endl;
                
  // read multiplicand from keyboard
  cout << "Enter the multiplicand: ";
  cin >> first;
                       
  // read multiplier from keyboard
  cout << "Enter the multiplier: ";
  cin >> second;
                            
  // perform multiplication as * operator
  product = first * second;
                                
  // display the result
  cout << first << " * " << second << " = " << product << endl;
                                    
  return 0;
}
