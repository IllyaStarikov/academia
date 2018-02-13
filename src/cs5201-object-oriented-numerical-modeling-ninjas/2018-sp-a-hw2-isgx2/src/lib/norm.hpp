//
//  norm.hpp
//  lib
//
//  Created by Illya Starikov on 02/12/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#ifndef norm_hpp
#define norm_hpp

/* @brief Calculates the 1-Norm over a set of polar pairs.
 *
 * @param objects The polar pairs to calculate the 1-Norm
 *        over.
 *
 * @return The sum of the magnitudes of @p objects.
 *
 * @pre None.
 * @post See `return`.
 * */
template <class R, class Theta>
R PolarPairNorm<R, Theta>::operator() (const std::vector<PolarPair<R, Theta>>& objects) const {
    R total = 0.0;

    for (const auto& element : objects)  {
        total += ~element;
    }

    return total;
}

#endif /* norm_hpp */

