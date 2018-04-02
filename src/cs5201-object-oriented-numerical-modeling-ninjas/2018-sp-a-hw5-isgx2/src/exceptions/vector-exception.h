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

class OutOfBoundsError {
private:
    int index;

public:
    OutOfBoundsError(const int index);

    OutOfBoundsError() = delete;
    OutOfBoundsError(const OutOfBoundsError& other) = default;
    OutOfBoundsError(OutOfBoundsError&& other) = default;
    OutOfBoundsError& operator=(const OutOfBoundsError& other) = default;
    OutOfBoundsError& operator=(OutOfBoundsError&& other) = default;

    const std::string what() const;
};

class MistmatchedDimensionsError {
public:
    const std::string what() const;
};

#endif /* vector_exception_h */

