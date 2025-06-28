// Programmer: Illya Starikov                                Date: 04/17/15
// File: Resident.cpp                                        Class: CS1570A
// Purpose: To write the prototypes of the Resident Class


#ifndef Final_Boss__Resident
#define Final_Boss__Resident

#include "Forensic Data.h"

#include <iostream>

class Resident {
public:
    Resident();
    forensicData dropEvidence();
    void killMe();
    
    friend std::ostream &operator << (std::ostream & os, const Resident & residentToOuput);
    
    // Maintenance Functions
    void randomAssignmentDNA();
    void randomAssignmentFingerPrint();
    std::string fileNameParsor();
    unsigned int fileSize(std::ifstream& fin);
    
    // Accessors
    std::string getResidentName()const { return residentName; }
    char getResidentDNACharacter(const int positionInArray)const { return residentForensics.DNA[positionInArray]; }
    char getResidentFingerPrintCharacter(const int lengthCell, const int heightCell)const { return residentForensics.forensicPrint.fingerPrintData[lengthCell][heightCell]; };
    int getResidentFingerPrintLoops()const { return residentForensics.forensicPrint.loops; };
    int getResidentFingerPrintArches()const { return residentForensics.forensicPrint.arches; };
    int getResidentFingerPrintWhirles()const { return residentForensics.forensicPrint.whirls; };
    int getResidentHair()const { return residentForensics.hair; };
    int getResidentIsAlive()const { return isAlive; };
    
    // Mutators
    void setResidentIsMurderer(bool isMurderToChange) { isMurderer = isMurderToChange; return; }
    
private:
    std::string residentName;
    bool isAlive;
    bool isMurderer;

    forensicData residentForensics;
};


#endif /* defined(Final_Boss__Resident) */
