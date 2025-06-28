#include<iostream>
#include<functional>
using namespace std;

int main() {
  function<void()> hello = [] () {
    cout << "Hello World" << endl; 
  };
  hello();

  [] () {
    string name;
    cout << "Who are you? ";
    cin >> name;
    cout << "Goodbye " << name << endl;
  }();

  return 0;
}