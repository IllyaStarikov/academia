//
//  move-time-calculator.h
//  Desktop
//
//  Created by Illya Starikov on 04/03/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#ifndef move_time_calculator_h
#define move_time_calculator_h

#include <cmath>

namespace ChessEngine {
    class MoveTimeCalculator {
    public:
        double operator()(const int &moveNumber, const double& timeRemaining);
    };
}

#endif /* move-time-calculator_h */

