//
//  chebyshev-node-generator.h
//  src
//
//  Created by Illya Starikov on 02/27/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#ifndef chebyshev_node_generator_h
#define chebyshev_node_generator_h

#include <math.h>
#include <functional>
#include <ostream>

#include "polynomial-interpolation.h"

/** @class ChebyshevNodeGenerator
 *
 *  @brief A functor that calculates the Chebyshev Polynomial nodes.
 *
 *  @tparam T must have the following operations defined:
 *  - Addition (`+`)
 *  - Subtraction (`-`)
 *  - Multiplication (`*`)
 *  - Division (`/`)
 *  - Equal To (`==`)
 *  - Negation (`-T`)
 **/

template <class T>
class ChebyshevNodeGenerator {
private:
    static constexpr const auto nodeGenerator = [=](const int nodeNumber, const int numberOfNodes) {
        auto N = numberOfNodes;
        auto K = nodeNumber;

        return cos((2.0*K + 1)/(2.0*N) * M_PI);
    };

public:
    std::vector<std::pair<T, T>> operator()(const int numberOfNodes, const std::function<T(T x)>& function);

    template<typename S>
    friend std::ostream& operator<<(std::ostream& os, const ChebyshevNodeGenerator<S>& object);
};

#include "chebyshev-node-generator.hpp"

#endif /* chebyshev_node_generator_h */

