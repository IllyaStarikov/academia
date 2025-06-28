// Programmer: Illya Starikov                                Date: 04/17/15
// File: Resident.cpp                                        Class: CS1570A
// Purpose: To write the driver of the program (main), and to do
// unit testing.

/*
 To clear any confusion, the directory is named Final Boss.
 
 So for #ifndef gaurds, the prefix is my directory.
 */


#include <iostream>

// Random Function Libraries
#include <stdio.h>      // NULL
#include <stdlib.h>     // srand, rand
#include <time.h>       // time

#include "Resident.h"
#include "CrimeRoom.h"
#include "Judicial.h"
#include "CSI Agent.h"

#include "Functions.h"

using namespace std;

int main() {
    srand(static_cast<unsigned>(time(NULL)));
    
    CrimeRoom pricesOffice;
    Resident pricesStudents[NUMBER_OF_RESIDENTS], residentThatMeet[RESIDENTS_PER_MEETING];
    Judicial pricesGrader(DEFAULT_JUDGE);
    
    int studentsRemaining = NUMBER_OF_RESIDENTS;
    int residentOne, residentTwo;
    int timeCounter = 0;
    
    bool murderOccurred;
    
    do {
        do {
            residentOne = randomArbitrary(0, studentsRemaining - 1);
            residentTwo = randomArbitrary(0, studentsRemaining - 1);
        } while (residentOne == residentTwo);
        
        residentThatMeet[0] = pricesStudents[residentOne];
        residentThatMeet[1] = pricesStudents[residentTwo];
        
        pricesOffice.meeting(residentThatMeet[0], residentThatMeet[1]);
        murderOccurred = pricesOffice.checkRoom();
        meetingResults(MEETING_TIMES[timeCounter], murderOccurred, residentThatMeet[0], residentThatMeet[1]);

        if (murderOccurred) {
            
            takeOutVictim(pricesStudents, studentsRemaining, residentOne, residentTwo);
            csiAgent mainAgent;
            investigation(mainAgent, pricesStudents, studentsRemaining, pricesOffice);
            
            timeCounter = 0;
        }
        (timeCounter > MEETINGS_PER_DAY - 2) ? timeCounter = 0 : timeCounter++;
        
    } while (studentsRemaining > 1);
    
    if (studentsRemaining == 1) {
        // Declare Winner
        cout << pricesStudents[0].getResidentName() << " is the winner!";
    }
    return 0;
}
