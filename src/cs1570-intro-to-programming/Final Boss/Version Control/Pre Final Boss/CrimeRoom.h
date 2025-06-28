// Programmer: Illya Starikov                Date: 04/17/15
// File: Functions.h                      Class: CS1570A
// Purpose: Prototype the resident class.

#ifndef Final_Boss__CrimeRoom
#define Final_Boss__CrimeRoom

#include <iostream>
#include "Resident.h"

/*
CrimeRoom Constructor
Description:    To construct the CrimeRoom with defaults values.
Pre-Condition:  CrimeRoom must be intitlized.
Post-Condition: CrimeRoom is assigned random values.
*/

/*
meeting
Description:    Initializes a meeting, where two residents will be sent.
If a murder occurs, there residents will be updated as such.
Pre-Condition:  Two valid residents must be passed.
Post-Condition: Probability of a murder occurring.
*/

/*
Murder
Description:    Checks the probability of a murder occurring. And returns if
a murder has occurred.
Pre-Condition:  None.
Post-Condition: Returns a bool, true if a murder has happened, false else-wise
*/

/*
Description:    Checks to see if a murder has occurred. If so, ouput a statement
indicating such. Else, sweeps or does garbage collection (pun intended).
Pre-Condition:  None.
Post-Condition: Outputs that a murder has occurred, side effects.
*/

class CrimeRoom
{
public:
  CrimeRoom();
  void meeting(Resident residentOne, Resident residentTwo);
  bool murder();
  void checkRoom();

private:
  bool m_murderCommitted;
  int m_hair;
  std::string m_deadResident;

};

#endif /* defined(Final_Boss__CrimeRoom) */
