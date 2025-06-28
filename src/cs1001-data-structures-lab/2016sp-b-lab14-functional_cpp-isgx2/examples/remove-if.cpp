#include<iostream>
#include<vector>
#include<algorithm>
#include"print_vector.h"
using namespace std;

int main() {
  vector<int> n = {1,2,3,4,5,6,7,8,9};
  print_vector(n);

  auto end = remove_if(
      n.begin(),
      n.end(),
      [] (auto x) { return x % 2 == 0; }
    );

  n.erase(end,n.end());

  print_vector(n);

  return 0;
}