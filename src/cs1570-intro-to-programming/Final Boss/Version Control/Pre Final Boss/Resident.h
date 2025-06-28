// Programmer: Illya Starikov                Date: 04/17/15
// File: Resident.cpp                    Class: CS1570A
// Purpose: To write the prototypes of the Resident Class


#ifndef Final_Boss__Resident
#define Final_Boss__Resident

/*
Resident Constructor
Description:    Constructs the default resides class.
Pre-Condition:  Resident class must be initilized.
Post-Condition: Sets the values for the class.
*/

/*
changeHairColor
Description:    Changes the calling object's hair color.
Pre-Condition:  Must be passed a value to represent the hair color.
Post-Condition: The calling object's hair color is changed to specified value.
*/

/*
killMe
Description:    Changes the calling object's member variable that represents
the liviliness to false.
Pre-Condition:  The resident class must be intitized.
Post-Condition: The calling object's isAlive variable is set to false.
*/

/*
operator overloaded <<
Description:    Friend of the class << makes an appearance by outputting the
the class member variables in a nice fashion.
Pre-Condition:  None.
Post-Condition: Outputting of the class member variables, depeding on the
type of stream you are using.
*/

/*
getResidentName
Description:    An accessor to return the resident name.
Pre-Condition:  None.
Post-Condition: Returns specified name of the resident.
*/

/*
getHair
Description:    Get the Resident hair integer.
Pre-Condition:  None.
Post-Condition: Returns the hair of the calling object's.
*/

/*
setResidentIsMurderer
Description:    a mutator to change to isMurderer variable.
Pre-Condition:  must be passed a variable if the resident is a murderer.
Post-Condition: Changes the calling object's isMurderer variable.
*/
#include <iostream>

class Resident
{
public:
  Resident();
  void changeHairColor(const int changingHairColor);
  void killMe();

  friend std::ostream &operator << (std::ostream & os,
    const Resident & residentToOuput);

  // Accessors
  std::string getResidentName()const
    { return m_residentName; }
  int getHair()const
    { return m_residentHairColor; }

  // Mutators
  void setResidentIsMurderer(bool isMurderToChange)
    { m_isMurderer = isMurderToChange; return; }

private:
  std::string m_residentName;
  bool m_isAlive;
  bool m_isMurderer;
  int m_residentHairColor;

};


#endif /* defined(Final_Boss__Resident) */
