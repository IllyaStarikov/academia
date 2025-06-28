// Programmer: Illya Starikov				Date:
// File: SherlockHolmes.cpp				Class: cs 1570 A 
// Purpose: To play a gallant detective and figure 
// the probably of some weirdo cannabalizing another.

#include <iostream>

using namespace::std;

int main()
{
  // Function Variables
  int intMenuOption, intCannibalismRobberyMenu;
  
  // Massive amount of constants
  const int constA_PARANOID_NARCISSISTIC_CANNIBALISM = 3;
  const int constA_PARANOID_SADISTIC_CANNIBALISM = 4;
  const int constA_SCHIZOID_DEPRESSIVE_CANNIBALISM = 5;
  const int constA_SCHIZOID_COMPULSIVE_CANNIBALISM = 3;

  const int constB_ANTISOCIAL_AVOIDANT_CANNIBALISM = 2;
  const int constB_ANTISOCIAL_CREEPY_CANNIBALISM = 9;
  const int constB_JUSTAJERK_STUPID_CANNIBALISM = 12;
  const int constB_JUSTAJERK_WEIRDO_CANNIBALISM = 33;

  const int constA_PARANOID_NARCISSISTIC_ROBBERY = 12;
  const int constA_PARANOID_SADISTIC_ROBBERY = 1;
  const int constA_SCHIZOID_DEPRESSIVE_ROBBERY = 3;
  const int constA_SCHIZOID_COMPULSIVE_ROBBERY = 7;

  const int constB_ANTISOCIAL_AVOIDANT_ROBBERY = 8;
  const int constB_ANTISOCIAL_CREEPY_ROBBERY = 3;
  const int constB_JUSTAJERK_STUPID_ROBBERY = 22;
  const int constB_JUSTAJERK_WEIRDO_ROBBERY = 45;

  int intChanceOfCommittingCannibalism_SuspectOne = 0, 
  intChanceOfCommittingRobbery_SuspectOne = 0; //  Suspect One / Initialized To Prevent 
  // If statement fall through
  int intChanceOfCommittingCannibalism_SuspectTwo = 0, 
  intChanceOfCommittingRobbery_SuspectTwo = 0; //  Suspect Two / Initialized To Prevent 
  // If statement fall through
  int intSuspectNumber = 1;
  
  string strUserName;
  
  cout <<
  "Hello, Welcome" << endl <<
  "What's Your Name, Stranger? ";
  cin >> strUserName;
  
  cout << "Okay, " << strUserName << ", let's get started!" << endl << endl;
  
  while (intCannibalismRobberyMenu != 1 && intCannibalismRobberyMenu != 2)
  {
    cout <<
    "Please Select The Crime" << endl <<
    "1. Cannibalism" << endl <<
    "2. Robbery" << endl <<
    "*Numeric* Menu Option: ";
    cin >> intCannibalismRobberyMenu;
    if (intCannibalismRobberyMenu != 1 && intCannibalismRobberyMenu != 2)
    {
      cout << endl << "Error – Invalid Option. Please Try Again" << endl;
    }
  }
  do
  {
    
    do
    {
      cout << endl << endl <<
      "Suspect " << intSuspectNumber << endl <<
      "First, Cluster" << endl <<
      "1. A – Odd Disorders" << endl <<
      "2. B – Dramato-Erratic" << endl <<
      "*Numeric* Menu Option: ";
      cin >> intMenuOption;
      cout << endl;
      
      if (intMenuOption != 1 && intMenuOption != 2)
      {
        cout << endl << "Error – Invalid Option. Please Try Again" << endl;
      }
    } while (intMenuOption != 1 && intMenuOption != 2);
    
    // if blocks begin
    if (intMenuOption == 1)
    { // [CLUSTER] A – Odd Disorders
      do
      {
        
        cout <<
        "Second, Personality Disorder" << endl <<
        "1. Paranoid" << endl <<
        "2. Schizoid" << endl <<
        "*Numeric* Menu Option: ";
        cin >> intMenuOption;
        cout << endl;
        
        if (intMenuOption != 1 && intMenuOption != 2)
        {
          cout << endl << "Error – Invalid Option. Please Try Again" << endl;
        }
      } while (intMenuOption != 1 && intMenuOption != 2);
      
      if (intMenuOption == 1)
      { // [PERSONALITY DISORDER] Paranoid
        do
        {
          cout <<
          "Second, Personality Disorder" << endl <<
          "1. Narcissistic" << endl <<
          "2. Sadistic" << endl <<
          "*Numeric* Menu Option: ";
          cin >> intMenuOption;
          cout << endl;
          
          if (intMenuOption != 1 && intMenuOption != 2)
          {
            cout << endl << "Error – Invalid Option. Please Try Again" << endl;
          }
        } while (intMenuOption != 1 && intMenuOption != 2);
        
        if (intMenuOption == 1)
        { // [FEATURE] Chance of Committing Cannibalism / Chance of committing Robbery
          if (intSuspectNumber == 1)
          {
            intChanceOfCommittingCannibalism_SuspectOne = constA_PARANOID_NARCISSISTIC_CANNIBALISM;
            intChanceOfCommittingRobbery_SuspectOne = constA_PARANOID_NARCISSISTIC_ROBBERY;
          }
          else if (intSuspectNumber == 2)
          {
            intChanceOfCommittingCannibalism_SuspectTwo = constA_PARANOID_NARCISSISTIC_CANNIBALISM;
            intChanceOfCommittingRobbery_SuspectTwo = constA_PARANOID_NARCISSISTIC_ROBBERY;
          }
        }
        else if (intMenuOption == 2)
        { // Chance of Committing Cannibalism / Chance of committing Robbery
          if (intSuspectNumber == 1)
          {
            intChanceOfCommittingCannibalism_SuspectOne = constA_PARANOID_SADISTIC_CANNIBALISM;
            intChanceOfCommittingRobbery_SuspectOne = constA_PARANOID_SADISTIC_ROBBERY;
          }
          else if (intSuspectNumber == 2)
          {
            intChanceOfCommittingCannibalism_SuspectTwo = constA_PARANOID_SADISTIC_CANNIBALISM;
            intChanceOfCommittingRobbery_SuspectTwo = constA_PARANOID_SADISTIC_ROBBERY;
          }
        }
        
      }
      else if (intMenuOption == 2)
      { // [PERSONALITY DISORDER] Schizoid
        do
        {
          
          cout <<
          "Second, Personality Disorder" << endl <<
          "1. Depressive" << endl <<
          "2. Compulsive" << endl <<
          "*Numeric* Menu Option: ";
          cin >> intMenuOption;
          cout << endl;
          
          if (intMenuOption != 1 && intMenuOption != 2)
          {
            cout << endl << "Error – Invalid Option. Please Try Again" << endl;
          }
        } while (intMenuOption != 1 && intMenuOption != 2);
        
        if (intMenuOption == 1)
        { // [FEATURE] Chance of Committing Cannibalism / Chance of committing Robbery
          if (intSuspectNumber == 1)
          {
            intChanceOfCommittingCannibalism_SuspectOne = constA_SCHIZOID_DEPRESSIVE_CANNIBALISM;
            intChanceOfCommittingRobbery_SuspectOne = constA_SCHIZOID_DEPRESSIVE_ROBBERY;
          }
          else if (intSuspectNumber == 2)
          {
            intChanceOfCommittingCannibalism_SuspectTwo = constA_SCHIZOID_DEPRESSIVE_CANNIBALISM;
            intChanceOfCommittingRobbery_SuspectTwo = constA_SCHIZOID_DEPRESSIVE_ROBBERY;
          }
        }
        else if (intMenuOption == 2)
        { // [FEATURE] Chance of Committing Cannibalism / Chance of committing Robbery
          if (intSuspectNumber == 1)
          {
            intChanceOfCommittingCannibalism_SuspectOne = constA_SCHIZOID_COMPULSIVE_CANNIBALISM;
            intChanceOfCommittingRobbery_SuspectOne = constA_SCHIZOID_COMPULSIVE_ROBBERY;
          }
          else if (intSuspectNumber == 2)
          {
            intChanceOfCommittingCannibalism_SuspectTwo = constA_SCHIZOID_COMPULSIVE_CANNIBALISM ;
            intChanceOfCommittingRobbery_SuspectTwo = constA_SCHIZOID_COMPULSIVE_ROBBERY;
          }
          
        }
      }
    }
    else if(intMenuOption == 2)
    { // [CLUSTER] B – Dramato-Erratic
      do
      {
        
        cout <<
        "Second, Personality Disorder" << endl <<
        "1. Antisocial" << endl <<
        "2. Just a Jerk" << endl <<
        "*Numeric* Menu Option: ";
        cin >> intMenuOption;
        
        if (intMenuOption != 1 && intMenuOption != 2)
        {
          cout << endl << "Error – Invalid Option. Please Try Again" << endl;
        }
      } while (intMenuOption != 1 && intMenuOption != 2);
      
      if (intMenuOption == 1)
      { // [PERSONALITY DISORDER] Antisocial
        do
        {
          cout <<
          "Second, Personality Disorder" << endl <<
          "1. Avoidant" << endl <<
          "2. Creepy" << endl <<
          "*Numeric* Menu Option: ";
          cin >> intMenuOption;
          cout << endl;
          
          if (intMenuOption != 1 && intMenuOption != 2)
          {
            cout << endl << "Error – Invalid Option. Please Try Again" << endl;
          }
        } while (intMenuOption != 1 && intMenuOption != 2);
        
        if (intMenuOption == 1)
        { // [FEATURE] Chance of Committing Cannibalism / Chance of committing Robbery
          if (intSuspectNumber == 1)
          {
            intChanceOfCommittingCannibalism_SuspectOne = constB_ANTISOCIAL_AVOIDANT_CANNIBALISM;
            intChanceOfCommittingRobbery_SuspectOne = constB_ANTISOCIAL_AVOIDANT_ROBBERY;
          }
          else if (intSuspectNumber == 2)
          {
            intChanceOfCommittingCannibalism_SuspectTwo = constB_ANTISOCIAL_AVOIDANT_CANNIBALISM;
            intChanceOfCommittingRobbery_SuspectTwo = constB_ANTISOCIAL_AVOIDANT_ROBBERY;
          }
          
        }
        else if (intMenuOption == 2)
        { // [FEATURE] Chance of Committing Cannibalism / Chance of committing Robbery
          if (intSuspectNumber == 1)
          {
            intChanceOfCommittingCannibalism_SuspectOne = constB_ANTISOCIAL_CREEPY_CANNIBALISM;
            intChanceOfCommittingRobbery_SuspectOne = constB_ANTISOCIAL_CREEPY_ROBBERY;
          }
          else if (intSuspectNumber == 2)
          {
            intChanceOfCommittingCannibalism_SuspectTwo = constB_ANTISOCIAL_CREEPY_CANNIBALISM;
            intChanceOfCommittingRobbery_SuspectTwo = constB_ANTISOCIAL_CREEPY_ROBBERY;
          }
          
        }
      }
      else if (intMenuOption == 2)
      { // [PERSONALITY DISORDER] Just a Jerk
        do
        {
          
          cout <<
          "Second, Personality Disorder" << endl <<
          "1. Stupid" << endl <<
          "2. Weirdo" << endl <<
          "*Numeric* Menu Option: ";
          cin >> intMenuOption;
          cout << endl;
          
          if (intMenuOption != 1 && intMenuOption != 2)
          {
            cout << endl << "Error – Invalid Option. Please Try Again" << endl;
          }
        } while (intMenuOption != 1 && intMenuOption != 2);
        
        if (intMenuOption == 1)
        { // [FEATURE] Chance of Committing Cannibalism / Chance of committing Robbery
          if (intSuspectNumber == 1)
          {
            intChanceOfCommittingCannibalism_SuspectOne = constB_JUSTAJERK_STUPID_CANNIBALISM;
            intChanceOfCommittingRobbery_SuspectOne = constB_JUSTAJERK_STUPID_ROBBERY;
          }
          else if (intSuspectNumber == 2)
          {
            intChanceOfCommittingCannibalism_SuspectTwo = constB_JUSTAJERK_STUPID_CANNIBALISM;
            intChanceOfCommittingRobbery_SuspectTwo = constB_JUSTAJERK_STUPID_ROBBERY;
          }
        }
        else if (intMenuOption == 2)
        { // [FEATURE] Chance of Committing Cannibalism / Chance of committing Robbery
          if (intSuspectNumber == 1)
          {
            intChanceOfCommittingCannibalism_SuspectOne = constB_JUSTAJERK_WEIRDO_CANNIBALISM;
            intChanceOfCommittingRobbery_SuspectOne = constB_JUSTAJERK_WEIRDO_ROBBERY;
          }
          else if (intSuspectNumber == 2)
          {
            intChanceOfCommittingCannibalism_SuspectTwo = constB_JUSTAJERK_WEIRDO_CANNIBALISM;
            intChanceOfCommittingRobbery_SuspectTwo = constB_JUSTAJERK_WEIRDO_ROBBERY;
          }
          
        }
      }
    }
    intSuspectNumber++;
  } while (intSuspectNumber < 3);
  
  // SUMMARY
  if (intCannibalismRobberyMenu == 1)
  {
    cout << "[Suspect 1] Chance of Committing Cannibalism: " << intChanceOfCommittingCannibalism_SuspectOne << "%" << endl;
    cout << "[Suspect 2] Chance of Committing Cannibalism: " << intChanceOfCommittingCannibalism_SuspectTwo << "%" << endl;
    if (intChanceOfCommittingCannibalism_SuspectOne > intChanceOfCommittingCannibalism_SuspectTwo)
    {
      cout << "Suspect 1 Was The Culprit!";
    }
    else if (intChanceOfCommittingCannibalism_SuspectOne < intChanceOfCommittingCannibalism_SuspectTwo)
    {
      cout << "Suspect 2 Was The Culprit!";
    }
    else if (intChanceOfCommittingCannibalism_SuspectOne == intChanceOfCommittingCannibalism_SuspectTwo) 
    {
      cout << "Suspect 1 Is As Guilty As Suspect 2";
    }
  }
  else if (intCannibalismRobberyMenu == 2) 
  {
    cout << "[Suspect 1] Chance of Committing Robbery: " << intChanceOfCommittingRobbery_SuspectOne << "%" << endl;
    cout << "[Suspect 2] Chance of Committing Robbery: " << intChanceOfCommittingRobbery_SuspectTwo << "%" << endl;
    if (intChanceOfCommittingRobbery_SuspectOne > intChanceOfCommittingRobbery_SuspectTwo) 
    {
      cout << "Suspect 1 Was The Culprit!";
    }
    else if (intChanceOfCommittingRobbery_SuspectOne < intChanceOfCommittingRobbery_SuspectTwo) 
    {
      cout << "Suspect 2 Was The Culprit!";
    }
    else if (intChanceOfCommittingRobbery_SuspectOne == intChanceOfCommittingRobbery_SuspectTwo) 
    {
      cout << "Suspect 1 Is As Guilty As Suspect 2";
    }
  }
  cout << endl;
  cout << 
  "Thank you for using this program, signing off now.." << endl <<
  "Good Bye!";
  
  return 0; // Return Type int
  
}