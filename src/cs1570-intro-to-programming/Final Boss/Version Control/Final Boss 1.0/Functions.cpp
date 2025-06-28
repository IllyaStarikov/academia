// Programmer: Illya Starikov                                Date: 04/17/15
// File: Functions.h                                          Class: CS1570A
// Purpose: Define general functions.

#include <iostream>
#include <fstream>

#include "Functions.h"

/*--------------------srand/rand C++ 98 Header--------------------*/
#include <stdio.h>                  // NULL
#include <stdlib.h>                 // srand, rand
#include <time.h>                   // time

using namespace std;


void meetingResults(const std::string meetingTime, const bool murderOccured, Resident residentOne, Resident residentTwo) {
    cout << meetingTime << "\t|\t";
    if (murderOccured) {
        if(residentOne.getResidentIsAlive()) {
            cout << residentTwo.getResidentName() << " is dead!";
            residentTwo.getResidentName() == "Clayton Price" ? cout << " He has been murdered and Illya Starikov fails the CS1570 Final Project!" : cout << " He/She has been murdered!";
        } else {
            cout << residentOne.getResidentName() << " is dead!";
            residentTwo.getResidentName() == "Clayton Price" ? cout << " He has been murdered and Illya Starikov fails the CS1570 Final Project!" : cout << " He/She has been murdered!";
        }
        
        cout << endl;
    }
    else if (!murderOccured) {
        cout << residentOne.getResidentName() << " and " << residentTwo.getResidentName() << " meet." << endl;
        
    }
    
    
    return;
}

void takeOutVictim(Resident mainResidents[], int & SizeOfArray, int locationOfFirstResident, int locationOfSecondResident) {
    if (!mainResidents[locationOfFirstResident].getResidentIsAlive()) {
        removeResidentFromArray(mainResidents, SizeOfArray, locationOfFirstResident);
    } else {
        removeResidentFromArray(mainResidents, SizeOfArray, locationOfSecondResident);
    }
    SizeOfArray--;

    return;
}

void investigation(csiAgent agentForInvestigation, Resident residentsToSearch[], int & sizeOfResidents, CrimeRoom roomToSearch) {
    bool matchFound;
    int residentPlace, roomVisits = 0;
    
    do {
        agentForInvestigation.gatherInformation(roomToSearch);
        residentPlace = - 1; // Immediate incremint.
       
        do {
            ++residentPlace;
            matchFound = agentForInvestigation.perpSearch(residentsToSearch[residentPlace]);
        } while (!matchFound && residentPlace < sizeOfResidents);
        
        ++roomVisits;
    } while (!matchFound && roomVisits < MAX_NUMBER_OF_ROOM_SEARCHES);
    
    matchFound ?
    cout << "Match Found! After " << roomVisits << " It was " << residentsToSearch[residentPlace].getResidentName() << endl :
    cout << "No match found:(" << endl << "Better luck next time..." << endl;
    
    if (matchFound) {
        removeResidentFromArray(residentsToSearch, sizeOfResidents, residentPlace);
        --sizeOfResidents;
    }
    
    return;
}

void removeResidentFromArray(Resident residentArray[], const int sizeOfArray, const int residentToRemove) {
    // I know I can just assign on the spot,
    // but I like being.. organized?
    Resident temp = residentArray[residentToRemove];
    residentArray[residentToRemove] = residentArray[sizeOfArray - 1];
    residentArray[sizeOfArray - 1] = temp;

    return;
}

int randomArbitrary(const int floor, const int ceiling) {
    return (floor + rand() % (ceiling - floor + 1));
}

void errorMessage(const int errorCode) {
    // Error Codes
    // 1. Miscellaneous Error
    // 2. Error fStream
    // 3. End of file reached.
    switch (errorCode) {
        case 1:
            cout << endl << "ERROR. Please Try Again." << endl << endl;
            break;
            
        case 2:
            cout << endl << "ERROR. Unable To Open File." << endl << endl;
            break;
            
        case 3:
            cout << endl << "ERROR. End of File reached." << endl << endl;
            break;
    }
    
    return;
}