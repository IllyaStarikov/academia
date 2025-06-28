// Programmer: Illya Starikov                                Date: 15/03/02
// File: TODist                                              Class: CS1570A
// Purpose: To Calculate the time of death for someone under
// strange circumstances.

#include <iostream>

// *notes to grader* 
// 1. func is my Hungarian abbreviation for function
// 2. Not sure how precise you want my documentation to be, so I got as 
// precise as possible. Please note if less documentation is wanted/needed
// 3. Due to large variable names, most of code goes past the 80th column.
// Tried to adjust as best as possible

// FUNCTIONS

// FUNCTION DESCRIPTION: To Greet the user with a short cout statement
// PRE CONDITION:  none.
// POST CONDITION: single cout statement with greeting
void funcGreetingMessage();

// FUNCTION DESCRIPTION: Present menu to user, accept input
// PRE CONDITION: accepts any input, but a valid input should be 1-6
// POST CONDITION: return the menu choice, main_menuoption
char funcPresentMenu();

// FUNCTION DESCRIPTION: to get user data for Rigor Mortis
// PRE CONDITION:  the body temperature be within the range of the 
// specified constants, the char either be a "T, F, t, f"
// POST CONDITION: [Everything is passed by reference] nothing is returned,
// but the actual values for specified arguments are altered 
// arguments include body temp, input character to change to the two bools
void funcUserData_RigorMortis(float & floBodyTemperature, 
  char & charInputForBoolEvalutation, bool & boolComputerScientist, 
  bool & boolIllness);

// FUNCTION DESCRIPTION: to get user data for Algor Mortis
// PRE CONDITION: the body temperature be within the range of the 
// specified constants
// POST CONDITION: [Everything is passed by reference] nothing is returned,
// but the actual values for specified arguments are altered 
// arguments include only the body temperature
void funcUserData_AlgorMortis(float & floBodyTemperature);

// FUNCTION DESCRIPTION: to get user data for Occular Mortis
// PRE CONDITION:  the char either be a "T, F, t, f"
// POST CONDITION: [Everything is passed by reference] nothing is returned,
// but the actual values for specified arguments are altered 
// arguments include a character to be evaluated to the be changed to the
// two bool values
void funcUserData_OccularMortis(char & charInputForBoolEvalutation, 
  bool & boolOccularDiscoloration, bool & boolEyesBulging);

// FUNCTION DESCRIPTION: to get user data for Vitreous Potassium Mortis
// PRE CONDITION: the potassium concentrate is within the range specified 
// in the constants
// POST CONDITION: [Everything is passed by reference] nothing is returned,
// but the actual values for specified arguments are altered 
// arguments include floPotassiumConcentrateFormEyeFluid
void funcUserData_funcVitreousPotassiumMortis(float & 
  floPotassiumConcentrationFromEyeFluid);

// FUNCTION DESCRIPTION: to get user data for Stomach Mortis
// PRE CONDITION: the number of shots is within the constants specified
// POST CONDITION:[Everything is passed by reference] nothing is returned,
// but the actual values for specified arguments are altered 
// arguments include the number of shots
void funcUserData_funcStomachMortis(int & intNumberOfShots);

// FUNCTION DESCRIPTION: to display error message when input is invalid
// PRE CONDITION: none.
// POST CONDITION: a simple cout statement, only a side affect
void funcInvalidInputOutputStatement();

// FUNCTION DESCRIPTION: to static cast and round a float to an int
// PRE CONDITION: number be a float
// POST CONDITION: returns a rounded int
int funcFloatToIntegerAndRounding(const float floNumberToRound);

// FUNCTION DESCRIPTION: to evaluate if a function a true of false based on
// t or f, uppercase and lowercase
// PRE CONDITION: a character being passed
// POST CONDITION: returns a boolean if input is valid. if invalid, 
// prompted to input alternative number
bool funcCharToBool(char charInputForBoolEvalutation); // THIS SHOULD NOT BE A
// CONST
// Please look at function code, 
// charInputForBoolEvaluation can change if input is invalid

// FUNCTION DESCRIPTION: to calculate the TOD for Rigor Mortis option
// PRE CONDITION: float body temp be within range, and the two bools are valid
// POST CONDITION: returns an int that is rounded to be used for the TOD
int funcRigorMortis(const float floBodyTemperature, 
  const bool boolComputerScientist, const bool boolIllness);

