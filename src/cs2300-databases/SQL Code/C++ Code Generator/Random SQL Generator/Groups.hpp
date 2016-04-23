//
//  Groups.hpp
//  Random SQL Generator
//
//  Created by Illya Starikov on 4/10/16.
//  Copyright © 2016 Illya Starikov. All rights reserved.
//

#ifndef Groups_hpp
#define Groups_hpp

#include <iostream>

class Group {
    std::string title, startDate;
    int groupID;
    
public:
    Group();
    void printInsert();
    void printAttributes(bool isLastPrint);
    int generateID();
};

#endif /* Groups_hpp */
