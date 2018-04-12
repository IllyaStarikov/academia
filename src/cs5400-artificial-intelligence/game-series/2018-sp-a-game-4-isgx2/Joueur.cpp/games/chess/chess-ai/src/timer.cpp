//
//  timer.cpp
//  Desktop
//
//  Created by Illya Starikov on 04/03/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#include "timer.h"

using namespace ChessEngine;

void Timer::start() {
    begin = std::chrono::steady_clock::now();
}

void Timer::stop() {
    end = std::chrono::steady_clock::now();
}

double Timer::elapsed() {
    static const double MILLION = 1000000.0;
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - begin).count() / MILLION;
}

