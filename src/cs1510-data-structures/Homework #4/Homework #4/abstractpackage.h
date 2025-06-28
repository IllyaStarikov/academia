/* @file: AbstractPackage.h
 * Definition of Abstract class Package
 * @c - Planet Express
 *
 * Version 15.3
 */

#ifndef ABSTRACTPACKAGE_H
#define ABSTRACTPACKAGE_H

#include <string>

using namespace std;


//----------------------------------------
/* _______________________
  /                       \
  | AbstractPackage Class |
  \_______________________/

    ABSTRACT CLASS

    PURPOSE: Base class for all Package classes.

*/
class AbstractPackage {
protected:
  string m_from;    // the name of the sender
  string m_to;      // the name of the receiver

public:
// Purpose: Constructor
// Postconditions: name of from and to set to parameters
// -- INLINE
   AbstractPackage(string f, string t) :
	     m_from(f), m_to(t)
	 {}

// Purpose: Returns the charge of a package.
// -- VIRTUAL
virtual float getCharge() const = 0;

// Purpose: Returns the package's sender.
// -- VIRTUAL
virtual const string& getFrom() const = 0;

// Purpose: Returns the package's receiver.
// -- VIRTUAL
virtual const string& getTo() const = 0;


// Purpose: Destructor
// -- INLINE
virtual ~AbstractPackage() {}


}; //Abstract Package


#endif
