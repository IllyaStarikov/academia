#ifndef VECTOR_H
#define VECTOR_H

#include<stdexcept> // for invalid_argument
using namespace std;

template<class T>
class Vector
{
  public:
    // Constructor
    Vector();

    // Copy Constructor
    Vector(const Vector<T>& v);

    // Destructor
    ~Vector();

    // Add elements to the vector
    void push_back(T v);

    // Read elements of the vector
    T& operator[](const unsigned int idx);

    // length getter
    unsigned int length() const;

    // size getter
    unsigned int size() const;

  private:
    unsigned int sz;
    unsigned int max;
    T* array;
};

#include"vector.hpp"
#endif
