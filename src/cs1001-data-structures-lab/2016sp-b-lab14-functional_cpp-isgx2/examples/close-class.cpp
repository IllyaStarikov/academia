#include<iostream>
#include<functional>
using namespace std;

class Name {
  public:
    Name(const string& the_name) {
      name = the_name;
    }

    function<bool(string)> get_name_matcher() {
      return [this] (string check) {
        return name == check;
      };
    }

  private:
    string name;
};

int main() {
  Name my_name("Nate");
  auto name_matches = my_name.get_name_matcher();

  string input;

  cout << "What is your name? ";
  cin >> input;

  if(name_matches(input)) {
    cout << "Wow, we have the same name!" << endl;
  }
  else {
    cout << "You are definitely not me." << endl;
  }

  return 0;
}
