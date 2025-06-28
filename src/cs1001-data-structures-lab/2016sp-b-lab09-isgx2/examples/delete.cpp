#include<iostream>
using namespace std;

int main()
{
  cout << "Double delete" << endl;
  int* x = new int;
  delete x;
  delete x;

  cout << "Invalid delete" << endl;
  int* arr1 = new int[5];
  int* arr2 = arr1 + 1;
  delete arr2;

  cout << "Mismatched delete" << endl;
  int* arr3 = new int[5];
  delete arr3;

  return 0;
}