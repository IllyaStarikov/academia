// Programmer: Illya Starikov
// Section: 3E
// File: Array.h
// Description: To calculate with arrays.

#ifndef Lab13_H
#define  Lab13_H

/*
Array_Class(T m_0, T m_1, T m_2, T m_3)
Description:    Constructor to take 4 items in and assign them.
Pre-Condition:  Have four members of the same type.
Post-Condition: Constructed.
*/

/*
Array_Class(T m_array[])
Description:    To construct based off an array that is passed.
Pre-Condition:  An array must be passed of size 4.
Post-Condition: An array is assigned.
*/

/*
Array_Class()
Description:    Default construction.
Pre-Condition:  None.
Post-Condition: A default constructor is called, and the member
variables are 0.
*/

/*
Array_Class<T> operator *= (const Array_Class<T> & rhs);
Description:
Pre-Condition:
Post-Condition:
*/

/*
friend Array_Class<S> operator + (const Array_Class<S> & lhs,
const Array_Class<S> & rhs);
Description:    Overloading the + operator to add two array classes.
Pre-Condition:  Two objects.
Post-Condition: A returned object that is the two added values.
*/

/*
friend ostream & operator<< (ostream & stream, const Array_Class<S>
    &array);
Description:    Overload the << to output items easily.
Pre-Condition:  None.
Post-Condition: Ouputs items to streams.
*/
using namespace std;

template <class T>
class Array_Class
{
private:
    T m[4];
public:
    Array_Class(T m_0, T m_1, T m_2, T m_3);
    Array_Class(T m_array[]);
    Array_Class();

    Array_Class<T> operator *= (const Array_Class<T> & rhs);
    template <class S>
    friend Array_Class<S> operator + (const Array_Class<S> & lhs,
        const Array_Class<S> & rhs);
    template <class S>
    friend ostream & operator<< (ostream & stream,
        const Array_Class<S> &array);
};
#include "Array.hpp"

#endif