#include<iostream>
using namespace std;

int main()
{
  int* x = new int[5];
  for(int i = 0; i < 5; i++)
  {
    x[i] = i;
  }

  int* y = x+1;

  delete [] x;

  cout << *y << endl;

  return 0;
}
