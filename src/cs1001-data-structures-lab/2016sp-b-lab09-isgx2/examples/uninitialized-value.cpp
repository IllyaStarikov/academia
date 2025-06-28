#include<iostream>
using namespace std;

int main()
{
  cout << "Stack uninitialized value" << endl;
  int x;
  if(x > 5)
  {
    cout << "> 5" << endl;
  }

  cout << "Heap uninitialized value" << endl;
  int* y = new int;
  if(*y < 5)
  {
    cout << "< 5" << endl;
  }

  delete y;

  return 0;
}
