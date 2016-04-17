//
//  main.cpp
//  Random SQL Generator
//
//  Created by Illya Starikov on 4/10/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#include <iostream>

#include "Groups.hpp"
#include "Functions.hpp"
#include "Constants.h"



int main(int argc, const char * argv[]) {
    Group group[GROUP_COUNT];
    
    group[0].printInsert();
    for (int i = 0; i < GROUP_COUNT; i++) {
        group[i].printAttributes(i == GROUP_COUNT - 1);
    }
}
