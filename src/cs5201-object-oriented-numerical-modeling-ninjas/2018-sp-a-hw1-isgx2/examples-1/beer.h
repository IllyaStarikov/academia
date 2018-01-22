#ifndef BEER_H
#define BEER_H

#include"yeast.h"
#include"hops.h"
#include"grains.h"

class Beer
{
  public:
    Beer() {};
    void Drink();
    void Brew();
  private:
    Yeast m_yeast;
    Hops m_hops;
    Grain m_grain;
    float m_sugar;
};

#endif
