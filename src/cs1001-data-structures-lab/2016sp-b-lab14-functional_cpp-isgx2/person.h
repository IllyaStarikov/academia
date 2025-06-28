#include<string>
#include<vector>
using namespace std;

class Person {
  public:
    Person(const string& n, const int a) {
      m_name = n;
      m_age = a;
    }

    string name() const {
      return m_name;
    }

    void name(const string& n) {
      m_name = n;
    }

    int age() const {
      return m_age;
    }

    void age(const int a) {
      m_age = a;
    }
    friend inline bool operator==(const Person &lhs, const Person &rhs){ return lhs.name() == rhs.name(); }
  private:
    string m_name;
    int m_age;
};

vector<Person> get_people() {
  vector<Person> ret;
  ret.push_back(Person("rick", 75));
  ret.push_back(Person("morty", 12));
  ret.push_back(Person("summer", 17));
  ret.push_back(Person("gazorpazorpfield", 3290));
  ret.push_back(Person("bird person", 68));

  return ret;
}
