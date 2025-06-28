// Programmers: Illya Starikov and Alex Androff        Date: 04/17/15
// File: Resident.cpp                                  Class: CS1570A
// Purpose: To write the definitions of the Resident Class




#include <fstream>
#include <sstream>
#include <limits>
#include <cstring>

#include "Resident.h"
#include "Functions.h"
#include "Constants.h"

unsigned Resident::m_filePlaceholder = 1;

Resident::Resident()
{
  residentName = fileNameParsor();
  m_isPrice = residentName == "Clayton Price";
  weapon = getRandomWeapon();
  m_isAlive = DEFAULT_ISALIVE;
  m_isMurderer = DEFAULT_ISMURDERER;

  // Forensic Data
  m_residentForensics.m_hair = randomArbitrary(HAIR_MIN, HAIR_MAX);
  randomAssignmentDNA();

  // Finger Print
  randomAssignmentFingerPrint();
}

void Resident::randomAssignmentDNA()
{
  int randomAssignment, memberCounterDNA;
  int rangeFloor, rangeCeiling;

  bool assignmentMatch;

  for (int arrayCell = 0; arrayCell < LENGTH_OF_DNA; ++arrayCell)
  {
    randomAssignment = randomArbitrary(1, 100);
    memberCounterDNA = 0;

    rangeFloor = 0;
    rangeCeiling = DNA_PERCENTAGES[0] * 100; // reset for ever iteration

    do
    {
      assignmentMatch = ((randomAssignment > rangeFloor) &&
                 (randomAssignment <= rangeCeiling));

      if (assignmentMatch == true)
      {
        m_residentForensics.m_DNA[arrayCell] =
        DNA_MEMBERS[memberCounterDNA];
      }
      else
      {
        rangeFloor += DNA_PERCENTAGES[memberCounterDNA] * 100;
        rangeCeiling += DNA_PERCENTAGES[memberCounterDNA + 1] * 100;
      }

      ++memberCounterDNA;
    } while ((assignmentMatch == false) &&
         (memberCounterDNA < NUMBER_OF_DNA_MEMBERS));
    // The second statement is strictly for precaution.
    // Shouldn't need it but hey, anything could happen
  }
  m_residentForensics.m_DNA[LENGTH_OF_DNA] = NULL_TERMINATING_CHAR;
  // Ensure last char is terminating char.

  return;
}

void Resident::randomAssignmentFingerPrint()
{
  // loops, arches, and whirls.
  m_residentForensics.m_forensicPrint.loops = randomArbitrary(LOOPS_MIN,
                                LOOPS_MAX);
  m_residentForensics.m_forensicPrint.arches = randomArbitrary(ARCHES_MIN,
                                 ARCHES_MAX);
  m_residentForensics.m_forensicPrint.whirls = randomArbitrary(WHIRLES_MIN,
                                 WHIRLES_MAX);

  // The heavy lifting
  // Plot out (one dimensionally) where the stars will be
  char assignmentArray[FINGERPRINT_SIZE];
  bool assignTheStar, starNotAssigned;
  int starsCounter = NUMBER_OF_STARS, loopCounter = 0;
  // These aren't in async, but they shouldn't be.
  // i have to assign so many stars, while building the structure
  // for where the stars are going to land
  do
  {
    assignTheStar = (randomArbitrary(1, 100) <=
             (CHANCE_OF_ASSIGNMENT * 100));
    starNotAssigned = (assignmentArray[loopCounter] !=
               FINGERPRINT_MEMBERS[true]);

    if (assignTheStar && starNotAssigned)
    {
      assignmentArray[loopCounter] = FINGERPRINT_MEMBERS[true];
      --starsCounter;
    }
    else if (!assignTheStar && starNotAssigned)
    {
      assignmentArray[loopCounter] = FINGERPRINT_MEMBERS[false];
    }

    (loopCounter < FINGERPRINT_SIZE) ? loopCounter++ : loopCounter = 0;
  } while (starsCounter > 0);

  // The easy job. Sort of.
  // Walk down the two dimensional array and assign accordingly
  loopCounter = 0;
  for (int i = 0; i < HEIGHT_OF_FINGERPRINT_ARRAY; ++i)
  {
    for (int j = 0; j < LENGTH_OF_FINGERPRINT_ARRAY; ++j)
    {
      m_residentForensics.m_forensicPrint.fingerPrintData[i][j]
      = assignmentArray[i * LENGTH_OF_FINGERPRINT_ARRAY +j];
    }
    m_residentForensics.m_forensicPrint.fingerPrintData[i]
    [HEIGHT_OF_FINGERPRINT_ARRAY] = NULL_TERMINATING_CHAR;
  }
}

