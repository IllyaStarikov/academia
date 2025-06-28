#include<iostream>
#include"list.h"
using namespace std;

Cell<int>* bigger_than(int x) {
  List<int> l;
  for(int i = 0; i < 100; i++) {
    l.append(i);
  }
  Cell<int>* it = l.iterator();
  while(it != NULL && it->elem < x) {
    it = it->next;
  }
  return it; // List's destructor frees this!
}

int main() {
  Cell<int>* bigger = bigger_than(50);

  while(bigger) {
    cout << bigger->elem << endl;
    bigger = bigger->next;
  }

  return 0;
}