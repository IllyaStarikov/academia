//
//  gaussian-exception.cpp
//  exceptions
//
//  Created by Illya Starikov on 03/31/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#include "gaussian-exception.h"

/**
 *  @brief  Generate a string description of the error object.
 *
 *  @return A string description of the error object.
 *
 *  @pre    None.
 *  @post   See `return`.
 **/
const std::string SingularMatrixError::what() const {
    return "Matrix is singular.";
}
