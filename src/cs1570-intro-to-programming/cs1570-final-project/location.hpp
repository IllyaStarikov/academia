//
//  location_hpp
//  homework-10
//
//  Created by Illya Starikov on 4/13/17.
//  Copyright © 2017 Illya Starikov. All rights reserved.
//

#ifndef location_hpp
#define location_hpp

struct Location {
    char cell;
    bool exchangedPants;
};

class Point {
public:
    int x, y;

    Point(const int x, const int y);
    Point();

    Point& operator=(const Point& rhs);
};

#endif /* location_hpp */
