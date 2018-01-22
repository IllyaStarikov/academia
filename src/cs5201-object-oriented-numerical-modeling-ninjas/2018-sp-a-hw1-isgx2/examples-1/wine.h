#ifndef WINE_H
#define WINE_H

#include<iostream>
using namespace std;

#include "yeast.h"
#include "additives.h"

template<class T>
class Wine
{
  public:
    Wine() {};
    void Drink();
    void Brew();
  private:
    T m_type;
    Yeast m_yeast;
    Additive m_additive;
};
#include "wine.hpp"

#endif

