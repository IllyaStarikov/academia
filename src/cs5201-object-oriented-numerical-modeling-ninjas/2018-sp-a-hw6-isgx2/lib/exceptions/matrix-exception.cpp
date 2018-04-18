//
//  vector-exception.cpp
//  exceptions
//
//  Illya Starikov, Section 1A, 18083141
//  cs5201 – Object Oriented Numerical Modeling
//

#include "matrix-exception.h"

const std::string BandedMatrixDimensionError::what() const {
    return "Banded Matrix must be of dimension 3.";
}

const std::string NonSquareMatrixError::what() const {
    return "Matrix dimensions (row x column) must be equal.";
}

const std::string NonSymmetricMatrixError::what() const {
    return "Matrix dimensions (row x column) must be equal.";
}