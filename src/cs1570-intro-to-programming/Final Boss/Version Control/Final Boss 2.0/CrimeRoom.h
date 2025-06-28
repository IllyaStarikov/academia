// Programmers: Illya Starikov and Alex Androff               Date: 04/17/15
// File: CrimeRoom.h                                          Class: CS1570A
// Purpose: Define Crimeroom to match associated protyped functions.

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
    bool checkRoom();
    forensicData getEvidence();
    
    // Accessors
    char getRoomDNACharacter(const int positionInArray)const { return roomForensics.DNA[positionInArray]; }
    std::string getDeadResident()const { return deadResident; }
private:
    bool murderCommitted;
    std::string deadResident;
    forensicData roomForensics;

};

#endif /* defined(Final_Boss__CrimeRoom) */
