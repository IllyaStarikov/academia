#include<iostream>
#include<tuple>
using namespace std;

int main() {
  tuple<int,int,string> coord_name(2,4,"A");

  cout << get<2>(coord_name) << ": ("
       << get<0>(coord_name) << "," 
       << get<1>(coord_name) << ")\n";

  int x, y;
  tie(x, y, ignore) = coord_name;
  cout << "(" << x << "," << y << ")\n";
  return 0;
}