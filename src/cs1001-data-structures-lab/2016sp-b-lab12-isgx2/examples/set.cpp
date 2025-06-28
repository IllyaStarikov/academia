#include<iostream>
#include<set>
using namespace std;
int main() {
  set<int> nums;
  for(int i = 1; i < 10; i++) {
    nums.insert(i);
    nums.insert(i-1);
  }

  if(nums.find(3) != nums.end()) {
    cout << "nums contains 3" << endl;
  }
  if(nums.find(42) == nums.end()) {
    cout << "nums does not contain 42" << endl;
  }
  return 0;
}