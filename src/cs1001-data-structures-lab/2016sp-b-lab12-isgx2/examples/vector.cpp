#include<iostream>
#include<vector>
using namespace std;

int main() {
  vector<int> v;
  for(int i = 0; i < 10; i++) {
    v.push_back(i);
  }

  v.insert(v.begin() + 4, 200);

  for(vector<int>::iterator it = v.begin(); it != v.end(); it++) {
    cout << *it << endl;
  }
  return 0;
}