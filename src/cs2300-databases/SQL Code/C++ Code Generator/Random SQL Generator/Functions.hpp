//
//  Functions.hpp
//  Random SQL Generator
//
//  Created by Illya Starikov on 4/10/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#ifndef Functions_hpp
#define Functions_hpp

#include <iostream>
#include <fstream>
#include <sstream>

#include "Constants.h"
int randomArbitrary(const int floor, const int ceiling) {
    return floor + rand() % (ceiling - floor + 1);
}

std::string importFromFile(const std::string filename, const int lineNumber);


std::string sqlDate() {
    std::ostringstream ss;
    
    // YEAR
    ss << randomArbitrary(START_YEAR, CURRENT_YEAR);
    ss << DELIMITER;
    
    ss << 
    
    
    return ss.str();
}


#endif /* Functions_hpp */
