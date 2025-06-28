#include<iostream>
using namespace std;

int main()
{
  cout << "Invalid write" << endl;
  int *arr = new int[5];
  for(int i = 0; i <= 5; i++)
  {
    arr[i] = i;
  }

  cout << "Invalid read" << endl;
  for(int i = 0; i <= 5; i++)
  {
    cout << arr[i] << endl;
  }

  delete[] arr;

  return 0;
}
