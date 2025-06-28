#include<iostream>
#include<algorithm>
#include<vector>
#include"print_vector.h"
using namespace std;

int main() {
  auto nums = vector<int>({1,3,2,6,5,4,1,8,6,8,3});

  cout << "Original:   ";
  print_vector(nums);

  cout << "Ascending:  ";
  sort(nums.begin(), nums.end());
  print_vector(nums);

  cout << "Descending: ";
  sort(nums.begin(), nums.end(), [] (int x, int y) { return x > y; });
  print_vector(nums);
  return 0;
}
