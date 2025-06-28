#include<iostream>
#include<utility>
using namespace std;

int main() {
  pair<int,int> origin = pair<int,int>(0,0);
  pair<int,int> coord = make_pair(3,5);

  cout << "(" << origin.first << ","
       << origin.second << ")" << endl;
  return 0;
}