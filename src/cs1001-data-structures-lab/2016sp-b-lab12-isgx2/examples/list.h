#ifndef LIST_H
#define LIST_H

#include<stdexcept>
using namespace std;

template<class T>
struct Cell
{
  T elem;
  Cell* next;

  Cell(const T& t, Cell* n);
  Cell(const Cell& c);
};

template<class T>
class List
{

  public:
    // Constructor
    List();

    // Copy Constructor
    List(const List& l);

    // Destructor
    ~List();

    // Inserting stuff
    void prepend(const T& t);
    void append(const T& t);

    void extend(const List& l);

    // Removing stuff
    void pop();

    // Accessors
    T& head(); // First element
    List tail(); // Everything except the first element

    Cell<T>* iterator();

    // Properties
    unsigned int length() const;
    bool empty() const;

  private:
    Cell<T>* cell;
};

#include"list.hpp"
#endif