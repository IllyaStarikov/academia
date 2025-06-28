// Programmer: Illya Starikov                                Date: 03/06/15
// File: WavelengthCalculator5001.h                          Class: CS1570A
// Purpose: To find the wavelengths of.. very, very strange matter.

#ifndef Homework6_Header
#define Homework6_Header

// FUNCTIONS
// [BEGINNING FUNCTIONS]

// Description:     Greet the user a pleasant message.
// Pre-Condition:   None.
// Post-Condition:  cout statements, side effects.
void funcGreetingMessage();

// Description:     To get user input to dictate what menu option is selected.
// Pre-Condition:   A valid character must be entered.
// Post-Condition:  A value for charMenuOption is received,
// dictating what functions are used form there.
void funcPresentMenu_GetInput(char & charMenuOption);

// Description:     To drive the rest of the program,
// go to the respective functions that are needed for results.
// Pre-Condition:   A value for charMenuOption must be present,
// and intWavelength must be calculated before the return statement.
// Post-Condition:  The rest of the program is branched out. Respective
// functions are called, values are being received from those functions to be
// passed to the calculating functions. Although nothing is returned,
// the intWavelength is passed by reference, and is modified to the proper val-
// ue (<-  sorry about that)
void funcMainMenu(const char charMenuOption, int & intWavelength,
                                             bool & boolPresentResults);

// [SWITCH CASE FUNCTIONS]
// Nothing is passed, all return something that is to be passed to one of the
// overloading functions

// Description:     To obtain a value for the hair index
// Pre-Condition:   None.
// Post-Condition:  A float for the function is returned,
// ready to be passed for it's respective calculation function.
float funcGetHairIndex();

// Description:     To obtain a value for precision
// Pre-Condition:   None.
// Post-Condition:  An int for the function is returned,
// ready to be passed for it's respective calculation function.
int funcGetPrecision();

// Description:     To obtain a boolean value for the soup being homemade
// Pre-Condition:   None.
// Post-Condition:  A boolean for the function is returned,
// ready to be passed for it's respective calculation function.
bool funcSoupIsHomemade(); // lol. boolean soup.

// Description:     To obtain a value for goo grade
// Pre-Condition:   None.
// Post-Condition:  An int for the function is returned,
// ready to be passed for it's respective calculation function.
int funcGetGooGrade();

// Description:     To obtain a height for the cute, little alien
// Pre-Condition:   None.
// Post-Condition:  An int for the function is returned,
// ready to be passed for it's respective calculation function.
int funcGetAlienHeight();

// [FUNCTION OVERLOADING]
// Functions are overloaded because specified in assignment

// Description:     To calculate the wavelength for hair
// Pre-Condition:   floHair Index must be valid
// Post-Condition:  returns a float (the wavelength), ready to be passed
// to the display results function.
float funcCalculateWavelength(const float floHairIndex); // For Hair

// Description:     To calculate the wavelength for saliva and hair
// Pre-Condition:   floHairIndex and intPrecision must be valid,
// initialized, and have the correct value.
// Post-Condition:  Returns a float (the wavelength), ready to be passed
// to the display results function.
float funcCalculateWavelength(const float floHairIndex,
  const int intPrecision); // Saliva and Hair

// Description:     To calculate the wavelength for chicken noodle soup,
// saliva, and hair. so strange.
// Pre-Condition:   intPrecision must be valid and boolSoupIsHomemade must be
// correct.
// Post-Condition:  Returns a float (the wavelength), ready to be passed
// to the display results function.
float funcCalculateWavelength(const int intPrecision,
  const bool boolSoupIsHomemade); // Chicken-Noodle Soup and Saliva and Hair

// Description:     To calculate the wavelength for chicken noodle soup,
// saliva, and hair. so strange.
// Pre-Condition:   intGooGrade and intAlien Height must both be valid and
// integers.
// Post-Condition:  Returns a float (the wavelength), ready to be passed
// to the display results function.
float funcCalculateWavelength(const int intGooGrade, const int intAlienHeight);

// [CLOSING FUNCTIONS]

// Description:     To present the results to the user.
// Pre-Condition:   intWavelength must be an int (thankfully, static casted
// prior to return) and have a valid value.
// Post-Condition:  cout statements. side effects.
void funcPresentResults(const int intWavelength);

// Description:     Presents a goodbye message to the user, prior to
// "return 0" in main
// Pre-Condition:   charMenuOption *must be* '5'
// Post-Condition:  cout statements. side effects.
void funcClosingMessage();

// Description:     Return a rounded int when passed a float
// Pre-Condition:   floNumberToRound is a valid float
// Post-Condition:  Return of a rounded int
int funcFloatToIntegerAndRounding(const float floNumberToRound);

// [MAINTENANCE FUNCTIONS]
// Description:     To display a warning message that something has went wrong,
// used only when improper value has been used.
// Pre-Condition:   none.
// Post-Condition:  cout statements. side effects.
void funcErrorMessage();

// CONSTANTS
const float cHAIRINDEX_BLONDE = 1.2;
const float cHAIRINDEX_BROWN = 1.3;
const float cHAIRINDEX_BLACK = 1.7;

const int cHAIRINDEX_MULTIPLIER = 400;

const float cHOMEMADESOUP_ADDER = 2.3;

const int cMAX_GOOGRADE = 6, cMIN_GOOGRADE = 0;

const int cGREENGOO_BASEWAVELENGTH = 200;
const int cADDER_GREENGOOGRADE_1 = 43, cADDER_GREENGOOGRADE_2 = 17;
const int cADDER_GREENGOOGRADE_3 = 23, cADDER_GREENGOOGRADE_4 = 77;
const int cADDER_GREENGOOGRADE_5 = 55, cADDER_GREENGOOGRADE_6 = 35;

const int cMAX_PRECISION = 8, cMIN_PRECISION = 0;
#endif