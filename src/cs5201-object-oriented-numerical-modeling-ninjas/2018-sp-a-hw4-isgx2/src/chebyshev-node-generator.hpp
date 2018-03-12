//
//  chebyshev-node-generator.cpp
//  src
//
//  Created by Illya Starikov on 02/27/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//


/**
 *   @brief  The node generating function.
 *
 *   @return An `std::vector` of `std::pair`s of the form (x, y).
 *
 *   @pre None.
 *   @post See `return`.
 **/
template <typename T>
std::vector<std::pair<T, T>> ChebyshevNodeGenerator<T>::operator()(const int numberOfNodes, const std::function<T(T x)>& function) {
    auto points = std::vector<std::pair<T, T>>();

    for (int i = 0; i < numberOfNodes; i++) {
        auto point = nodeGenerator(i, numberOfNodes);
        points.push_back(std::make_pair(point, function(point)));
    }

    return points;
}

/**
 *  @brief Insert a string description of a Chebyshev Node Generator into a stream.
 *
 *  @param os The stream to put a string description of the Chebyshev Node Generator into.
 *
 *  @param object The Chebyshev Node Generator to generate a string description from.
 *
 *  @return The stream with the string description of the @p object in it.
 *
 *  @pre None.
 *  @post See `return`.
 **/
template<typename S>
std::ostream& operator<<(std::ostream& os, const ChebyshevNodeGenerator<S>& object) {
    (void)object;
    os << "ChebyshevNodeGenerator(x)";

    return os;
}

