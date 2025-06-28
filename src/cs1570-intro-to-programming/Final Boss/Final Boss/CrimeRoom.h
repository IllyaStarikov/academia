// Programmers: Illya Starikov and Alex Androff         Date: 04/17/15
// File: CrimeRoom.h                                    Class: CS1570A
// Purpose: Define Crimeroom to match associated protyped functions.

/*
--------------------CrimeRoom--------------------
Description:   The default constructor.
Pre-Condition:   A calling object must be initilized and declared.
Post-Condition:  The murder in the room value is set to false and the
dead resident string is set to false.
*/

/*
--------------------meeting--------------------
Description:   Meeting of two residents, and determines if the residents
kill each other.
Pre-Condition:   Two valid residents must be passed.
Post-Condition:  Checks to see if a murder has occured, if so, determines
who is murdered.
*/

/*
--------------------triedToKillTeacher--------------------
Description:  Basically, sees to see if Mr. Price is the victim. If so,
he beats up whoever tries to attack him.
Pre-Condition:  The victim must be the teacher (Price).
Post-Condition: Whoever attempted to kill Price gets killed.
*/

/*
--------------------murder--------------------
Description:   Randomly determines if a murder has occurred,
based on a probability.
Pre-Condition:   None.
Post-Condition:  Returns a boolean to see if a murder has occurred.
*/

/*
--------------------checkRoom--------------------
Description:   Checks the room see if there is a dead body in there.
Pre-Condition:   None.
Post-Condition:  A boolean to determine if someone is dead within the room.
*/

/*
--------------------getEvidence--------------------
Description:   Returns a copy of the evidence.
Pre-Condition:   None.
Post-Condition:  Returns the forensic data of the room.
*/

/*
--------------------ACCESSORS--------------------
Description:   Returns the respective member data.
Pre-Condition:   None.
Post-Condition:  Returns the respective data of the respective type.
*/

#ifndef Final_Boss__CrimeRoom
#define Final_Boss__CrimeRoom

#include <iostream>

#include "Resident.h"
#include "Forensic Data.h"

class CrimeRoom {
public:
  CrimeRoom();
  void meeting(Resident residentOne, Resident residentTwo);
  void triedToKillTeacher(Resident teacher, Resident attemptedMurderer);
  bool murder();
  bool checkRoom()const;
  forensicData getEvidence();

  // Accessors
  char getRoomDNACharacter(const int positionInArray)const {
    return m_roomForensics.m_DNA[positionInArray]; }
  std::string getDeadResident()const {
    return m_deadResident; }
private:
  bool m_murderCommitted;
  std::string m_deadResident;
  forensicData m_roomForensics;

};

#endif /* defined(Final_Boss__CrimeRoom) */
