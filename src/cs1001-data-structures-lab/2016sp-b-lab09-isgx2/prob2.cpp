#include<iostream>
using namespace std;

class plain
{
  public:
  plain()
  {
    ptr = new int;
  }

  int* ptr;
};

class dtor
{
  public:
  dtor()
  {
    ptr = new int;
  }

  ~dtor()
  {
    delete ptr;
  }

  int* ptr;
};

int main()
{
  plain* plain_var = new plain;
  plain* plain_array = new plain[5];

  dtor* dtor_var = new dtor;
  dtor* dtor_array = new dtor[5];

//  int* segfault = 0;
  //cout << *segfault << endl;

  return 0;
}
