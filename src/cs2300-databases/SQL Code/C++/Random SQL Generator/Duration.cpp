//
//  Duration.cpp
//  Random SQL Generator
//
//  Created by Illya Starikov on 4/17/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#include "Duration.hpp"
#include "Functions.hpp"

Duration::Duration() {
    hours = 0, minutes = 0;
}

Duration::Duration(int _hours, int _minutes) {
    hours = _hours;
    minutes = _minutes;
}

Duration Duration::randomDuration() {
    Duration toReturn(randomArbitrary(1, WORKOUT_MAX_HOURS), randomArbitrary(1, WORKOUT_MAX_MINS));
    return toReturn;
}

std::ostream& operator<< (std::ostream & out, Duration const& duration) {
    out << duration.hours;
    out << ":";
    if (duration.minutes < 10) { out << '0'; }
    out << duration.minutes;
    return out;
}

int Duration::totalMinutes() {
    return (MINUTES_IN_HOUR * hours) + minutes;
}