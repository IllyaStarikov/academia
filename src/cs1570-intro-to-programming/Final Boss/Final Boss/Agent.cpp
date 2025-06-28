// Programmers: Illya Starikov and Alex Androff       Date: 04/17/15
// File: Agent.cpp                                    Class: CS1570A
// Purpose: To write the definitions of the Agent Class

#include "Agent.h"
#include "Functions.h"
#include "Constants.h"

csiAgent::csiAgent()
{
  m_name = CSI_AGENT_NAME;
}

void csiAgent::visitCrimeScene(CrimeRoom roomToInvestigate)
{

  gatherInformation(roomToInvestigate);

  return;
}

void csiAgent::gatherInformation(CrimeRoom roomToGatherInformation)
{

  int assignmentCounter = 0;

  int randomHeight, randomLength, randomLocation;
  int randomFlipHeight, randomFlipLength;

  bool oppositeMembers;
  char temp;

  m_theEvidence = roomToGatherInformation.getEvidence();

  /*--------------------HAIR CORRUPTION--------------------*/
  m_theEvidence.m_hair = dataCorruptionAddition
  (m_theEvidence.m_hair, randomArbitrary
   (MIN_HAIR_CORRUPTION, MAX_HAIR_CORRUPTION), HAIR_MIN, HAIR_MAX);

  /*--------------------DNA CORRUPTION--------------------*/
  do
  {
    randomLocation = randomArbitrary(0, LENGTH_OF_DNA - 1);
    if (m_theEvidence.m_DNA[randomLocation] != DNA_CORRUPTION_CHAR)
    {
      m_theEvidence.m_DNA[randomLocation] = DNA_CORRUPTION_CHAR;
      ++assignmentCounter;
    }
    else if (m_theEvidence.m_DNA[randomLocation] == DNA_CORRUPTION_CHAR)
    {
      m_theEvidence.m_DNA[randomLocation] =
      roomToGatherInformation.getRoomDNACharacter(randomLocation);
      ++assignmentCounter;
    }
  } while (assignmentCounter < DNA_CORRUPTION_LENGTH);

  // Reset the assignmentCounter for next loop.
  assignmentCounter = 0;

  /*--------------------FINGER PRINT CORRUPTION--------------------*/
  // I am about to.. FLIP THE SCRIPT.
  do
  {
    // Get Random Spots that *do not* have the same types
    randomLength = randomArbitrary(0, LENGTH_OF_FINGERPRINT_ARRAY - 1);
    // - 1 Because location starts at 0
    randomHeight = randomArbitrary(0, HEIGHT_OF_FINGERPRINT_ARRAY - 1);
    // Same reasoning as above
    do
    {
      randomFlipLength = randomArbitrary(0,
                         LENGTH_OF_FINGERPRINT_ARRAY
                         - 1);
      randomFlipHeight = randomArbitrary(0,
                         HEIGHT_OF_FINGERPRINT_ARRAY
                         - 1);

      oppositeMembers = (m_theEvidence.m_forensicPrint.
                 fingerPrintData[randomLength][randomHeight]
                 != m_theEvidence.m_forensicPrint.
                 fingerPrintData[randomFlipLength]
                 [randomFlipHeight]);
    } while (oppositeMembers == false);

    // Reverse Bubble Sort.
    // This is made to scale. That's why reverse.

    temp = m_theEvidence.m_forensicPrint.fingerPrintData[randomLength]
    [randomHeight];
    m_theEvidence.m_forensicPrint.fingerPrintData[randomLength]
    [randomHeight] = m_theEvidence.m_forensicPrint.fingerPrintData
    [randomFlipLength][randomFlipHeight];
    m_theEvidence.m_forensicPrint.fingerPrintData[randomFlipLength]
    [randomFlipHeight] = temp;
    ++assignmentCounter;
  } while (assignmentCounter < FINGERPRINT_CORRUPTION_LENGTH);

  // Member Variable Corruption
  m_theEvidence.m_forensicPrint.loops =
  dataCorruptionAddition(m_theEvidence.m_forensicPrint.loops,
               randomArbitrary(LOOP_MIN_CORRUPTION,
                       LOOP_MAX_CORRUPTION),
               LOOPS_MIN, LOOPS_MAX);
  m_theEvidence.m_forensicPrint.arches =
  dataCorruptionAddition(m_theEvidence.m_forensicPrint.arches,
               randomArbitrary(ARCH_MIN_CORRUPTION,
                       ARCH_MAX_CORRUPTION),
               ARCHES_MIN, ARCHES_MAX);
  m_theEvidence.m_forensicPrint.whirls =
  dataCorruptionAddition(m_theEvidence.m_forensicPrint.whirls,
               randomArbitrary(WHIRL_MIN_CORRUPTION,
                       WHIRL_MAX_CORRUPTION),
               WHIRLES_MIN, WHIRLES_MAX);

  return;
}

