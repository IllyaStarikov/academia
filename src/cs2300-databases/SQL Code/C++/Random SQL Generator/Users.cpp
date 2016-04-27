//
// Users.cpp
// Random SQL Generator
//
// Created by Claire Trebing on 4/18/2016
//

#include "Users.hpp"
#include "Functions.hpp"
#include "Constants.h"

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

Users::Users () {
	int RandNum, PasswordNum;
	//UiD
	Uid = createID();
    
	//Username
	RandNum = randomArbitrary(0,USERS_USERNAME_TO_GO_TO);
	Username = importFromFile(USER_USERNAME_FILENAME, RandNum);

	
	RandNum = randomArbitrary(0, 1);
	if(RandNum == 0){Username.append("the");}

	RandNum = randomArbitrary(0,USERS_USERNAME_TO_GO_TO);
	Username.append(importFromFile(USER_USERNAME_FILENAME, RandNum));

    RandNum = randomArbitrary(0, 1);
    if(RandNum == 0){Username.append(std::to_string(randomArbitrary(0,999)));}
	//HeightFeet
	HeightFeet = randomArbitrary(4, 6); // All users will be between 4 and 6 ft tall

	//HeightInches
	HeightInches = randomArbitrary(0,11); //All users will have a number of inches between 0 and 11

	//Birthdate
	Birthdate = sqlDate(START_YEAR, CURRENT_YEAR - 18);

	//Password
	RandNum = randomArbitrary(8,15); //Makes password a random length
	for(int i = 0; i < RandNum; ++i){
        PasswordNum = randomArbitrary(0, 1);
        Password += (randomLetter(PasswordNum));
    }

	//JoinDate
	JoinDate = sqlDate(CURRENT_YEAR - 18, CURRENT_YEAR); 
	
	//Gender 
	RandNum = randomArbitrary(0, 1);
	if(RandNum == 0){ Gender = 'F'; }
	else{ Gender = 'M';}
	
	//Weight 
	if(RandNum == 0){
		Weight = randomArbitrary(140, 180); //The average weight of an american female is 166.2 
		Weight = Weight + randomArbitrary(0,9)/10.0; //Possible weights range from 140 and 180.9
	}
	else {
		Weight = randomArbitrary(180, 215); //The average weight of an american male is 195.2 lbs
		Weight = Weight + randomArbitrary(0,9)/10.0; //Possible weights range from 180.0 to 215.9
	}

	//Goal
	Goal = Weight - randomArbitrary(0, 30) + randomArbitrary(0,9)/10.0; //Possible goals range from losing 0.0 to 30.9 lbs

	//First Name
	if (RandNum == 0) {
		RandNum = randomArbitrary(0, USERS_FFIRST_NAME_TO_GO_TO);
		FName = string(importFromFile("data/FName.txt", RandNum));
	} else {
		RandNum = randomArbitrary(0, USERS_MFIRST_NAME_TO_GO_TO); 
		FName = string(importFromFile("data/FName.txt", RandNum));
	}
	
	//Middle Initial 
	MInit = 'A' + randomArbitrary(0, 25);
	
	//Last Name 
	RandNum = randomArbitrary(0,USERS_LNAME_TO_GO_TO);
	LName = importFromFile(USER_LNAME_FILENAME, RandNum);
    
    RandNum = randomArbitrary(0, NUMBER_OF_MAIL_PROVIDERS - 1);
    
    email = FName + LName + std::to_string(Uid) + "@" + MAIL_PROVIDERS[RandNum];
}
const std::string USER_EMAIL = "Email";

void Users::printInsert(){
    cout << "INSERT INTO " << USER_TABLE_NAME_ATTRIBUTE << "(";
    cout << USER_UID_ATTRIBUTE << SEPERATOR << USER_USERNAME_ATTRIBUTE << SEPERATOR;
    cout << USER_EMAIL << SEPERATOR;
    cout << USER_HEIGHT_FEET_ATTRIBUTE << SEPERATOR << USER_HEIGTH_INCHES_ATTRIBUTE << SEPERATOR;
    cout << USER_BIRTHDATE_ATTRIBUTE << SEPERATOR << USER_STARTING_WEIGHT_ATTRIBUTE << SEPERATOR;
    cout << USER_GOAL_WEIGHT_ATTRIBUTE << SEPERATOR << USER_PASSWORD_ATTRIBUTE << SEPERATOR;
    cout << USER_JOINDATE_ATTRIBUTE << SEPERATOR << USER_GENDER_ATTRIBUTE << SEPERATOR;
    cout << USER_FNAME_ATTRIBUTE << SEPERATOR << USER_MINIT_ATTRIBUTE << SEPERATOR << USER_LNAME_ATTRIBUTE;
    cout << ") VALUES" << endl;
}

void Users::printAttributes(bool isLastPrint) {
    std::cout <<  std::setw(TAB_LENGTH) << "(" << Uid << SEPERATOR << DELIMETER << Username << DELIMETER << SEPERATOR << DELIMETER << email << DELIMETER << SEPERATOR
    << HeightFeet << SEPERATOR << HeightInches << SEPERATOR
    << DELIMETER << Birthdate  << DELIMETER << SEPERATOR << Weight << SEPERATOR << Goal << SEPERATOR
    << DELIMETER << Password << DELIMETER << SEPERATOR << DELIMETER << JoinDate << DELIMETER << SEPERATOR << DELIMETER << Gender << DELIMETER << SEPERATOR;
    cout << flush << flush << DELIMETER << FName << DELIMETER << SEPERATOR << DELIMETER << MInit << DELIMETER << SEPERATOR << DELIMETER << LName << DELIMETER << ")";
    isLastPrint ? std::cout << ";"  << std::endl : std::cout << "," << std::endl;
    
}

int Users::createID() {
	static int ID = 0; 
	return ++ID;
}
