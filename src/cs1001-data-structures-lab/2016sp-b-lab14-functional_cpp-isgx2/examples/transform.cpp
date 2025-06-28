#include<iostream>
#include<vector>
#include<algorithm>
#include"print_vector.h"
using namespace std;

int main() {
  vector<int> n = {1,2,3,4,5,6};
  print_vector(n);

  transform(
      n.begin(), // Start
      n.end(),   // End
      n.begin(), // Destination
      [] (int x) {return x*x;}
    );
  print_vector(n);

  return 0;
}