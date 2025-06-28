#include<iostream>
using namespace std;

struct List
{
  int value;
  List* next;
};

void printList(List* l)
{
  while(l != NULL)
  {
    cout << l->value << endl;
    l = l->next;
  }
}

void appendTen(List* l)
{
  for(unsigned int i = 0; i < 10; i++)
  {
    l->next = new List;
    l = l->next;
    l->value = i + 1;
    l->next = NULL;
  }
}

void deleteWithDelete(List* list) {
    List *temp = list -> next;
    
    while  (temp != NULL) {
      // duplicate
      list -> next = temp -> next;
      
      delete temp;
      temp = NULL;
      temp = list -> next;
    }
}

int main()
{
  List l;
  l.value = 5;
  
  l.next = new List;
  l.next->value = 6;
  
  l.next -> next = nullptr;
  
  printList(&l);
  cout << "\nAdding some numbers...\n";

  appendTen(l.next -> next);

  printList(&l);

  deleteWithDelete(&l);
//  printList(&l);
  return 0;
}