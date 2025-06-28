//
//  move-time-calculator.cpp
//  Desktop
//
//  Created by Illya Starikov on 04/03/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#include "move-time-calculator.h"

double MoveTimeCalculator::operator()(const int &moveNumber, const double& timeRemaining) {
    static const double a = 0.06;
    static const double b = 70.0;
    static const double c = 25;

    return timeRemaining * a * (0.1 + std::exp(-std::pow(moveNumber - b, 2)/(2 * c * c)));
}

