// Programmers: Illya Starikov and Alex Androff               Date: 04/17/15
// File: Judicial.h                                          Class: CS1570A
// Purpose: Write definitions of Judicial Class

#ifndef __Final_Boss__Judicial__
#define __Final_Boss__Judicial__


#include <iostream>

#include "Constants.h"

class Judicial {
public:
    Judicial(std::string judgeName, int judgeConvictionRating = DEFAULT_CONVICTION_RATE);
    bool judgement(std::string nameOfPrisoner);
    void outcomeAnnouncement(bool convictedToDeath, std::string nameOfPrisoner);
    void announceTheJudge();
private:
    std::string name;
    int convictionRate;
};
#endif /* defined(__Final_Boss__Judicial__) */