forensicData Resident::dropEvidence()
{
  forensicData copyOfForensicsData;

  copyOfForensicsData.m_hair = m_residentForensics.m_hair;
  strncpy(copyOfForensicsData.m_DNA, m_residentForensics.m_DNA,
      LENGTH_OF_DNA);
  copyOfForensicsData.m_DNA[LENGTH_OF_DNA] = NULL_TERMINATING_CHAR;

  for (int i = 0; i < HEIGHT_OF_FINGERPRINT_ARRAY; ++i)
  {
    for (int j = 0; j < LENGTH_OF_FINGERPRINT_ARRAY; ++j)
    {
      copyOfForensicsData.m_forensicPrint.fingerPrintData[i][j] =
      m_residentForensics.m_forensicPrint.fingerPrintData[i][j];
    }
    copyOfForensicsData.m_forensicPrint.fingerPrintData[i]
    [HEIGHT_OF_FINGERPRINT_ARRAY] = NULL_TERMINATING_CHAR;
  }

  copyOfForensicsData.m_forensicPrint.loops
  = m_residentForensics.m_forensicPrint.loops;
  copyOfForensicsData.m_forensicPrint.arches
  = m_residentForensics.m_forensicPrint.arches;
  copyOfForensicsData.m_forensicPrint.whirls
  = m_residentForensics.m_forensicPrint.whirls;

  return copyOfForensicsData;
}

void Resident::killMe()
{
  m_isAlive = false;

  return;
}

std::ostream & operator << (std::ostream & os,
              const Resident & residentToOuput)
{
  os << residentToOuput.residentName;
  residentToOuput.m_isAlive ? os << " is alive" : os << " is not alive";
  residentToOuput.m_isMurderer ? os << ", is a murderer" :
  os << ", is not a murderer";
  residentToOuput.residentName == "Clayton Price" ?
  os << ". Coooool." : os << ".";
  os << std::endl;

  return os;
}

std::string Resident::fileNameParsor()const
{
  std::string nameFromFile;

  std::ifstream nameReadIn;
  nameReadIn.open("Names.dat");

  if (nameReadIn.is_open())
  {
    gotoLine(nameReadIn, Resident::m_filePlaceholder);
    getline(nameReadIn, nameFromFile);
    Resident::m_filePlaceholder++;
  }
  else
  {
    errorMessage(2);
  }

  nameReadIn.close();
  return nameFromFile;
}

std::string Resident::getRandomWeapon()const
{
  std::string randomWeapon;

  std::ifstream weapon;
  weapon.open("Weapons.dat");

  if (weapon.is_open())
  {
    static unsigned fileLength = fileSize(weapon);
    gotoLine(weapon, randomArbitrary(0, fileLength));
    getline(weapon, randomWeapon);
  }
  else
  {
    errorMessage(2);
  }

  weapon.close();

  return m_isPrice ? "his Hammer of GNU and Knowledge of C++" : randomWeapon;
}

std::ifstream & Resident::gotoLine(std::ifstream & fin, int numberToJumpTo)
const
{
  fin.clear();
  fin.seekg(0,std::ios::beg); // begin at the.. beginning

  for (int i = 0; i < numberToJumpTo - 1; ++i)
  {
    // Ignore the data. If reached the EOF,
    // Throw in a new line character into the stream.
    fin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
  }

  return fin;
}

unsigned int Resident::fileSize(std::ifstream & fin)const
{
  unsigned int fileLength = 0; // The unsigned integer to return

  while (!fin.eof())
  {
    fileLength++; // Incremment fileLength,
    fin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    // while Ignoring the actual data,
  } // until it reaches the end of file marker

  fin.clear(); // clear the fail bit,
  fin.seekg(0,std::ios::beg); // and return the stream to the beginning
  // Since this stream is passed by reference, have to return stream
  // To original state. If not, you'll begin at the eof / failed bit

  return fileLength;
}