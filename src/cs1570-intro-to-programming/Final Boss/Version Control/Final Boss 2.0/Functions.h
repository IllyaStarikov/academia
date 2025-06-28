// Programmers: Illya Starikov and Alex Androff              Date: 04/17/15
// File: Functions.h                                         Class: CS1570A
// Purpose: Prototype general functions.

#ifndef Final_Boss__Functions
#define Final_Boss__Functions

#include "Resident.h"
#include "Agent.h"
#include "CrimeRoom.h"

void setTheScene();

void meetingResults(const CrimeRoom roomOfCrime, const std::string meetingTime, const bool murderOccured, Resident residentOne, Resident residentTwo);
void takeOutVictim(Resident mainResidents[], CrimeRoom roomOfCrime, int & SizeOfArray, int locationOfFirstResident, int locationOfSecondResident);
void investigation(csiAgent agentForInvestigation, Resident residentsToSearch[], int & sizeOfResidents, CrimeRoom roomToSearch);
void judgementDay(Resident residentArray[], int & sizeOfArray, int locationOfJudgingResident);

void removeResidentFromArray(Resident residentArray[], int & sizeOfArray, const int residentToRemove);
void closingStatement(const Resident residentZero, const bool someoneDidWin);
void timeManagement(int & timeOfDay, int & theDay, bool isMurderOccuring);

void twoRandomNumbers(int & numberOne, int & numberTwo, const int floor, const int ceiling);
int randomArbitrary(const int floor, const int ceiling);
int round(const float numberToRound);
int absolute(const int numberToAbsolute);
void errorMessage(const int errorCode);


#endif /* defined(Final_Boss__Functions) */