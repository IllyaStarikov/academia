#include<iostream>
#include<string.h>

#include"vector.h"
using namespace std;

int main()
{
  Vector<char*> lines;
  char* buf = new char[100];
  unsigned int length = 0;
  unsigned int totalLines = 0;
  while(cin.getline(buf,100))
  {
    length += strlen(buf);
    totalLines++;
    
    cout << length / totalLines << endl;
  }
  
  delete[] buf;
  return 0;
}