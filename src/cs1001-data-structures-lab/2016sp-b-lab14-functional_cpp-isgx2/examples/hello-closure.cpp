#include<iostream>
#include<functional>
using namespace std;

int main() {
  string name = "bob";

  auto get_name = [&] () {
    cout << "Who are you? ";
    cin >> name;
  };

  get_name();
  cout << "Goodbye " << name << endl;

  return 0;
}