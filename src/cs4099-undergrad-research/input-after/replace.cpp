#include <fstream>
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

//
//  replace.cpp
//  input
//
//  Created by Illya Starikov on 01/10/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//


#include <iostream>
using namespace std;

int main()
{__lineNum__(0);

  int x = 1;
__lineNum__(1);
  int y = 7;
__lineNum__(2);
  int z = 0;
__lineNum__(3);
  int a[2] = {1, 2};
__lineNum__(4);
  int arraySize = 2;
__lineNum__(5);

  int i = 0;
__lineNum__(6);
FORLOOP1:


    if (a[i] == x)
    {
      a[i] = z;
__lineNum__(7);
    }
    if (a[i] == y)
    {
      a[i] = z;
__lineNum__(8);
    }
  

 i++;
__lineNum__(9);
if ( i < arraySize) {
__lineNum__(10);
  goto FORLOOP1;
__lineNum__(11);
}


  // Output results

  for (int i = 0; i < arraySize; i++)
    cout << a[i] << " ";
__lineNum__(12);
cout << endl;
__lineNum__(13);

  return(0);
}
