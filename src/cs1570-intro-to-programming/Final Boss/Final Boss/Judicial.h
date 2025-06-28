// Programmers: Illya Starikov and Alex Androff         Date: 04/17/15
// File: Judicial.h                                     Class: CS1570A
// Purpose: Write definitions of Judicial Class

/*
--------------------Judicial--------------------
Description:   Default constructor.
Pre-Condition:   A judgeName *MUST* be passed.
Post-Condition:  The judge class is.. constructed.
*/

/*
--------------------judgment--------------------
Description:   Judges the outcome of the trial.. which is probably rigged.
Pre-Condition:   There must be a judge calling object.
Post-Condition:  Determining if the resident is guilty or not.
*/

/*
--------------------outcomeAnnouncement--------------------
Description:   To make the announcement if the person is guily/not guilty.
Pre-Condition:   The name of the person on trial and if the conviction has
occurred must be passed.
Post-Condition:  The announcement is made, cout statements. Side effects.
*/

/*
--------------------announceTheJudge--------------------
Description:   Makes the announcement of the judge coming to court.
Pre-Condition:   A judge object must be created.
Post-Condition:  Cout statements, side effects.
*/

#ifndef __Final_Boss__Judicial__
#define __Final_Boss__Judicial__

#include <iostream>

#include "Constants.h"

class Judicial
{
public:
  Judicial(std::string judgeName,
       int judgeConvictionRating = DEFAULT_CONVICTION_RATE);
  bool judgement(const std::string nameOfPrisoner);
  void outcomeAnnouncement(const bool convictedToDeath,
               const std::string nameOfPrisoner)const;
  void announceTheJudge()const;

private:
  std::string m_name;
  int m_convictionRate;
};
#endif /* defined(__Final_Boss__Judicial__) */
