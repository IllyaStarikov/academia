// Programmer: Illya Starikov                Date: 04/17/15
// File: Resident.cpp                    Class: CS1570A
// Purpose: To write the definintions of the Resident Class

#include "Resident.h"

#include "Functions.h"
#include "Constants.h"

Resident::Resident()
{
  m_residentName = fileNameParsor();
  m_residentHairColor = randomArbitrary(HAIR_MIN, HAIR_MAX);
  m_isAlive = DEFAULT_ISALIVE;
  m_isMurderer = DEFAULT_ISMURDERER;
}

void Resident::changeHairColor(const int changingHairColor)
{
  m_residentHairColor = changingHairColor;

  return;
}

void Resident::killMe()
{
  m_isAlive = false;

  return;
}

std::ostream &operator << (std::ostream & os, const Resident & residentToOuput)
{

  os << residentToOuput.m_residentName;
  residentToOuput.m_isAlive ? os << " is alive" : os << " is not alive";
  residentToOuput.m_isMurderer ? os << ", is a murderer" : os
    << ", is not a murderer";
  os << " and has hair color " << residentToOuput.m_residentHairColor;
  residentToOuput.m_residentName == "Clayton Price" ? os
    << ". Coooool." : os << ".";
  os << endl;

  return os;
}