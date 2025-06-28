// Programmers: Illya Starikov and Alex Androff        Date: 04/17/15
// File: CrimeRoom.cpp                                 Class: CS1570A
// Purpose: Define Crimeroom to match associated protyped functions.

#include <cstring>

#include "CrimeRoom.h"
#include "Resident.h"
#include "Functions.h"
#include "Forensic Data.h"
#include "Constants.h"

CrimeRoom::CrimeRoom()
{
  m_murderCommitted = false;
  m_deadResident = "";

}

void CrimeRoom::meeting(Resident residentOne, Resident residentTwo)
{
  m_murderCommitted = murder();

  if (m_murderCommitted == true)
  {
    int victimResident = randomArbitrary(1, 2);

    if (victimResident == 1)
    {
      if (residentOne.getResidentIsPrice())
      {
        triedToKillTeacher(residentOne, residentTwo);
      }
      else
      {
        m_deadResident = residentOne.getResidentName();
        residentOne.killMe();
        residentTwo.setResidentIsMurderer(true);
        m_roomForensics = residentTwo.dropEvidence();
      }
    }
    else if (victimResident == 2)
    {
      if (residentTwo.getResidentIsPrice())
      {
        triedToKillTeacher(residentTwo, residentOne);
      }
      else
      {
        m_deadResident = residentTwo.getResidentName();
        residentTwo.killMe();
        residentOne.setResidentIsMurderer(true);
        m_roomForensics = residentOne.dropEvidence();
      }
    }
  }

  return;
}

void CrimeRoom::triedToKillTeacher(Resident teacher,
                   Resident attemptedMurderer)
{
  m_deadResident = attemptedMurderer.getResidentName();
  attemptedMurderer.killMe();
  teacher.setResidentIsMurderer(true);
  m_roomForensics = teacher.dropEvidence();
}

bool CrimeRoom::murder()
{
  int murderChance = randomArbitrary(1, 100);
  return (static_cast<float>(murderChance) <= (CHANCE_OF_MURDER * 100));
}

bool CrimeRoom::checkRoom()const
{
  return m_murderCommitted;
}

forensicData CrimeRoom::getEvidence()
{
  forensicData copyOfForensics;

  copyOfForensics.m_hair = m_roomForensics.m_hair;
  strncpy(copyOfForensics.m_DNA, m_roomForensics.m_DNA, LENGTH_OF_DNA);

  for (int i = 0; i < HEIGHT_OF_FINGERPRINT_ARRAY; i++)
  {
    for (int j = 0; j < LENGTH_OF_FINGERPRINT_ARRAY; j++)
    {
      copyOfForensics.m_forensicPrint.fingerPrintData[i][j] =
      m_roomForensics.m_forensicPrint.fingerPrintData[i][j];
    }
  }

  copyOfForensics.m_forensicPrint.loops =
  m_roomForensics.m_forensicPrint.loops;
  copyOfForensics.m_forensicPrint.arches =
  m_roomForensics.m_forensicPrint.arches;
  copyOfForensics.m_forensicPrint.whirls =
  m_roomForensics.m_forensicPrint.whirls;

  return copyOfForensics;
}


