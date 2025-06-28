#include<iostream>
using namespace std;

int main()
{
  int* x = new int[5];
  x++;

  /* Current status:
  x -----
        V
  +---+---+---+---+---+
  |   |   |   |   |   |
  +---+---+---+---+---+
  */

  int* segfault = 0;
  cout << *segfault << endl;

  return 0;
}
