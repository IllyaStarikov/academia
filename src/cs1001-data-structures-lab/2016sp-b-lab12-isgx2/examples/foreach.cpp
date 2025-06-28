#include<iostream>
using namespace std;

int main() {
  int nums[] = {1,2,3,4,5,6};

  for(auto i : nums) {
    cout << i * i << endl;
  }

  for(auto i = begin(nums); i != end(nums); i++) {
    cout << (*i) * (*i) << endl;
  }
  return 0;
}
