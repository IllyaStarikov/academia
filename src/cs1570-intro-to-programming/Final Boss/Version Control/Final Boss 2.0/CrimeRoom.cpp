// Programmers: Illya Starikov and Alex Androff              Date: 04/17/15
// File: CrimeRoom.cpp                                       Class: CS1570A
// Purpose: Define Crimeroom to match associated protyped functions.

#include <cstring>

#include "CrimeRoom.h"
#include "Resident.h"
#include "Functions.h"
#include "Forensic Data.h"
#include "Constants.h"

CrimeRoom::CrimeRoom() {
    murderCommitted = false;
    deadResident = "";
    
}

void CrimeRoom::meeting(Resident residentOne, Resident residentTwo) {
    murderCommitted = murder();
    
    if (murderCommitted == true) {
        int victimResident = randomArbitrary(1, 2);
        
        if (victimResident == 1) {
            if (residentOne.getResidentIsPrice()) {
                triedToKillTeacher(residentOne, residentTwo);
            } else {
                deadResident = residentOne.getResidentName();
                residentOne.killMe();
                residentTwo.setResidentIsMurderer(true);
                roomForensics = residentTwo.dropEvidence();
            }
        } else if (victimResident == 2) {
            if (residentTwo.getResidentIsPrice()) {
                triedToKillTeacher(residentTwo, residentOne);
            } else {
                deadResident = residentTwo.getResidentName();
                residentTwo.killMe();
                residentOne.setResidentIsMurderer(true);
                roomForensics = residentOne.dropEvidence();
            }
        }
    }
    
    return;
}

void CrimeRoom::triedToKillTeacher(Resident teacher, Resident attemptedMurderer) {
    deadResident = attemptedMurderer.getResidentName();
    attemptedMurderer.killMe();
    teacher.setResidentIsMurderer(true);
    roomForensics = teacher.dropEvidence();
}

bool CrimeRoom::murder() {
    int murderChance = randomArbitrary(1, 100);
    return (static_cast<float>(murderChance) <= (CHANCE_OF_MURDER * 100));
}

bool CrimeRoom::checkRoom() {
    return murderCommitted;
}

forensicData CrimeRoom::getEvidence() {
    forensicData copyOfForensics;
    
    copyOfForensics.hair = roomForensics.hair;
    strncpy(copyOfForensics.DNA, roomForensics.DNA, LENGTH_OF_DNA);
    
    for (int i = 0; i < HEIGHT_OF_FINGERPRINT_ARRAY; i++) {
        for (int j = 0; j < LENGTH_OF_FINGERPRINT_ARRAY; j++) {
            copyOfForensics.forensicPrint.fingerPrintData[i][j] = roomForensics.forensicPrint.fingerPrintData[i][j];
        }
    }
    
    copyOfForensics.forensicPrint.loops = roomForensics.forensicPrint.loops;
    copyOfForensics.forensicPrint.arches = roomForensics.forensicPrint.arches;
    copyOfForensics.forensicPrint.whirls = roomForensics.forensicPrint.whirls;
    
    return copyOfForensics;
}


