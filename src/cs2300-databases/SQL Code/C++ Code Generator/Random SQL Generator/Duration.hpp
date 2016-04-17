//
//  Duration.hpp
//  Random SQL Generator
//
//  Created by Illya Starikov on 4/17/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#ifndef Duration_hpp
#define Duration_hpp

#include "Constants.h"

struct Duration {
    int hours, minutes;
    
    Duration();
    Duration(int _hours, int _minutes);
    
    Duration randomDuration();
    friend std::ostream& operator<< (std::ostream & out, Duration const& duration);
    int totalMinutes();
};

#endif /* Duration_hpp */
