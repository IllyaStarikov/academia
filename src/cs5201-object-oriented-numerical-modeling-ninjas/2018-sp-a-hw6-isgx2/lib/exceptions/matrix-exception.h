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

class BandedMatrixDimensionError {
public:
	const std::string what() const;
};

class NonSquareMatrixError {
public:
	const std::string what() const;
};

class NonSymmetricMatrixError {
public:
	const std::string what() const;
};
#endif /* matrix-exception_h */

