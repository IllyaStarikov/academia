#ifndef ADDITIVES_H
#define ADDITIVES_H

#include<iostream>
using namespace std;

class Additive
{
  public:
    Additive() {};
    void someFunc();
    int someOtherFunc();
  private:
    string m_name;
    int m_type;
};

#endif
