//
//  matrix-exception.h
//  exceptions
//
//  Created by Illya Starikov on 03/27/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#ifndef matrix_exception_h
#define matrix_exception_h

#include "vector-exception.h"
#include <string>

/** @class BandedMatrixDimensionError
 *
 *  @brief An error object to represent a banded matrix of dimension less than three.
 *
 **/
class BandedMatrixDimensionError {
public:
	const std::string what() const;
};

/** @class NonSquareMatrixError
 *
 *  @brief An error object to represent a without matching dimensions.
 *
 **/
class NonSquareMatrixError {
public:
	const std::string what() const;
};

/** @class NonSymmetricMatrixError
 *
 *  @brief An error object to represent a non symmetric matrix.
 *
 **/
class NonSymmetricMatrixError {
public:
	const std::string what() const;
};
#endif /* matrix-exception_h */

