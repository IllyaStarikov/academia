//
//  Groups.hpp
//  Random SQL Generator
//
//  Created by Claire Trebing on 4/18/2016
//

#ifndef Users_hpp
#define Users_hpp

#include <iostream>

class Users {
	int Uid, Height, Weight, Goal; 
	std::string Username, Birthdate, Password, JoinDate, FName, LName;
	char Gender, MInit; 
	
public:
    Users(); 
    void printInsert();
    void printAttributes(bool isLastPrint);
};

#endif /* Users_hpp */