#include<iostream>
#include<tuple>
using namespace std;

tuple<int,int> divide(int divisor, int dividend) {
  return make_pair(divisor / dividend, divisor % dividend);
}

int main() {
  int quotient, remainder;
  tie(quotient, remainder) = divide(13,5);
  cout << "13 / 5 = " << quotient
       << " with remainder " << remainder << endl;

  return 0;
}