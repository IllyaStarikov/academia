//
//  timer.h
//  Desktop
//
//  Created by Illya Starikov on 04/03/18.
//  Copyright 2018. Illya Starikov. All rights reserved.
//

#ifndef timer_h
#define timer_h

#include <chrono>

class Timer {
    std::chrono::steady_clock::time_point begin;
    std::chrono::steady_clock::time_point end= std::chrono::steady_clock::now();

public:
    void start();
    void stop();

    double elapsed();
};

#endif /* timer_h */

