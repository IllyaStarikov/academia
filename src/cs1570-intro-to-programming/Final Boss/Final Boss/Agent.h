// Programmers: Illya Starikov and Alex Androff       Date: 04/17/15
// File: Agent.h                                      Class: CS1570A
// Purpose: To write the definitions of the Agent Class

/*
--------------------csiAgent--------------------
Description:  The default constructor. Sets up the agent class.
Pre-Condition:  None.
Post-Condition: Sets the name.
*/

/*
--------------------visitCrimeScene--------------------
Description:   Visit Crime Room.
Pre-Condition:   A valid room must be passed.
Post-Condition:  The gather function is called, and gathers information from
the room.
*/

/*
--------------------gatherInformation--------------------
Description:   Gathers corrupted information from the room.
Pre-Condition:   A valid room must be passed.
Post-Condition:  Room information is collected via the agent,
read for investigation.
*/

/*
--------------------perpSearch--------------------
Description:   Search a person.
Pre-Condition:   A valid resident must be passed.
Post-Condition:  A boolean is returned to show if the person is likely to
commit the crime.
*/

/*
--------------------dataCorruptionAddition--------------------
Description:   Maintenance function to corrupt the data within a range.
Pre-Condition:   The original data, how much to add (positive/negative), and
the range of corruption must be passed.
Post-Condition:  An int is returned, the valid corruption.
*/

/*
--------------------withinX--------------------
Description:  Determines if a number is within a range of a different number.
Pre-Condition:  The original number, comparing number, and margin of error must
be passed.
Post-Condition: A boolean is returned to show if the number is within
a range of a different number.
*/



#ifndef Final_Boss__CSI_Agent
#define Final_Boss__CSI_Agent

#include <iostream>

#include "Forensic Data.h"
#include "CrimeRoom.h"
#include "Resident.h"


class csiAgent
{
public:
  csiAgent();
  void visitCrimeScene(CrimeRoom roomToInvestigate);
  void gatherInformation(CrimeRoom roomToGatherInformation);
  bool perpSearch(Resident residentToSearch);

  // Maintenance Functions
  int dataCorruptionAddition(const int data, const int dataAddition,
                 const int floor, const int ceiling)const;
  bool withinX(const int originalNumber, const int comparingNumber,
         const int marginOfError)const;
private:
  std::string m_name;
  forensicData m_theEvidence;
};

#endif /* defined(Final_Boss__CSI_Agent) */