// FUNCTION DESCRIPTION: to calculate the TOD for Algor Mortis option
// PRE CONDITION: float body temp be within range, and the two bools are valid
// POST CONDITION: returns an int that is rounded to be used for the TOD
int funcAlgorMortis(const float floBodyTemperature);

// FUNCTION DESCRIPTION: to calculate the TOD for Rigor Occular option
// PRE CONDITION: the two bools are valid
// POST CONDITION: returns an int that is rounded/type casts to be used for 
// the TOD
int funcOccularMortis(const bool boolOccularDiscoloration, 
  const bool boolEyesBulging);

// FUNCTION DESCRIPTION: to calculate the TOD for Rigor Potassium option
// PRE CONDITION: potassium concentrate is within range, specified in consts
// POST CONDITION: returns an int that is rounded to be used for the TOD
int funcVitreousPotassiumMortis(const float 
  floPotassiumConcentrationFromEyeFluid);

// FUNCTION DESCRIPTION: to calculate the TOD for Rigor Stomach option
// PRE CONDITION: the number of shots are within the range specified in the 
// consts
// POST CONDITION: returns an int that is rounded to be used for the TOD
int funcStomachMortis(const int intNumberOfShots);

// FUNCTION DESCRIPTION: to present results to the user, after calculation
// PRE CONDITION: TOD and Error tolerance are only passed.
// POST CONDITION: cout statements, side effects
void funcPresentResults(const int intTimeOfDeath, 
  const int intErrorTolerance);

// FUNCTION DESCRIPTION: say farewells to the user.
// PRE CONDITION: none
// POST CONDITION: cout statement, side effects
void funcSignOffMessage();

// NAMESPACES
using namespace std;

// CONSTANTS
// [FUNCTIONS]
// Part of the formulas used within the functions
const float cAVERAGEBODYTEMPERATURE = 98.6;

const float cRIGORMORTIS_DIVISOR = 2.1;
const float cRIGORMORTIS_ILLADDER = 1.5;
const float cRIGORMORTIS_COMPUTERSCIENTISTSUBTRACTOR = 2.5;

const float cALGORMORTIS_DIVISOR = 1.5;

const float cVITREOUSPOTASSIUMMORTIS_MULTIPLIER = 17.14;
const float cVITREOUSPOTASSIUMMORTIS_SUBTRACTOR = 39.1;

const int cSTOMACHMORTIS_SUBTRACTEE = 10;

const int cNODISCOLORATION_NOBULGING = 4;
const int cNODISCOLORATION_YESBULGING = 16;
const int cYESDISCOLORATION_NOBULGING = 7;
const int cYESDISCOLORATION_YESBULGING = 24;

// [ERROR TOLERANCE]
const int cET_RIGORMORTIS = 3;
const int cET_ALGORMORTIS = 2;
const int cET_OCCULARMORTIS = 5;
const int cET_VITREOUSPOTASSIUMMORTIS = 4;
const int cET_STOMACHMORTIS = 0;

// [VALIDATION MIN/MAXES]
const int cMAX_NUMBEROFSHOTS = 30;
const int cMIN_NUMBEROFSHOTS = 0;
const float cMAX_BODYTEMPERATURE = 134; 
// assuming he might of been found in Death Valley
const float cMIN_BODYTEMPERATURE = -129; 
// assuming he might of been found in Antarctica
const int cMAX_POTASSIUMCONCENTRATIONFROMEYEFLUID = 7;
const int cMIN_POTASSIUMCONCENTRATIONFROMEYEFLUID = 3;

