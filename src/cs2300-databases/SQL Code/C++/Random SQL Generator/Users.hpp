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
	int Uid, HeightFeet, HeightInches;
	std::string Username, Birthdate, Password, JoinDate, FName, LName, email;
	float Goal; 
	char Gender, MInit; 
	
public:
    Users(); 
    void printInsert();
    void printAttributes(bool isLastPrint);
    int createID();
};

#endif /* Users_hpp */