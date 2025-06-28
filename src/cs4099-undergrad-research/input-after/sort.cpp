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
//  sort.cpp
//  input
//
//  Created by Illya Starikov on 01/10/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//
//
#include <iostream>
using namespace std;

int main()
{__lineNum__(0);

  bool swapped = true;
__lineNum__(1);
  int a[3] = {3, 2, 1};
__lineNum__(2);
  int arraySize = 3;
__lineNum__(3);

  WHILELOOP1:


    swapped = false;
__lineNum__(4);
    int i = 1;
__lineNum__(5);
FORLOOP1:


      if (a[i-1] > a[i])
      {
        a[i] = a[i-1];
__lineNum__(6);
        a[i-1] = a[i];
__lineNum__(7);
        swapped = true;
__lineNum__(8);
      }
    

 i++;
__lineNum__(9);
if ( i <= arraySize-1) {
__lineNum__(10);
  goto FORLOOP1;
__lineNum__(11);
}

  

if (swapped) {
  goto WHILELOOP1;
__lineNum__(12);
}


  // Output results

  for (int i = 0; i < arraySize; i++)
    cout << a[i] << " ";
__lineNum__(13);
  cout << endl;
__lineNum__(14);

  return(0);
}