int main()
{
  
  char charMenuOption, charInputForBoolEvalutation;
  bool boolProgramQuit = false, boolShouldCalculate;
  
  float floBodyTemperature;                          // Every Mortis
  bool boolComputerScientist, boolIllness;          // Rigor Mortis
  bool boolOccularDiscoloration, boolEyesBulging;  // Occular Mortis
  float floPotassiumConcentrationFromEyeFluid;    // Vitreous Potassium Mortis
  int intNumberOfShots;                          // Stomach Mortis
  
  int intErrorTolerance = 0; // Initialized For Semantic Purposes
  int intMain_TimeofDeath = 0; // Could be passed without have a value
  
  funcGreetingMessage(); // pre menu greeting call
  
  do
  {
    
    charMenuOption = funcPresentMenu();
    boolShouldCalculate = true; 
    // Resets - Changes Value In Switch Case Default
    
    // Table Of Contents
    // 1.  RigorMortis
    // 2.  AlgorMortis
    // 3.  OccularMortis
    // 4.  VitreousPotassiumMortis
    // 5.  StomachMortis
    // 6.  Program Quit
    
    switch (charMenuOption)
    {
      case '1':
        funcUserData_RigorMortis(floBodyTemperature, 
          charInputForBoolEvalutation, boolComputerScientist, 
          boolIllness);
        intMain_TimeofDeath = funcRigorMortis(floBodyTemperature, 
          boolComputerScientist, boolIllness);
        
        break;
        
      case '2':
        funcUserData_AlgorMortis(floBodyTemperature);
        intMain_TimeofDeath = funcAlgorMortis(floBodyTemperature);
        
        break;
        
      case '3':
        funcUserData_OccularMortis(charInputForBoolEvalutation, 
          boolOccularDiscoloration, boolEyesBulging);
        intMain_TimeofDeath = funcOccularMortis(
          boolOccularDiscoloration, boolEyesBulging);
        
        break;
        
      case '4':
        funcUserData_funcVitreousPotassiumMortis(
          floPotassiumConcentrationFromEyeFluid);
        intMain_TimeofDeath = funcVitreousPotassiumMortis(
          floPotassiumConcentrationFromEyeFluid);
        
        break;
        
      case '5':
        funcUserData_funcStomachMortis(intNumberOfShots);
        intMain_TimeofDeath = funcStomachMortis(intNumberOfShots);
        
        break;
        
      case '6':
        boolProgramQuit = true;
        boolShouldCalculate = false;
        
        break;
        
      default:
        cout << endl 
             << "Sorry, this is an invalid option" << endl 
             << "Please Try Again" << endl << endl;
        boolShouldCalculate = false;
        
        break;
        
    }
    
    if (boolShouldCalculate == true)
    {
      // Inherit The Error Tolerance
      // This way, the calculations are done after switch,
      // Instead of having 5 different functions/function calls in
      // respective case
      
      if (charMenuOption == '1')
      {
        intErrorTolerance = cET_RIGORMORTIS;
      }
      else if (charMenuOption == '2')
      {
        intErrorTolerance = cET_ALGORMORTIS;
      }
      else if (charMenuOption == '3')
      {
        intErrorTolerance = cET_OCCULARMORTIS;
      }
      else if (charMenuOption == '4')
      {
        intErrorTolerance = cET_VITREOUSPOTASSIUMMORTIS;
      }
      else if (charMenuOption == '5')
      {
        intErrorTolerance = cET_STOMACHMORTIS;
      }
      
      funcPresentResults(intMain_TimeofDeath, intErrorTolerance);
    }
    
  } while (boolProgramQuit == false);
  
  funcSignOffMessage();
  return 0;
}

// [INTIAL FUNCTIONS]
void funcGreetingMessage()
{
  cout 
       << "Welcome to the TODist" << endl 
       << "You're one and only source of Time of Death Calculations" << endl;
  
  return;
}

char funcPresentMenu()
{
  char charPresentMenu_MenuOption;
  cout << endl 
       << "Main Menu" << endl
       << "1.  RigorMortis" << endl
       << "2.  AlgorMortis" << endl
       << "3.  OccularMortis" << endl
       << "4.  VitreousPotassiumMortis" << endl
       << "5.  StomachMortis" << endl
       << "6.  QuitMortis" << endl
       << "Menu Option: ";
  cin >> charPresentMenu_MenuOption;
  
  return charPresentMenu_MenuOption;
}

