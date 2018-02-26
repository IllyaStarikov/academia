//
//  vector-exception.cpp
//  exceptions
//
//  Illya Starikov, Section 1A, 18083141
//  cs5201 – Object Oriented Numerical Modeling
//

#include "vector-exception.h"


/**
 *  @brief  Construct an error object representing
 *  an OutOfBounds error with index @p index.
 *
 *  @param  index The improper index.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
OutOfBounds::OutOfBounds(const int index) {
    this -> index = index;
}

/**
 *  @brief  Generate a string description of the error object.
 *
 *  @return A string description of the error object.
 *
 *  @pre    None.
 *  @post   See `return`.
 **/
const std::string OutOfBounds::what() const {
    auto ss = std::stringstream();
    ss << "Trying to reach out of bounds with index " << this -> index << ".";

    return ss.str();
}
