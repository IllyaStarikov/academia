#include<iostream>
using namespace std;

void initialize(int* arr, int size)
{
  for(int i = 0; i < size; i++) {
    arr[i] = i;
  }
}

void pretty_print(int* arr, int size)
{
  cout << "[";
  int i = 0;

  for(; i < size; i++)
  {
    cout << arr[i] << ", ";
  }
  cout << arr[i] << "]" << endl;
}

int main()
{
  int* arr = new int[5];
  int *brr;

  initialize(arr, 5);
  initialize(brr, 5);

  pretty_print(arr, 5);
  pretty_print(brr, 5);

  delete arr;
  delete brr;

  return 0;
}