void funcUserData_RigorMortis(float & floBodyTemperature, 
  char & charInputForBoolEvalutation, bool & boolComputerScientist, 
  bool & boolIllness) {
  cout << "** Rigor Mortis **" << endl;
  do
  {
    cout <<
            "Body Temperature: ";
    cin >> floBodyTemperature;
    if ((floBodyTemperature > cMAX_BODYTEMPERATURE) || 
      (floBodyTemperature < cMIN_BODYTEMPERATURE))
    {
      funcInvalidInputOutputStatement();
    }
  } while ((floBodyTemperature > cMAX_BODYTEMPERATURE) || 
    (floBodyTemperature < cMIN_BODYTEMPERATURE));
  cout << "Computer Scientist (Y or N): ";
  cin >> charInputForBoolEvalutation;
  boolComputerScientist = funcCharToBool(charInputForBoolEvalutation);
  cout << "Was Ill (Y or N): ";
  cin >> charInputForBoolEvalutation;
  boolIllness = funcCharToBool(charInputForBoolEvalutation);
}

void funcUserData_AlgorMortis(float & floBodyTemperature) {
  cout << endl <<
  "** Algor Mortis **" << endl;
  do
  {
    cout <<
    "Body Temperature: ";
    cin >> floBodyTemperature;
    if ((floBodyTemperature > cMAX_BODYTEMPERATURE) || 
      (floBodyTemperature < cMIN_BODYTEMPERATURE))
    {
      funcInvalidInputOutputStatement();
    }
  } while ((floBodyTemperature > cMAX_BODYTEMPERATURE) || 
    (floBodyTemperature < cMIN_BODYTEMPERATURE));
}

void funcUserData_OccularMortis(char & charInputForBoolEvalutation, 
  bool & boolOccularDiscoloration, bool & boolEyesBulging) {
  cout << endl 
       << "** Occular Mortis **" << endl 
       << "Occular Discoloration (Y or N): ";
  cin >> charInputForBoolEvalutation;
  boolOccularDiscoloration = funcCharToBool(charInputForBoolEvalutation);
  cout << "Eyes Bulging (Y or N): ";
  cin >> charInputForBoolEvalutation;
  boolEyesBulging = funcCharToBool(charInputForBoolEvalutation);
}

void funcUserData_funcVitreousPotassiumMortis(float & 
  floPotassiumConcentrationFromEyeFluid) {
  cout << endl <<
  "** Vitreous Potassium Mortis **" << endl;
  do
  {
    cout << "Potassium Concentration From Eye Fluid: ";
    cin >> floPotassiumConcentrationFromEyeFluid;
    if ((floPotassiumConcentrationFromEyeFluid  > 
      cMAX_POTASSIUMCONCENTRATIONFROMEYEFLUID) || 
      (floPotassiumConcentrationFromEyeFluid < 
        cMIN_POTASSIUMCONCENTRATIONFROMEYEFLUID))
    {
      funcInvalidInputOutputStatement();
    }
  } while ((floPotassiumConcentrationFromEyeFluid  > 
    cMAX_POTASSIUMCONCENTRATIONFROMEYEFLUID) || (
    floPotassiumConcentrationFromEyeFluid < 
    cMIN_POTASSIUMCONCENTRATIONFROMEYEFLUID));
}

void funcUserData_funcStomachMortis(int & intNumberOfShots) {
  cout << endl <<
  "** Stomach Mortis **" << endl;
  do
  {
    
    cout <<
    "Number of Shots: ";
    cin >> intNumberOfShots;
    if ((intNumberOfShots > cMAX_NUMBEROFSHOTS) || 
      (intNumberOfShots < cMIN_NUMBEROFSHOTS))
    {
      funcInvalidInputOutputStatement();
    }
  } while ((intNumberOfShots > cMAX_NUMBEROFSHOTS) || 
    (intNumberOfShots < cMIN_NUMBEROFSHOTS));
}

// [SWITCH CASE FUNCTIONS]
// NOTES
// 1. The return types are mismatched in all case functions. Therefore, a 
// rounding and static cast function is needed.
// The rounding function is in the maintenance functions, and is called upon 
// returning.

int funcRigorMortis(const float floBodyTemperature, 
  const bool boolComputerScientist, const bool boolIllness)
{
  float floTimeOfDeath = 0;
  
  floTimeOfDeath = ((cAVERAGEBODYTEMPERATURE - floBodyTemperature)/
    cRIGORMORTIS_DIVISOR);
  if (boolIllness == true)
  {
    floTimeOfDeath += cRIGORMORTIS_ILLADDER;
  }
  if (boolComputerScientist == true)
  {
    floTimeOfDeath -= cRIGORMORTIS_COMPUTERSCIENTISTSUBTRACTOR;
  }
  
  return (funcFloatToIntegerAndRounding(floTimeOfDeath));
}

