//
//  interpolation-function.h
//  src
//
//  Created by Illya Starikov on 03/12/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#ifndef interpolation_function_h
#define interpolation_function_h

#include <functional>

template <class T>
class InterpolationFunction {
private:
    std::function<T(T x)> function;

public:
    InterpolationFunction(const std::function<T(T x)>& function): function(function) {}

    InterpolationFunction() = default;
    InterpolationFunction<T>& operator=(const InterpolationFunction<T>& other);
    InterpolationFunction<T>& operator=(const InterpolationFunction<T>&& other);
    InterpolationFunction(const InterpolationFunction& other): function(other.function) {}
    InterpolationFunction(const InterpolationFunction&& other): function(std::move(other.function)) {}

    T operator()(const T& x);
};

#include  "interpolation-function.hpp"

#endif /* interpolation-function_h */

