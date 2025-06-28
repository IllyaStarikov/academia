//
//  functions.hpp
//  homework-10
//
//  Created by Illya Starikov on 4/13/17.
//  Copyright © 2017 Illya Starikov. All rights reserved.
//

#ifndef functions_hpp
#define functions_hpp

#include <stdlib.h>

// Description: Generates a random number with the type of second parameter.
// Pre:         The comparison operator must be defined for lower and upper,
// and because they are different types, they must be comperable.
// Types must be able to have modulus arithmetic operations
// performed on them. (I.e. integer is fine, floating point
//                    is not).
// Post:        A random number will be returned with bounds lower <= x <= upper.
// If lower is higher than upper, 0 will be returned.

template<typename T, typename S>
S randomArbitrary(const T lower, const S upper)
{
    return (lower > upper) ? 0 : lower + rand() % (upper - lower + 1);
}

bool randomChoiceBasedOnProbability(const int probability);

#endif /* functions_hpp */
