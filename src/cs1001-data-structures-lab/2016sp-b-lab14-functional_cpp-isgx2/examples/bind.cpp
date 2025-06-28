#include<vector>
#include<functional>
#include<algorithm>
#include"print_vector.h"
using namespace std;
using namespace std::placeholders;

int power(int base, int exponent) {
  int ret = 1;
  for(int i = 0; i < exponent; i++) {
    ret *= base;
  }
  return ret;
}

int main() {
  vector<int> n = {0,1,2,3,4,5,6,7,8,9};

  auto square_func = bind(power,_1,2);
  auto power_of_2_func = bind(power,2,_1);

  vector<int> squares(n);
  transform(squares.begin(),squares.end(),squares.begin(),square_func);

  vector<int> powers_of_2(n);
  transform(n.begin(),n.end(),powers_of_2.begin(),power_of_2_func);

  print_vector(n);
  print_vector(squares);
  print_vector(powers_of_2);

  return 0;
}
