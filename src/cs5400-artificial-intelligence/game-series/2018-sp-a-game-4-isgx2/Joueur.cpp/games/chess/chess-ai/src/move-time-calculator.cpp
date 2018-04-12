//
//  move-time-calculator.cpp
//  Desktop
//
//  Created by Illya Starikov on 04/03/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#include "move-time-calculator.h"
using namespace ChessEngine;

double MoveTimeCalculator::operator()(const int &moveNumber, const double& timeRemaining) {
    static const double a = 0.035;
    static const double b = 80.0;
    static const double c = 35;

    return timeRemaining * a * (0.1 + std::exp(-std::pow(moveNumber - b, 2)/(2 * c * c)));
}

