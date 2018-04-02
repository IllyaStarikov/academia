//
//  gaussian-solver.h
//  src
//
//  Created by Illya Starikov on 03/30/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#ifndef gaussian_exception_h
#define gaussian_exception_h

#include <string>

/** @class SingularMatrixError
 *
 *  @brief An error to represent an unexpected singular matrix.
 *
 **/
class SingularMatrixError {
    const std::string what() const;
};

#endif /* gaussian-solver_h */

