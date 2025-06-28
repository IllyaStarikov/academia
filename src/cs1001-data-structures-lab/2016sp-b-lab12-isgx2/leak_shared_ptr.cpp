#include <iostream>
#include <memory>

using namespace std;

struct List
{
  int value;
  shared_ptr<List> next;
};

void printList(shared_ptr<List> l)
{
  while(l != NULL)
  {
    cout << l->value << endl;
    l = l->next;
  }
}

void appendTen(shared_ptr<List> l)
{
  for(unsigned int i = 0; i < 10; i++)
  {
    l->next = shared_ptr<List>(new List);
    l = l->next;
    l->value = i + 1;
    l->next = nullptr;
  }
}

int main()
{
  auto l = shared_ptr<List>(new List);
  l->value = 5;
  
  l->next = shared_ptr<List>(new List);
  l->next -> value = 6;
  l->next -> next = nullptr;

  
  printList(l);
  cout << "\nAdding some numbers...\n";
  
  appendTen(l -> next);
  printList(l);
  
  return 0;
}
