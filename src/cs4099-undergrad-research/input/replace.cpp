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
{
  int x = 1;
  int y = 7;
  int z = 0;
  int a[2] = {1, 2};
  int arraySize = 2;

  for (int i = 0; i < arraySize; i++)
  {
    if (a[i] == x)
    {
      a[i] = z;
    }
    if (a[i] == y)
    {
      a[i] = z;
    }
  }

  // Output results

  for (int i = 0; i < arraySize; i++)
    cout << a[i] << " ";
cout << endl;

  return(0);
}
