// Programmer: Illya Starikov                Date: 04/17/15
// File: Functions.h                     Class: CS1570A
// Purpose: Prototype general functions.

#ifndef Final_Boss__Functions
#define Final_Boss__Functions

using namespace std;

/*
Description:    To parse a file containing names, returning a single name.
                Will incrememnt the names, working down the file.
Pre-Condition:  File must be present, or will show an error message.
Post-Condition: Returns a name to be used.
*/
string fileNameParsor();

/*
Description:    determine the file size of the file.
Pre-Condition:  File must be present in the fileNameParsor function.
Post-Condition: Returns the size of the file.
*/
unsigned int fileSize(ifstream& fin);


/*
Description:    Returns an random, arbitrary number.
Pre-Condition:  must be passed a floor and ceiling of the function.
Post-Condition: Returns a random, arbitrary number within the specified
fllor and ceiling.
*/
int randomArbitrary(const int floor, const int ceiling);

/*
Description:    Returns an error message determined by the code.
Pre-Condition:  Must be a valid errorCode
Post-Condition: Side effects, cout statements.
*/
void errorMessage(const int errorCode);

#endif /* defined(Final_Boss__Functions) */