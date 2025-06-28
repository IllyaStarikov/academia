// Programmers: Illya Starikov and Alex Androff         Date: 04/17/15
// File: ForensicData.h                                 Class: CS1570A
// Purpose: Define different forensic data types for the program

#ifndef Final_Boss__Forensic_Data
#define Final_Boss__Forensic_Data

#include "Constants.h"

struct fingerPrint
{
  char fingerPrintData[LENGTH_OF_FINGERPRINT_ARRAY + 1]
  [HEIGHT_OF_FINGERPRINT_ARRAY + 1];
  int loops, arches, whirls;
};

struct forensicData
{
  int m_hair;
  char m_DNA[LENGTH_OF_DNA + 1]; // +1 For Null Terminating Character
  fingerPrint m_forensicPrint;
};

#endif /* defined(Final_Boss__Forensic_Data) */
