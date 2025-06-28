#include<iostream>
#include<map>
#include<string>
using namespace std;

int main() {
  map<string, int> ages;
  ages["rick"] = 70;
  ages["morty"] = 14;

  for(auto it = ages.begin(); it != ages.end(); it++) {
    cout << it->first << " is "
         << it->second << " years old.\n";
  }

  return 0;
}