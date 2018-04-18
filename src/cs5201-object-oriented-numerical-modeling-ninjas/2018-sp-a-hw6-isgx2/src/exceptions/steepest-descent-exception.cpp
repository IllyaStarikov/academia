//
//  vector-exception.cpp
//  exceptions
//
//  Illya Starikov, Section 1A, 18083141
//  cs5201 – Object Oriented Numerical Modeling
//

#include "steepest-descent-exception.h"


const std::string NonDiagonallyDominantMatrixError::what() const {
	return "Matrix is diagonally dominant."
}