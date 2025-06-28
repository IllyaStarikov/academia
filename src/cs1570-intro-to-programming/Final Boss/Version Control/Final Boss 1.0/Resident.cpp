// Programmer: Illya Starikov                                Date: 04/17/15
// File: Resident.cpp                                        Class: CS1570A
// Purpose: To write the definintions of the Resident Class


#include <fstream>
#include <sstream>

#include <limits>

#include "Resident.h"

#include "Functions.h"
#include "Constants.h"

Resident::Resident() {
    residentName = fileNameParsor();
    isAlive = DEFAULT_ISALIVE;
    isMurderer = DEFAULT_ISMURDERER;
    
    // Forensic Data
    residentForensics.hair = randomArbitrary(HAIR_MIN, HAIR_MAX);
    randomAssignmentDNA();
    
    // Finger Print
    randomAssignmentFingerPrint();
}

void Resident::randomAssignmentDNA() {
    int randomAssignment, memberCounterDNA;
    int rangeFloor, rangeCeiling;
    
    bool assignmentMatch;
    
    for (int arrayCell = 0; arrayCell < LENGTH_OF_DNA; ++arrayCell) {
        randomAssignment = randomArbitrary(1, 100);
        memberCounterDNA = 0;
        
        rangeFloor = 0;
        rangeCeiling = DNA_PERCENTAGES[0] * 100; // reset for ever iteration
        
        do {
            assignmentMatch = ((randomAssignment > rangeFloor) && (randomAssignment <= rangeCeiling));
            
            if (assignmentMatch == true) {
                residentForensics.DNA[arrayCell] = DNA_MEMBERS[memberCounterDNA];
            } else {
                rangeFloor += DNA_PERCENTAGES[memberCounterDNA] * 100;
                rangeCeiling += DNA_PERCENTAGES[memberCounterDNA + 1] * 100;
            }
            
            ++memberCounterDNA;
        } while ((assignmentMatch == false) && (memberCounterDNA < NUMBER_OF_DNA_MEMBERS));
        // The second statement is strictly for precaution.
        // Shouldn't need it but hey, anything could happen
    }
    residentForensics.DNA[LENGTH_OF_DNA] = '\0'; // Ensure last char is terminating char.
    
    return;
}

void Resident::randomAssignmentFingerPrint() {
    // loops, arches, and whirls.
    residentForensics.forensicPrint.loops = randomArbitrary(LOOPS_MIN, LOOPS_MAX);
    residentForensics.forensicPrint.arches = randomArbitrary(ARCHES_MIN, ARCHES_MAX);
    residentForensics.forensicPrint.whirls = randomArbitrary(WHIRLES_MIN, WHIRLES_MAX);

    // The heavy lifting
    // Plot out (one dimensionally) where the stars will be
    char assignmentArray[FINGERPRINT_SIZE];
    bool assignTheStar, starNotAssigned;
    int starsCounter = NUMBER_OF_STARS, loopCounter = 0; // These aren't in async, but they shouldn't be.
    // i have to assign so many stars, while building the structure for where the stars are going to land
    do {
        assignTheStar = (randomArbitrary(1, 100) <= (CHANCE_OF_ASSIGNMENT * 100));
        starNotAssigned = (assignmentArray[loopCounter] != FINGERPRINT_MEMBERS[true]);
        
        if (assignTheStar && starNotAssigned) {
            assignmentArray[loopCounter] = FINGERPRINT_MEMBERS[true];
            --starsCounter;
        } else if (!assignTheStar && starNotAssigned) {
            assignmentArray[loopCounter] = FINGERPRINT_MEMBERS[false];
        }
        
        (loopCounter < FINGERPRINT_SIZE) ? loopCounter++ : loopCounter = 0;
    } while (starsCounter > 0);
    
    // The easy job. Sort of.
    // Walk down the two dimensional array and assign accordingly
    loopCounter = 0;
    for (int i = 0; i < HEIGHT_OF_FINGERPRINT_ARRAY; i++) {
        for (int j = 0; j < LENGTH_OF_FINGERPRINT_ARRAY; j++) {
            residentForensics.forensicPrint.fingerPrintData[i][j] = assignmentArray[i * LENGTH_OF_FINGERPRINT_ARRAY +j];
        }
    }
}

