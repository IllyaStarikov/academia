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
{
  bool swapped = true;
  int a[3] = {3, 2, 1};
  int arraySize = 3;

  while (swapped)
  {
    swapped = false;
    for (int i = 1; i <= arraySize-1; i++)
    {
      if (a[i-1] > a[i])
      {
        a[i] = a[i-1];
        a[i-1] = a[i];
        swapped = true;
      }
    }
  }

  // Output results

  for (int i = 0; i < arraySize; i++)
    cout << a[i] << " ";
  cout << endl;

  return(0);
}
