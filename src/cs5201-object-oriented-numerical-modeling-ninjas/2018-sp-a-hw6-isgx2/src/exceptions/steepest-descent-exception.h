//
//  vector-exception.h
//  exceptions
//
//  Illya Starikov, Section 1A, 18083141
//  cs5201 – Object Oriented Numerical Modeling
//

#ifndef steepest_descent_exception_h
#define steepest_descent_exception_h

#include <string>
#include <sstream>


/** @class NonDiagonallyDominantMatrixError
 *
 *  @brief An error object to represent a Non Diagonally Dominant Matrix.
 *
 **/


class NonDiagonallyDominantMatrixError {
public:
    const std::string what() const;
};

#endif /* vector_exception_h */

