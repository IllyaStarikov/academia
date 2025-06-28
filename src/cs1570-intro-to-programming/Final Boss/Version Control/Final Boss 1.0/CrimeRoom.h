// Programmer: Illya Starikov                                Date: 04/17/15
// File: Functions.h                                          Class: CS1570A
// Purpose: Prototype the resident class.

#ifndef Final_Boss__CrimeRoom
#define Final_Boss__CrimeRoom

#include <iostream>

#include "Resident.h"

#include "Forensic Data.h"

class CrimeRoom {
public:
    CrimeRoom();
    void meeting(Resident residentOne, Resident residentTwo);
    bool murder();
    bool checkRoom();
    forensicData getEvidence();
    
    // Mutators
//    void hairAddition(const int amountToAdd); // To corrupt the hair
    
private:
    bool murderCommitted;
    std::string deadResident;
    forensicData roomForensics;

};

#endif /* defined(Final_Boss__CrimeRoom) */
