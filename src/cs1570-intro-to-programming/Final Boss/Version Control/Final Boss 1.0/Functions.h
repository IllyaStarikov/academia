// Programmer: Illya Starikov                                Date: 04/17/15
// File: Functions.h                                         Class: CS1570A
// Purpose: Prototype general functions.

#ifndef Final_Boss__Functions
#define Final_Boss__Functions

#include "Resident.h"
#include "CSI Agent.h"
#include "CrimeRoom.h"

void meetingResults(const std::string meetingTime, const bool murderOccured, Resident residentOne, Resident residentTwo);
void takeOutVictim(Resident mainResidents[], int & SizeOfArray, int locationOfFirstResident, int locationOfSecondResident);
void investigation(csiAgent agentForInvestigation, Resident residentsToSearch[], int & sizeOfResidents, CrimeRoom roomToSearch);
void removeResidentFromArray(Resident residentArray[], const int sizeOfArray, const int residentToRemove);

int randomArbitrary(const int floor, const int ceiling);
void errorMessage(const int errorCode);


#endif /* defined(Final_Boss__Functions) */