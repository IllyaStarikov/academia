#include"person.h"
#include <algorithm>
#include <numeric>
#include <iostream>
using namespace std;

template<class T, class Func>
bool any(vector<T> v, Func pred) {
    return accumulate(v.begin(), v.end(), false, 
    [&] (bool acc, T val) { return acc || pred(val); } );
}

int main() {
    vector<Person> people = get_people();
    
    auto comparable = [](auto left, auto right) { return left.name() < right.name(); };
    
    auto toUpperFirstChar = [](string str) {
        auto mutableStr = str;
        mutableStr[0] = toupper(str[0]);
        return mutableStr;
    };
    
    auto promptForName = []() {
        string name;
        cout << "User Requested: ";
        cin >> name;
        return Person(name, 42);
    };
    
    for(auto p: people) {
        cout << p.name() << endl;
    }
    
    sort(people.begin(), people.end(), comparable );
    
    transform(people.begin(), people.end(), people.begin(), [=](auto x) {
        return Person(toUpperFirstChar(x.name()), x.age());
    });
    
    auto searchFor = promptForName();
    auto isEqual = [](auto l, auto r) { return l == r; };
    
    if (any(people, bind(isEqual, searchFor, std::placeholders::_1))) {
        cout << "Name Exists\n";
    } else {
        cout << "Name Doesn't Exist\n";
    }
    
    return 0;
}