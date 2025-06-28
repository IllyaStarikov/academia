#pragma once

#include<iostream>
#include<vector>
using namespace std;

template<class T>
void print_vector(vector<T> v) {
  cout << "[";
  for(T x : v) {
    cout << x << ", ";
  }
  cout << "\b\b]" << endl;
}

