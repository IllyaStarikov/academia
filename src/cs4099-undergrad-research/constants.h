//
//  constants.h
//  undergrad-research
//
//  Created by Illya Starikov on 01/10/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#ifndef constants_h
#define constants_h

// Note *the indentation matters*
auto HEADER =
R"(#include <fstream>
using namespace std;
bool __fileOpened__ = false;
void __lineNum__(int n);
void __lineNum__(int n)
{
  static ofstream fout;
  if (! __fileOpened__) fout.open("executionTrace.txt");
  fout << n << " ";
  __fileOpened__ = true;
}

)";

#endif /* constants_h */

