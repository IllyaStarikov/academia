#include<iostream>
#include<memory>
using namespace std;
int main() {
  shared_ptr<int> sp(new int);
  *sp = 5;
  shared_ptr<int> sp2(new int(3));

  cout << *sp << " " << *sp2 << endl;
  cout << sp.use_count() << endl;

  sp = sp2;

  cout << *sp << " " << *sp2 << endl;
  cout << sp.use_count() << endl;

  return 0;
}