/* @file: abstractqueue.h
 * Definition of templated class queue
 * Implementing A.D.T. Queue
 * @C - Galaxy Express Software
 *
 * Version 15.3.0
 */

/* ____________________
  /                    \
  | AbstractQueue Class |
  \____________________/

    Purpose: Implements a Queue ADT.

    Error Handling: Whenever a function is given invalid parameter values
        it THROWS a 'Oops' object.

*/
#ifndef ABSTRACTQUEUE_H
#define ABSTRACTQUEUE_H

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
	Oops(const string msg) : m_errormsg(msg) {}
	const string& getMsg() const
	{
		return m_errormsg;
	}
};


/* ---------------  Abstract Class AbstractQueue --------------- */
template < typename T >
class AbstractQueue
{
public:
  // Purpose: Checks if a queue is empty
  // Returns: 'true' if the queue is empty
  //     'false' otherwise
  virtual bool isEmpty() const = 0;


  // Purpose: looks at the front of the queue
  // Returns: a reference to the element currently in front of the queue
  // Exception: if the queue is empty, THROW a 'Oops' object with an error message!!!
  virtual const T& front() const throw (Oops) = 0;


  // Purpose: looks at the back of the queue
  // Returns: a reference to the element currently in the back of the queue
  // Exception: if the queue is empty, THROW a 'Oops' object with an error message!!!
  virtual const T& back() const throw (Oops) = 0;


  // Purpose: enqueue an element into the queue
  // Parameters: x is the item to add to the queue
  // Postconditions: x is now the element at the end of the queue,
  virtual void enqueue(const T& x) = 0;


  // Purpose: dequeues
  // Postconditions: the element formerly at the front of the queue has
  //     been removed.
  // Note: Dequeueing an empty queue results in an empty queue.
  virtual void dequeue() = 0;


  // Purpose: clears the queue
  // Postconditions: the queue is now empty
  virtual void clear() = 0;

};

#endif