int funcAlgorMortis(const float floBodyTemperature)
{
  float floTimeOfDeath = 0;
  
  floTimeOfDeath = (cAVERAGEBODYTEMPERATURE - floBodyTemperature)
    / cALGORMORTIS_DIVISOR;
  
  return (funcFloatToIntegerAndRounding(floTimeOfDeath));
}

int funcOccularMortis(const bool boolOccularDiscoloration, 
  const bool boolEyesBulging)
{
  
  float floTimeOfDeath  = 0;
  
  // could have nested this but it would be less readable for
  // such a small decision branch
  // also, matching constants and if statements make it *far* easier to 
  // follow
  if (boolOccularDiscoloration == false && boolEyesBulging == false)
  {
    floTimeOfDeath = cNODISCOLORATION_NOBULGING;
  }
  else if (boolOccularDiscoloration == false && boolEyesBulging == true)
  {
    floTimeOfDeath = cNODISCOLORATION_YESBULGING;
  }
  else if (boolOccularDiscoloration == true && boolEyesBulging == false)
  {
    floTimeOfDeath = cYESDISCOLORATION_NOBULGING;
  }
  else if (boolOccularDiscoloration == true && boolEyesBulging == true)
  {
    floTimeOfDeath = cYESDISCOLORATION_YESBULGING;
  }
  else
  {
    cout << "Well, I may have made an error in judgment" << endl;
  }
  
  return (funcFloatToIntegerAndRounding(floTimeOfDeath));
}

int funcVitreousPotassiumMortis(const float 
  floPotassiumConcentrationFromEyeFluid)
{
  float floTimeOfDeath  = 0;
  
  floTimeOfDeath = (cVITREOUSPOTASSIUMMORTIS_MULTIPLIER * 
    floPotassiumConcentrationFromEyeFluid) 
    - cVITREOUSPOTASSIUMMORTIS_SUBTRACTOR;
  
  return (funcFloatToIntegerAndRounding(floTimeOfDeath));
}

int funcStomachMortis(const int intNumberOfShots)
{
  float floTimeOfDeath = 0;
  
  floTimeOfDeath = cSTOMACHMORTIS_SUBTRACTEE - intNumberOfShots;
  
  return (funcFloatToIntegerAndRounding(floTimeOfDeath));
}

// [POST CASE FUNCTIONS]
void funcPresentResults(const int intTimeOfDeath, const int intErrorTolerance)
{
  
  cout 
        << "Victim's Time of Death Estimation" << endl
        << "Between: " << ((intTimeOfDeath >= intErrorTolerance)? 
          (intTimeOfDeath - intErrorTolerance):0) << " and " << 
          (intTimeOfDeath + intErrorTolerance) << " Hours" << endl;
  
}

void funcSignOffMessage()
{
  cout << endl 
       << "Thank you for using TODist" << endl 
       << "Have a nice day!" << endl << endl;
  
}

// [MAINTENANCE FUNCTIONS]
void funcInvalidInputOutputStatement()
{
  cout << "Invalid Input. Please Try Again." << endl;
}
bool funcCharToBool(char charInputForBoolEvalutation)
{
  bool boolPassingValue = false; // has to be initialized
  bool boolCharToBool_LoopKick;
  do
  {
    
    if (charInputForBoolEvalutation == 'y' || charInputForBoolEvalutation 
      == 'Y')
    {
      boolPassingValue = true;
      boolCharToBool_LoopKick = true;
    }
    else if (charInputForBoolEvalutation == 'n' || 
      charInputForBoolEvalutation == 'N')
    {
      boolPassingValue = false;
      boolCharToBool_LoopKick = true;
    }
    else
    {
      cout
            << "Sorry, this is an invalid option" << endl
            << "Please Try Again." << endl
            << "Y or N: ";
      cin >> charInputForBoolEvalutation;
      boolCharToBool_LoopKick= false;
    }
  } while (boolCharToBool_LoopKick == false);
  
  return boolPassingValue;
}

int funcFloatToIntegerAndRounding(const float floNumberToRound)
{
  int intReturningNumber;
  
  intReturningNumber = static_cast<int>((floNumberToRound + .5));
  
  return intReturningNumber;
}