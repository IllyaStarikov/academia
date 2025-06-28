//Programmers: ALEX ANDROFF & ILLYA STARIKOV  DATE: 3/21/15
//Class: CS1570                               Section: A
//Filename: constants.h
//Purpose: Use different tests to determine the identity of a missing cow.

#ifndef Homework_8_Constants_h
#define Homework_8_Constants_h

// The number of iterations for the main loop.
const int cMAIN_ITERATIONS = 3;

// This is strictly for readability of code.
const char cNTC = '\0';

// First Test (DNA) Constants
const int cMISSING_COWS = 5;
const int cDEAD_COW = 1;

const int cDNA_MISSINGCOWSLENGTH = 128;
const int cDNA_MATCHINGCOWLENGTH = 16;

/*
 These constants drive the first test.

 Made dynamic, therefore by changing one constant, you can change the
 whole program in this single file.
 Examples range from:
 SMALL: Changing one percent changes the amount in the whole program.
 LARGE: Adding a whole other member of DNA like 'U' will include it in the
 rest of the program, if done correctly.

 Something things to note:
 - *Most Important*: The arrays **MUST** line up. The first cell DNA Member
 must correspond to the second const's first cell - so on and so forth.
 If not, information will be invalid.
 - These constants are dependent of one another.
 Decreasing a length and not updating respective constants will break the
 program. Adding a length but not including additional information will do
 nothing.
 - A mistake in one cascades down to the other. A change, likewise.
 - These constants are made to be as fluid as possible.

 First, the cDNA_Length dictates the amount of members there are.

 Second, the cDNA_MEMBERS are the members of the DNA. So C, T, G, etc.

 Third, the the percentages correspond to the cDNA_MEMBERS.
 cDATA_CALCULATED_DOWN_THE_LINE signifies that there is no valid percentage.
 A percentage is not even specified to reduce confusion.
 There is a placeholder because certain numbers not every number works with the
 percentage.

 EXAMPLE:
 128 * [Percentages array] = 128 total.
 129 * [Percentages array] = 129 total.
 130 * [Percentages array] = 131 total.
 Above, Not Rounded    = 129 total.

 Doesn't work every time.
 Actually, it doesn't work less and less the higher you scale.
 1,000 members? 70%.
 1,000,000,000 members? 4.8%.
 1,000,000,000,000? Just forget about it.
 And, these values are rounded.

 Fourth, the values are calculated for the actual number of members for the
 cows.
 Granted, I could have wrote a function for this inside random assignment,
 but then it wouldn't be constants because I couldn't assign them in.
 So, better to calculate them here at runtime. Also, they are rounded.

 Last, same principle applies to the Matching Cow we found.. dead. :(

 */
const int cDATA_CALCULATED_DOWN_THE_LINE = 0;

const int cDNA_LENGTH = 4;
const char cDNA_MEMBERS[cDNA_LENGTH] =
{
  'C','T','G','A'
};

const float cDNA_PERCENTAGE[cDNA_LENGTH] =
{
  d
};

const int cDNA_LENGTHOFMEMBERS_MISSINGCOW[cDNA_LENGTH] =
{
  static_cast<int>(cDNA_PERCENTAGE[0] * cDNA_MISSINGCOWSLENGTH + .5),
  static_cast<int>(cDNA_PERCENTAGE[1] * cDNA_MISSINGCOWSLENGTH + .5),
  static_cast<int>(cDNA_PERCENTAGE[2] * cDNA_MISSINGCOWSLENGTH + .5),
  cDNA_MISSINGCOWSLENGTH - (cDNA_LENGTHOFMEMBERS_MISSINGCOW[0] +
                cDNA_LENGTHOFMEMBERS_MISSINGCOW[1] +
                cDNA_LENGTHOFMEMBERS_MISSINGCOW[2])
};
const int cDNA_LENGTHOFMEMBERS_MATCHINGCOW[cDNA_LENGTH] =
{
  static_cast<int>(cDNA_PERCENTAGE[0] * cDNA_MATCHINGCOWLENGTH + .5),
  static_cast<int>(cDNA_PERCENTAGE[1] * cDNA_MATCHINGCOWLENGTH + .5),
  static_cast<int>(cDNA_PERCENTAGE[2] * cDNA_MATCHINGCOWLENGTH + .5),
  cDNA_MATCHINGCOWLENGTH - (cDNA_LENGTHOFMEMBERS_MATCHINGCOW[0] +
                cDNA_LENGTHOFMEMBERS_MATCHINGCOW[1] +
                cDNA_LENGTHOFMEMBERS_MATCHINGCOW[2])
};

const float cCHANCE_OF_NULL = .02;
const char cNULL_CHAR = '-';

const float cFIRSTTEST_SUCCESSPERCENT = 90.0;

//Second Test(Dental) constants

const int cNUMBER_OF_TEETH = 32;

const int cDENTAL_LENGTH = 5;
const char cDENTAL_MEMBERS[cDENTAL_LENGTH] =
{
  'N','W','A','G','L'
};
const float cDENTAL_PERCENTAGE[cDENTAL_LENGTH] =
{
  .50, .20, .10, .10, cDATA_CALCULATED_DOWN_THE_LINE};

const int cDENTAL_LENGTHOFMEMBERS_COW[cDENTAL_LENGTH] =
{
  static_cast<int>(cDENTAL_PERCENTAGE[0] * cNUMBER_OF_TEETH + .5),
  static_cast<int>(cDENTAL_PERCENTAGE[1] * cNUMBER_OF_TEETH + .5),
  static_cast<int>(cDENTAL_PERCENTAGE[2] * cNUMBER_OF_TEETH + .5),
  static_cast<int>(cDENTAL_PERCENTAGE[3] * cNUMBER_OF_TEETH + .5),
  cNUMBER_OF_TEETH - (cDENTAL_LENGTHOFMEMBERS_COW[0] +
            cDENTAL_LENGTHOFMEMBERS_COW[1] +
            cDENTAL_LENGTHOFMEMBERS_COW[2] +
            cDENTAL_LENGTHOFMEMBERS_COW[3])
};

#endif