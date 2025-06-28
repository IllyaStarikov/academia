// filter.cpp - Filter commented-out lines from STDIN
// Written by Nathan Jarus
// 2015-01-27  Initial program

#include<iostream>

using namespace std;

bool matches_with_whitespace(const string& str, const char match) {
  for(unsigned int i = 0; i < str.length(); i++) {
    // Look for the match
    if(str[i] == match) {
      return true;
    }
    // Skip over whitespace 
    else if(!(str[i] == ' ' || str[i] == '\t')) {
      return false;
    }
  }

  // Blank or empty strings don't match
  return false;
}

int main(int argc, char** argv) {
  string buf;
  char match;

  cin >> match;
  
  while(getline(cin, buf)) {
    if(!matches_with_whitespace(buf, '#') {
      cout << buf << endl;
    }
  }

  return 0;
}

