//
//  vector-exception.h
//  exceptions
//
//  Illya Starikov, Section 1A, 18083141
//  cs5201 – Object Oriented Numerical Modeling
//

#ifndef vector_exception_h
#define vector_exception_h

#include <string>
#include <sstream>


/** @class OutOfBounds
 *
 *  @brief An error object to represent indexing past the bounds.
 *
 **/

class OutOfBounds {
private:
    int index;

public:
    OutOfBounds(const int index);

    OutOfBounds() = delete;
    OutOfBounds(const OutOfBounds& other) = default;
    OutOfBounds(OutOfBounds&& other) = default;
    OutOfBounds& operator=(const OutOfBounds& other) = default;
    OutOfBounds& operator=(OutOfBounds&& other) = default;

    const std::string what() const;
};

/** @class ImproperArgument
 *
 *  @brief An error class to represent an improper argument being passed
 *        into a function.
 *
 *  @tparam T Any object to represent an improper object. Must have the
 *          << operator defined.
 **/

template <class T>
class ImproperArgument {
private:
    T argument;

public:
    ImproperArgument(T argument);

    ImproperArgument() = delete;
    ImproperArgument(const ImproperArgument& other) = default;
    ImproperArgument(ImproperArgument&& other) = default;
    ImproperArgument& operator=(const ImproperArgument& other) = default;
    ImproperArgument& operator=(ImproperArgument&& other) = default;

    const std::string what() const;
};


#include "vector-exception.hpp"

#endif /* vector_exception_h */

