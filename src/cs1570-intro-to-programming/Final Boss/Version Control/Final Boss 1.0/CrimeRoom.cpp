// Programmer: Illya Starikov                                Date: 04/17/15
// File: Functions.h                                         Class: CS1570A
// Purpose: Define Crimeroom to match associated protyped functions.

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

        // In the case of more than two residents in a meeting, switch to switch case
        if (victimResident == 1) {
            deadResident = residentOne.getResidentName();
            residentOne.killMe();
            residentTwo.setResidentIsMurderer(true);
            roomForensics = residentTwo.dropEvidence();


        } else if (victimResident == 2) {
            deadResident = residentTwo.getResidentName();
            residentTwo.killMe();
            residentOne.setResidentIsMurderer(true);
            roomForensics = residentOne.dropEvidence();
        }
    }
    
    return;
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


