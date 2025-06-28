#ifndef LIST_H
#define LIST_H

#include<stdexcept>
using namespace std;

template<class T>
struct Cell
{
  T elem;
  Cell* next;

  Cell(T& t, Cell* n);
  Cell(Cell& c);
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
    void prepend(T& t);
    void append(T& t);

    void extend(const List& l);

    // Removing stuff
    void pop();

    // Accessors
    T& head();
    List tail();

    Cell<T>* iterator();

    // Properties
    unsigned int length() const;
    bool empty() const;

  private:
    Cell<T>* cell;
};

#include"list.hpp"
#endif