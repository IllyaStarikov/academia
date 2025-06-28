// Programmers: Illya Starikov and Alex Androff           Date: 04/17/15
// File: Agent.h                                       Class: CS1570A
// Purpose: To write the definitions of the Agent Class

#ifndef Final_Boss__CSI_Agent
#define Final_Boss__CSI_Agent

#include <iostream>

#include "Forensic Data.h"
#include "CrimeRoom.h"
#include "Resident.h"


class csiAgent {
public:
    csiAgent();
    void visitCrimeScene(CrimeRoom roomToInvestigate);
    void gatherInformation(CrimeRoom roomToGatherInformation);
    bool perpSearch(Resident residentToSearch);
    
    // Maintenance Functions
    int dataCorruptionAddition(const int data, const int dataAddition, const int floor, const int ceiling)const;
    bool withinX(const int originalNumber, const int comparingNumber, const int marginOfError)const;
private:
    std::string name;
    forensicData theEvidence;
};

#endif /* defined(Final_Boss__CSI_Agent) */
