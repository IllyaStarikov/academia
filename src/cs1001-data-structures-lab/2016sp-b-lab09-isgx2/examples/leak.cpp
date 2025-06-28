#include<iostream>
using namespace std;

struct List
{
  int value;
  List* next;
};

int main()
{
  List l;
  l.value = 5;
  l.next = new List;

  l.next->value = 6;
  l.next->next = new List;

  //delete l.next->next;
  //delete l.next;

  return 0;
}