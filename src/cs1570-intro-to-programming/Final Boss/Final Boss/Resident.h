// Programmers: Illya Starikov and Alex Androff        Date: 04/17/15
// File: Resident.h                                    Class: CS1570A
// Purpose: To write the definitions of the Resident Class

/*
--------------------Resident--------------------
Description:   Default constructor.
Pre-Condition:   Set the defaults, get the names from a file, and the weapons.
Post-Condition:  A resident object is created.
*/

/*
--------------------dropEvidence--------------------
Description:   After a crime has occurred, all of the residents are clumsy,
so they drop all of their information.
Pre-Condition:   None.
Post-Condition:  The evidence is dropped, copied over, and ready to be picked
up and searched.
*/

/*
--------------------killMe--------------------
Description:   Kills the resident.
Pre-Condition:   None.
Post-Condition:  The boolean to determine if the resident is alive is set
to false.
*/

/*
--------------------Extraction Operator (<<)--------------------
Description:   Output the Resident in a nice, friendly manner.
Pre-Condition:   A resident must be on the right hand side.
Post-Condition:  A resident is outputted into the stream in a nice, friendly
manner.
*/

/*
--------------------randomAssignmentDNA--------------------
Description:   Randomly assign the values to the DNA.
Pre-Condition:   A resident object must in the making.
Post-Condition:  DNA of a constant size is created.
*/

/*
--------------------randomAssignmentFingerPrint--------------------
Description:  The fingerprint is randomly assigned.
Pre-Condition:  A resident object must be in the making.
Post-Condition: The fingerprint of the object is randomly assigned certain
values.
*/

/*
--------------------fileNameParsor--------------------
Description:   A string is returned that is parsed from a file.
Pre-Condition:   None.
Post-Condition:  A string is returned, representing a name.
*/

/*
--------------------getRandomWeapon--------------------
Description:   Gets a random weapon from a text file.
Pre-Condition:   None.
Post-Condition:  A string is returned of a random name.
*/

/*
--------------------gotoLine--------------------
Description:   Goes to a particular line in a stream.
Pre-Condition:   A valid ifstream must be passed, and the number to jump to
Post-Condition:  The stream is returned, modified to be at a spot specified.
*/

/*
--------------------fileSize--------------------
Description:  Determine the files size, based on a passed stream.
Pre-Condition:  An fstream must be passed.
Post-Condition: The file size is determined.
*/

/*
--------------------Accessors--------------------
Description:   Gives access to a particular member data.
Pre-Condition:   None.
Post-Condition:  Respective member data is returned
*/

/*
--------------------Mutators--------------------
Description:   Mutate the data, change it to how specified.
Pre-Condition:   The changing data must be passed.
Post-Condition:  The member data is changed.
*/

#ifndef Final_Boss__Resident
#define Final_Boss__Resident

#include "Forensic Data.h"

#include <iostream>

class Resident
{
public:
  Resident();
  forensicData dropEvidence();
  void killMe();

  friend std::ostream &operator << (std::ostream & os,
                    const Resident & residentToOuput);

  // Maintenance Functions
  void randomAssignmentDNA();
  void randomAssignmentFingerPrint();
  std::string fileNameParsor()const;
  std::string getRandomWeapon()const;
  std::ifstream &gotoLine(std::ifstream & fin, const int numberToJumpTo)
  const;

  unsigned int fileSize(std::ifstream& fin)const;

  // Accessors
  std::string getResidentName()const { return residentName; }
  std::string getWeapon()const { return weapon; }
  char getResidentDNACharacter(const int positionInArray)const {
    return m_residentForensics.m_DNA[positionInArray]; }
  char getResidentFingerPrintCharacter(
                     const int lengthCell,
                     const int heightCell)const {
    return m_residentForensics.m_forensicPrint.fingerPrintData
    [lengthCell][heightCell]; }
  int getResidentFingerPrintLoops()const {
    return m_residentForensics.m_forensicPrint.loops; }
  int getResidentFingerPrintArches()const {
    return m_residentForensics.m_forensicPrint.arches; }
  int getResidentFingerPrintWhirles()const {
    return m_residentForensics.m_forensicPrint.whirls; }
  int getResidentHair()const {
    return m_residentForensics.m_hair; }
  int getResidentIsAlive()const {
    return m_isAlive; }
  bool getResidentIsPrice()const {
    return m_isPrice; }
  // Mutators
  void setResidentIsMurderer(bool isMurderToChange) {
    m_isMurderer = isMurderToChange; return; }

private:
  std::string residentName;
  std::string weapon;
  bool m_isPrice;
  bool m_isAlive;
  bool m_isMurderer;

  forensicData m_residentForensics;

  static unsigned m_filePlaceholder;
};

#endif /* defined(Final_Boss__Resident) */
