#ifndef LIST_H
#define LIST_H

#include<stdexcept>
#include<memory>
using namespace std;

template<class T>
struct Cell
{
  T elem;
  shared_ptr<Cell> next;

  Cell(const T& t, shared_ptr<Cell> n);
  Cell(const Cell& c);
};

template<class T>
class List
{

  public:
    // Constructor
    List() { /* empty */ }

    // Copy Constructor
    List(const List& l);

    // Inserting stuff
    void prepend(const T& t);
    void append(const T& t);

    void extend(const List& l);

    // Removing stuff
    void pop();

    // Accessors
    T& head(); // First element
    List tail(); // Everything except the first element

    shared_ptr<Cell<T> > iterator();

    // Properties
    unsigned int length() const;
    bool empty() const;

  private:
    shared_ptr<Cell<T>> cell;
};

#include"list-shared.hpp"
#endif