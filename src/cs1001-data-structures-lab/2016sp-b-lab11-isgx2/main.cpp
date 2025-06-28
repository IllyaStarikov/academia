#include<iostream>
#include"list.h"
using namespace std;

int main()
{
  List<int> l;
  for(int i = 0; i < 10; i++)
  {
    l.append(i);
  }

  l.pop();

  Cell<int>* it = l.iterator();
  while(it != NULL)
  {
    cout << it->elem << endl;
    it = it->next;
  }
  return 0;
}

