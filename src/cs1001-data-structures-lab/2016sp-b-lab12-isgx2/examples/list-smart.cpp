#include<iostream>
#include"list-shared.h"
#include<memory>
using namespace std;

shared_ptr<Cell<int> > bigger_than(int x) {
  List<int> l;
  for(int i = 0; i < 100; i++) {
    l.append(i);
  }
  auto it = l.iterator();
  while(it != NULL && it->elem < x) {
    it = it->next;
  }
  return it; // Not freed by list's destructor!
}

int main() {
  auto bigger = bigger_than(50);

  while(bigger) {
    cout << bigger->elem << endl;
    bigger = bigger->next;
  }

  return 0;
}