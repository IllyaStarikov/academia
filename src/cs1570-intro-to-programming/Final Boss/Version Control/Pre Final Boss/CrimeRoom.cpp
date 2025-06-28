// Programmer: Illya Starikov                Date: 04/17/15
// File: Functions.h                     Class: CS1570A
// Purpose: Define Crimeroom to match associated protyped functions.

#include "CrimeRoom.h"
#include "Resident.h"

#include "Functions.h"
#include "Constants.h"

CrimeRoom::CrimeRoom()
{
  m_murderCommitted = false;
  m_deadResident = "";
  m_hair = DEFAULT_HAIR;
}

void CrimeRoom::meeting(Resident residentOne, Resident residentTwo)
{
  m_murderCommitted = murder();
  if (m_murderCommitted == true)
  {
    int victimResident = randomArbitrary(1, 2);

    // In the case of more than two residents in a meeting,
    // switch to switch case
    if (victimResident == 1)
    {
      m_deadResident = residentOne.getResidentName();
      residentOne.killMe();
      residentTwo.setResidentIsMurderer(true);
      m_hair = residentTwo.getHair();

    }
    else if (victimResident == 2)
    {
      m_deadResident = residentTwo.getResidentName();
      residentOne.killMe();
      residentTwo.setResidentIsMurderer(true);
      m_hair = residentOne.getHair();
    }
  }

  return;
}

bool CrimeRoom::murder()
{
  int murderChance = randomArbitrary(1, 100);
  return (murderChance <= CHANCE_OF_MURDER) ? true : false;
}

void CrimeRoom::checkRoom()
{
  if (m_murderCommitted == true)
  {
    cout << m_deadResident << " has been murdered!" << endl;
  }

  return;
}