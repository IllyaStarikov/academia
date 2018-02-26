//
//  interpolation-exception.cpp
//  exceptions
//
//  Illya Starikov, Section 1A, 18083141
//  cs5201 – Object Oriented Numerical Modeling
//

#include "interpolation-exception.h"

/**
 *  @brief  Construct an error object from an errorMessage.
 *
 *  @param  errorMessage The error message that corresponds to the improper
 *          dataset.
 *
 *  @pre    None.
 *  @post   See `brief`.
 **/
ImproperDataset::ImproperDataset(const std::string errorMessage) {
    this -> errorMessage = errorMessage;
}

/**
 *  @brief  Generate a string description of the error object.
 *
 *  @return A string description of the error object.
 *
 *  @pre    None.
 *  @post   See `return`.
 **/
const std::string ImproperDataset::what() const {
    return "Improper dataset fed into Interpolation, error message: " + errorMessage;
}
