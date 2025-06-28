// Programmers: Illya Starikov and Alex Androff              Date: 04/17/15
// File: Resident.h                                       Class: CS1570A
// Purpose: To write the definitions of the Resident Class


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
    std::string getRandomWeapon();
    std::ifstream &gotoLine(std::ifstream & fin, int numberToJumpTo);
    
    void incrementPlaceholder();

    unsigned int fileSize(std::ifstream& fin);
    
    // Accessors
    std::string getResidentName()const { return residentName; }
    std::string getWeapon()const { return weapon; }
    char getResidentDNACharacter(const int positionInArray)const { return residentForensics.DNA[positionInArray]; }
    char getResidentFingerPrintCharacter(const int lengthCell, const int heightCell)const { return residentForensics.forensicPrint.fingerPrintData[lengthCell][heightCell]; }
    int getResidentFingerPrintLoops()const { return residentForensics.forensicPrint.loops; }
    int getResidentFingerPrintArches()const { return residentForensics.forensicPrint.arches; }
    int getResidentFingerPrintWhirles()const { return residentForensics.forensicPrint.whirls; }
    int getResidentHair()const { return residentForensics.hair; }
    int getResidentIsAlive()const { return isAlive; }
    bool getResidentIsPrice()const { return isPrice; }
    // Mutators
    void setResidentIsMurderer(bool isMurderToChange) { isMurderer = isMurderToChange; return; }
    
private:
    std::string residentName;
    std::string weapon;
    bool isPrice;
    bool isAlive;
    bool isMurderer;

    forensicData residentForensics;
    
    static unsigned filePlaceholder;
};

#endif /* defined(Final_Boss__Resident) */
