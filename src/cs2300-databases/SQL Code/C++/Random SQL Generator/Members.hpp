//
//  Members.hpp
//  Random SQL Generator
//
//  Created by Illya Starikov on 4/26/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#ifndef Members_hpp
#define Members_hpp

#include <stdio.h>
#include <iostream>

class Members {
    int groupID, userID;
    
public:
    Members();
    void printInsert();
    void printAttributes(bool isLastPrint);
    
    int getUserID();
};

#endif /* Members_hpp */