bool csiAgent::perpSearch(Resident residentToSearch)
{
  float score;
  float dnaScore, fingerPrintScore, hairScore;
  int matchingNumber, offByX;

  matchingNumber = 0;
  /*--------------------DNA SCORE CALCULATOR--------------------*/
  for (int i = 0; i < LENGTH_OF_DNA; ++i )
  {
    // I know this is a very inneffecient way to do this,
    // but it's the best i can do without pointers
    if (residentToSearch.getResidentDNACharacter(i)
      == m_theEvidence.m_DNA[i])
    {
      ++matchingNumber;
    }
  }
  dnaScore =  static_cast<float>(matchingNumber) / LENGTH_OF_DNA;

  // Reset For Next Iteration
  matchingNumber = 0;

  /*--------------------FINGERPRINT SCORE CALCULATOR--------------------*/
  for (int i = 0; i < LENGTH_OF_FINGERPRINT_ARRAY; ++i)
  {
    for (int j = 0; j < HEIGHT_OF_FINGERPRINT_ARRAY; ++j)
    {
      if (residentToSearch.getResidentFingerPrintCharacter(i, j) ==
        FINGERPRINT_MEMBERS[true] &&
        m_theEvidence.m_forensicPrint.fingerPrintData[i][j] ==
        FINGERPRINT_MEMBERS[true])
      {
        ++matchingNumber;
      }
    }
  }

  fingerPrintScore = MATCHING_STARS_MULTIPLIER *
  (static_cast<float>(matchingNumber) / NUMBER_OF_STARS);

  if (withinX(m_theEvidence.m_forensicPrint.loops,
        residentToSearch.getResidentFingerPrintLoops(),
        LOOPS_COMPARISON_MARGIN))
  {
    fingerPrintScore += LOOPS_COMPARISON_ADDER;
  }
  if (withinX(m_theEvidence.m_forensicPrint.arches,
        residentToSearch.getResidentFingerPrintArches(),
        ARCHES_COMPARISON_MARGIN))
  {
    fingerPrintScore += ARCHES_COMPARISON_ADDER;
  }
  if (withinX(m_theEvidence.m_forensicPrint.whirls,
        residentToSearch.getResidentFingerPrintWhirles(),
        WHIRLES_COMPARISON_MARGIN))
  {
    fingerPrintScore += WHIRLES_COMPARISON_ADDER;
  }

  /*--------------------HAIR SCORE CALCULATOR--------------------*/
  offByX = absolute(m_theEvidence.m_hair -
            residentToSearch.getResidentHair());
  switch (offByX)
  {
    case (0):
      hairScore = HAIR_IDENTICAL;
      break;

    case (1):
      hairScore = HAIR_OFF_BY_ONE;
      break;

    case (2):
      hairScore = HAIR_OFF_BY_TWO;
      break;

    default:
      hairScore = HAIR_OFF_BY_THREE_OR_MORE;
      break;
  }

  score = (dnaScore * DNA_SCORE_MULTIPLIER) +
  (fingerPrintScore * FINGERPRINT_SCORE_MULTIPLIER) +
  (hairScore * HAIR_SCORE_MULTIPLIER);
  return (round(score * 100) >= (PERP_SEARCH_SUCCESS * 100));
}

int csiAgent::dataCorruptionAddition(const int data, const int dataAddition,
                   const int floor, const int ceiling)const
{
  int dataToReturn = data + dataAddition;

  if (dataToReturn < floor)
  {
    dataToReturn = floor;
  }
  else if (dataToReturn > ceiling)
  {
    dataToReturn = ceiling;
  }

  return dataToReturn;
}

bool csiAgent::withinX(const int originalNumber, const int comparingNumber,
             const int marginOfError)const
{
  return (originalNumber <= comparingNumber + marginOfError &&
      originalNumber >= comparingNumber - marginOfError);
}