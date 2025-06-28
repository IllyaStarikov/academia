/* @file: abstractstack.h
 * Definition of templated class stack
 * Implementing A.D.T. Stack
 * @C - Galaxy Express Software
 *
 * Version 15.3.0
 */

/* ____________________
  /                    \
  | AbstractStack Class |
  \____________________/

    Purpose: Implements a Stack ADT using.

    Error Handling: Whenever a function is given invalid parameter values
        THROWS a 'Oops' object.

*/
#ifndef ABSTRACTSTACK_H
#define ABSTRACTSTACK_H

#include <string>

using namespace std;

/* ---------------  Class 'Oops' ---------------
Class
Thrown when an error is encountered.
Member 'm_msg' stores an error message.
*/
class Oops
{
    string m_errormsg;
public:
    Oops(const string &msg) : m_errormsg(msg) {}
    const string& getMsg() const
    {
        return m_errormsg;
    }
};


/* ---------------  Abstract Class AbstractStack --------------- */
template < typename T >
class AbstractStack
{
public:

  // Purpose: Checks if a stack is empty
  // Returns: 'true' if the stack is empty
  //     'false' otherwise
  virtual bool isEmpty() const = 0;


  // Purpose: looks at the top of the stack
  // Returns: a const reference to the element currently on top of the stack
  // Exception: if the stack is empty, THROW a 'Oops' object with an error message!!!
  virtual const T& top() const throw ( Oops ) = 0;

  // Purpose: push an element into the stack
  // Parameters: x is the value to push into the stack
  // Postconditions: x is now the element at the top of the stack,
  virtual void push(const T& x) = 0;

  // Purpose: pop the stack
  // Postconditions: the element formerly at the top of the stack has
  // been removed
  // Note: Poping an empty stack results in an empty stack.
  virtual void pop() = 0;


  // Purpose: clears the stack
  // Postconditions: the stack is now empty
  virtual void clear() = 0;


  // Purpose: DESTRUCTOR
  virtual ~AbstractStack() {}

};

#endif