#include<iostream>
#include<string>
#include"vector.h"
using namespace std;

int main()
{
  string buf;

  while(getline(cin, buf))
  {
    if(buf[0] != '#')
    {
      cout << buf << endl;
    }
  }

  return 0;
}