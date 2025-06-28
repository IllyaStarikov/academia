/* @file: arraylist.h
 * Definition of templated class ArrayList
 * Implementation of the List ADT
 * @C - Galaxy Express Softworks
 *
 * Version 15.3.0
 */

#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <iostream>

/* _________________
 /                 \
 | ArrayList Class |
 \_________________/
 
 Purpose: Implements a List ADT using a dynamically allocated array to
 store the elements of the list
 
 Error Handling: Whenever a function is given invalid parameter values
 the message "!-- ERROR : PANIC in ARRAYLIST!!" and maybe an explanation
 is displayed. The list remains unchanged.
 If such function returns a value this value is the dummy member object 'm_errobj'.
 */


// --------------- Forward Declarations ---------------
template <typename T>                  // the ArrayList class
class ArrayList;

template <typename T>                 // a friend function for output
std::ostream& operator<< (std::ostream& out, const ArrayList<T>& alist);



// ---------------  Class ArrayList Declarations ---------------
template <typename T>
class ArrayList
{
private:
    int m_size;                          // current number of elements
    int m_max;                           // maximum capacity of array m_data
    T* m_data;                           // array to store the elements
    
    T m_errobj;                          // dummy object to return in case of error
    
    
public:
    // Purpose: Default Constructor
    // Postconditions: Current size and maximum size set to 0,
    // and data set to NULL
    // -- INLINE
    ArrayList(): m_size(0), m_max(0), m_data(NULL) {};
    
    /*
     * ---- Big 3 Member Functions ---
     */
    
    // Purpose: Destructor
    // Postconditions: current size and maximum size set to 0,
    //                 data deallocated and set to NULL
    ~ArrayList();
    
    // Purpose: Operator=, performs a deep copy of 'rhs' into 'this' ArrayList
    // Parameters: rhs, ArrayList to be copied
    // Returns: *this
    // Postconditions: rhs == this
    ArrayList<T>& operator=(const ArrayList<T>& rhs);
    
    // Purpose: Copy Constructor
    // Parameters: cpy = ArrayList to be copied
    // Postconditions: current size, maximum size, and elements same as cpy
    ArrayList(const ArrayList<T>& cpy);
    
    
    /*
     * ----- Basic Accessor Operations -----
     */
    
    // Purpose: Accessor function for the number of elements in the list
    // Returns: number of elements in the list
    int size() const;
    
    // Purpose: Accessor function for the max capacity of elements
    // Returns: max capacity of this list
    // -- INLINE
    // ( used for grading purposes )
    int max() const { return m_max; };
    
    // Purpose: Accessor function for the first element of the list
    // Returns: the first element in the list
    const T& first() const;
    
    // Purpose: return a read-and-write reference to the element at
    // the specified position
    // Parameters: i is 0-based index into the ArrayList
    // Returns: the element at position i in the ArrayList
    T& operator[](int i);
    
    // Purpose: return a read-only reference to the element at
    // the specified position
    // Parameters: i is 0-based index into the ArrayList
    // Returns: the element at position i in the ArrayList
    const T& operator[](int i) const;
    
    // Purpose: finds an element in the ArrayList
    // Parameters: x is value to be found in the ArrayList
    // Returns: the position of the first occurrance of x in the list,
    //          or -1  if x is not found.
    int find(const T& x);
    
    
    /*
     * ----- Basic Mutator Operations -----
     */
    
    // Purpose: Clears the ArrayList
    // Postconditions: current size and maximum size set to 0,
    //                 elements are deallocated and data is set to NULL
    void clear();
    
    // Purpose: puts the value x at the end of an ArrayList
    // Parameters: x is value to be added to ArrayList
    // Postconditions: current size is incremented by 1
    //     If max size is reached, a new array of size max*2 is allocated
    //     and data is copied to it.
    void insert_back(const T& x);
    
    // Purpose: puts the value x at the position i in the  ArrayList
    // Parameters: x is value to be added to ArrayList
    //             i is the position to insert x at
    // Postconditions: current size is incremented by 1
    //     If max size is reached, a new array of size max*2 is allocated
    //     and data is copied to it.
    void insert(const T& x, int i);
    
    // Purpose: Removes the element at index i in the array
    // Parameters: i, the index of the element to remove
    // Postconditions: if the size of the list is greater than 0
    //     size is decremented by one.
    //     if the size of the list less than 1/4 the max size, a new array
    //     of size max/2 is allocated, and data is copied to it.
    void remove(int i);
    
    
    /*
     * ----- Complex Mutator Operations ----- */
    
    // Purpose: swaps two elements of the array
    // Parameters: i, k, two positions on the Arraylist
    // Postconditions: the elements at positions i and k swap positions
    void swap(int i, int k);
    
    // Purpose: appends two lists
    // Parameters: alist, a list to appended to the end of 'this' list
    // Postconditions: current size is incremented by size of alist
    //     the elements of alist are appended to the elements of 'this'
    void append(const ArrayList<T>& alist);
    
    // Purpose: removes duplicates from an Arraylist
    // Postconditions: all duplicate elements are removed from the list.
    void purge();
    
    
    /*
     * ----- Complex Accessor Operations -----
     */
    
    // Purpose: prints the ArrayList
    friend std::ostream& operator<< <> (std::ostream& out,
                                        const ArrayList<T>& alist);
};



// BONUS, BONUS, BONUS !!!
// -----------------  Friend Function to Print  -----------------
// Purpose: prints an ArrayList
template <typename T>
std::ostream& operator<< (std::ostream& out, const ArrayList<T>& alist)
{
    out << "[ ";
    for (int i=0; i < alist.m_size; i++){
        out << alist.m_data[i] << ", ";
    } 
    out << "]";
    return out;
}


#include "arraylist.hpp"
#endif