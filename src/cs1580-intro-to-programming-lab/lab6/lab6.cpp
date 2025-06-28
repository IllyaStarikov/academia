// Programmer: Illya Starikov
// Section: 3E
// File: lab6.cpp
// Description: To calculate average

#include <iostream>

// Functions — *note to grader* func is my hungarian abreviation for function
// Won't you take me to, funcy caalllll.
void funcGreet();
float funcReadNumber();
float funcArithmeticMean(float const floNumber1, const float floNumber2, float const floNumber3);
float funcHarmonicMean(float const floNumber1, float const floNumber2, float const floNumber3);
void funcPrintResult(float const floHarmonic, float const floArithmetic); //
void funcSignoff(); // sign off message

const int cTOTALNUMBEROFNUMBERS = 3; // to be able to change for multiple numbers
// ideally, i would just use an array and not deal with it.

using namespace std; // create template namespace

int main() 
{
  float floNumber1, floNumber2, floNumber3; // for passing values of nubmers
  
  float floArithmeticMean, floHarmonicMean; // the mean and harmonic mean
  
  funcGreet();
  
  floNumber1 = funcReadNumber(); // assign the first number from function callback
  floNumber2 = funcReadNumber(); // and again for second
  floNumber3 = funcReadNumber();
  
  floArithmeticMean = funcArithmeticMean(floNumber1, floNumber2, floNumber3);
   // call the aritmetic function
  floHarmonicMean = funcHarmonicMean(floNumber1, floNumber2, floNumber3); // do so again
  
  funcPrintResult(floHarmonicMean, floArithmeticMean);
  
  funcSignoff();
}

void funcGreet() 
{
  
  cout << "Hello," << endl <<
  "Welcome to the Harmonic and Arithmetic Mean" << endl << endl;
  
  return;
}

float funcReadNumber() 
{
  float floInputtedNumber;
  do 
  {
    cout << "Please Enter a Number: ";
    cin >> floInputtedNumber;
    
    if (floInputtedNumber < 1) 
    { // to check for valid data
      cout << "Sorry, that is invalid." << endl << "Please try again" << endl;
    }
  } while (floInputtedNumber < 1);
  return floInputtedNumber;
}

float funcArithmeticMean(float const floNumber1, const float floNumber2, float const floNumber3) 
{
  float floAverage;
  
  floAverage = (floNumber1 + floNumber2 + floNumber3) / cTOTALNUMBEROFNUMBERS;// calculate
  
  return floAverage; // return the value neccarsary for arthmetic
}

float funcHarmonicMean(float const floNumber1, float floNumber2, float floNumber3)
{
  float floAverage, floDenominator;
  
  floDenominator = (1/ floNumber1) + (1/ floNumber2) + (1/ floNumber3);
  floAverage = cTOTALNUMBEROFNUMBERS / floDenominator;
  
  return floAverage;
}

void funcPrintResult(float const floHarmonic, float const floArithmetic) 
{
  cout<< endl  << // display output
  "Arithmetic Mean: " << floArithmetic << endl <<
  "Harmonic Mean: " << floHarmonic << endl;
}

void funcSignoff() 
{
  cout << endl <<
  "Have a Good Day!";
}
