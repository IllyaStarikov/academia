//
//  interpolation-function.hpp
//  src
//
//  Created by Illya Starikov on 03/12/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#ifndef interpolation_function_hpp
#define interpolation_function_hpp


/**
 *  @brief  Construct an InterpolationFunction from @p other via copying.
 *
 *  @param  other The InterpolationFunction to move data from.
 *
 *  @return A reference to the current InterpolationFunction.
 *
 *  @pre    None.
 *  @post   See `return`.
 **/
template<typename T>
InterpolationFunction<T>& InterpolationFunction<T>::operator=(const InterpolationFunction<T>& other) {
    this -> function = other.function;
}

/**
 *  @brief  Construct an InterpolationFunction from @p other via move semantics.
 *
 *  @param  other The InterpolationFunction to move data from.
 *
 *  @return A reference to the current InterpolationFunction.
 *
 *  @pre    None.
 *  @post   See `return`.
 **/
template<typename T>
InterpolationFunction<T>& InterpolationFunction<T>::operator=(const InterpolationFunction<T>&& other) {
    this -> function = std::move(other.function);
}

/**
 *  @brief  Evaluate the interpolation function at a point @p x.
 *
 *  @param  x The point to the evaluate the function at.
 *
 *  @return The value at the interpolation function.
 *
 *  @pre    None.
 *  @post   See `return`.
 **/
template<typename T>
T InterpolationFunction<T>::operator()(const T& x) {
    return function(x);
}

#endif /* interpolation-function_hpp */

