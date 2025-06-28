//
//  location_hpp
//  homework-10
//
//  Created by Illya Starikov on 4/18/17.
//  Copyright © 2017 Illya Starikov. All rights reserved.
//

#include "location.hpp"

Point::Point(const int x, const int y) {
    this -> x = x;
    this -> y = y;
}

Point::Point() {
    x = 0;
    y = 0;
}

Point& Point::operator=(const Point& rhs) {
    if (this != &rhs) {
        x = rhs.x;
        y = rhs.y;
    }

    return *this;
}
