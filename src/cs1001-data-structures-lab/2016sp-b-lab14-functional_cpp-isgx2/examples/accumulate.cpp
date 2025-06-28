#include<iostream>
#include<vector>
#include<numeric>
using namespace std;

int main() {
  vector<int> numbers;
  string buf;
  while(cin >> buf) {
    if(buf == "=") {
      cout << "Total: ";
      cout << accumulate(
          numbers.begin(),
          numbers.end(),
          0,
          [] (int acc, int n) { return n + acc; }
        );

      cout << endl << endl;
      numbers.clear();
    }
    else {
      numbers.push_back(stoi(buf));
    }
  }

  return 0;
}