forensicData Resident::dropEvidence() {
    forensicData copyOfForensicsData;
    
    copyOfForensicsData.hair = residentForensics.hair;
    strncpy(copyOfForensicsData.DNA, residentForensics.DNA, LENGTH_OF_DNA);
    
    for (int i = 0; i < HEIGHT_OF_FINGERPRINT_ARRAY; i++) {
        for (int j = 0; j < LENGTH_OF_FINGERPRINT_ARRAY; j++) {
            copyOfForensicsData.forensicPrint.fingerPrintData[i][j] = residentForensics.forensicPrint.fingerPrintData[i][j];
        }
    }
    
    copyOfForensicsData.forensicPrint.loops = residentForensics.forensicPrint.loops;
    copyOfForensicsData.forensicPrint.arches = residentForensics.forensicPrint.arches;
    copyOfForensicsData.forensicPrint.whirls = residentForensics.forensicPrint.whirls;
    
    return copyOfForensicsData;
}

void Resident::killMe() {
    isAlive = false;
    
    return;
}

std::ostream &operator << (std::ostream & os, const Resident & residentToOuput) {
    os << residentToOuput.residentName;
    residentToOuput.isAlive ? os << " is alive" : os << " is not alive";
    residentToOuput.isMurderer ? os << ", is a murderer" : os << ", is not a murderer";
    residentToOuput.residentName == "Clayton Price" ? os << ". Coooool." : os << ".";
    os << std::endl;
    
    return os;
}

std::string Resident::fileNameParsor() {
    // Not the most elegant solution, but it gets the job done
    
    static unsigned filePlaceholder = 1; // static, won't redefine as 1 every call.
    bool reachedEndOfFile = false;
    // Notice, this is a placeholder, not a positions. Does not start at 0;
    std::string nameFromFile;
    
    std::ifstream nameReadIn;
    nameReadIn.open("Names.txt");
    
    if (nameReadIn.is_open()) {
        
        static unsigned fileLength = fileSize(nameReadIn); // one time call, negating the need to consistently call the function.
        // Unsigned because if this returns a negative number. I don't know what will happen but I do not care to find out.
        // Small optimization but when unit testing in the thousands pays off
        
        for (unsigned int i = 0; i < filePlaceholder; i++) {
            if (i < fileLength) {
                getline(nameReadIn, nameFromFile);
            } else {
                nameFromFile = "NULL";
                reachedEndOfFile = true;
            }
        }
        if (reachedEndOfFile == true) {
            errorMessage(3);
        }
        
    } else {
        errorMessage(2);
    }
    
    filePlaceholder++;
    nameReadIn.close();
    return nameFromFile;
}

std::fstream& GotoLine(std::fstream& fin, unsigned int num) {
    fin.seekg(std::ios::beg); // begin at the.. beginning
    
    for(int i=0; i < num - 1; ++i){
        // Ignore the data. If reached the EOF,
        // Throw in a new line character into the stream.
        fin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }
    return fin;
}

unsigned int Resident::fileSize(std::ifstream& fin) {
    unsigned int fileLength = 0; // The unsigned integer to return
    
    do {
        fileLength++; // Incremment fileLength,
        fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // while Ignoring the actual data,
    } while (!fin.eof()); // until it reaches the end of file marker
    
    fin.clear(); // clear the fail bit,
    fin.seekg(0,std::ios::beg); // and return the stream to the beginning
    // Since this stream is passed by reference, have to return stream
    // To original state. If not, you'll begin at the eof / failed bit
    
    return fileLength;
}
