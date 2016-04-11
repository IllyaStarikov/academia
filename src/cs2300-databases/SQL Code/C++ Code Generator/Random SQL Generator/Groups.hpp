//
//  Groups.hpp
//  Random SQL Generator
//
//  Created by Illya Starikov on 4/10/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#ifndef Groups_hpp
#define Groups_hpp

#include <stdio.h>
#include <iostream>

#include "Functions.hpp"
#include "Constants.h"

class Group  {
    std::string title, startDate;
    
    Group(const int numberToGetNameFrom) {
        title = importFromFile(GROUPS, numberToGetNameFrom);

    }
};

#endif /* Groups_hpp */
