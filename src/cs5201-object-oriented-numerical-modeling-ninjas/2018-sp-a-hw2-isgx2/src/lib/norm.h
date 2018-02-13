//
//  norm.h
//  lib
//
//  Created by Illya Starikov on 02/01/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#ifndef norm_h
#define norm_h

/** @class PolarPair
 *
 *  @brief A functor class to calculate 1-Norm for a set of polar pairs .
 *
 *  @tparam R The modulus type for polar pairs. Must be able to promoted to be
 *          @p Theta or  @p Theta must be able to be promoted to @p R.
 *          I.e., a `double` and a `float` would work or an `int` and a
 *          `double`, but a `char*` and an `int` would not. Must also be
 *          able to support all of the following operations:
 *  - Addition (`+`)
 *  - Subtraction (`-`)
 *  - Multiplication (`*`)
 *  - Division (`/`)
 *  - Less Than (`<`)
 *  - Greater Than (`>`)
 *  - Equal To (`==`)
 *  - Negation (`-R`)
 *
 *  @tparam Theta The argument type for polar pairs. Must be able to be
 *          promoted to  @p Theta or  @p Theta must be able to be promoted
 *          to @p R. I.e., a `double` and a `float` would work or an `int` and a
 *          `double`, but a `char*` and an `int` would not. Must also be
 *          able to support all of the following operations:
 *  - Addition (`+`)
 *  - Subtraction (`-`)
 *  - Multiplication (`*`)
 *  - Division (`/`)
 *  - Less Than (`<`)
 *  - Greater Than (`>`)
 *  - Equal To (`==`)
 *  - Negation (`-R`) */


#include <vector>
#include "polarpair.h"

template <class R, class Theta>
class PolarPairNorm {
public:
    R operator() (const std::vector<PolarPair<R, Theta> >& objects) const;
};

#include "norm.hpp"

#endif /* norm_h */

