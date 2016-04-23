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
	UiD = createID(); 

	//Username
	RandNum = randomArbitrary(0,USERS_USERNAME_TO_GO_TO);
	Username = importFromFile(USER_USERNAME_FILENAME, RandNum);
	
	RandNum = rand()%2; 
	if(RandNum == 0){Username.append('the');}

	RandNum = randomArbitrary(0,USERS_USERNAME_TO_GO_TO); 
	Username.append(importFromFile(USER_USERNAME_FILENAME, RandNum));
	
	RandNum = rand()%2;
	if(RandNum == 0){Username.append(randomArbitrary(0,999));} 

	//HeightFeet
	HeightFeet = randomArbitrary(4, 6); // All users will be between 4 and 6 ft tall
	
	//HeightInches
	HeightInches = randomArbitrary(0,11); //All users will have a number of inches between 0 and 11
	
	//Birthdate
	Birthdate = sqlDate(START_YEAR, CURRENT_YEAR - 18); 

	//Password 
	RandNum = randomArbitrary(8,15); //Makes password a random length
	for(int i = 0; i < RandNum; ++i){
		PasswordNum = rand()&62; 
		if(PasswordNum <= 25){ //Capital Letters
			Password.append('A' + PasswordNum);
		}
		else{
			if(PasswordNum > 25 && PasswordNum <= 51){//Lowercase letters
				Password.append('a' + PasswordNum - 26);
			}
			else{ //Numbers 
				Password.append('0' + PasswordNum - 52);
			}
		}
	}
		
	//JoinDate
	JoinDate = sqlDate(CURRENT_YEAR - 18, CURRENT_YEAR); 
	
	//Gender 
	RandNum = rand()% 2; 
	if(RandNum == 0){ Gender = 'F'; }
	else{ Gender = 'M';}
	
	//Weight 
	if(RandNum = 0){
		Weight = randomArbitrary(140, 180); //The average weight of an american female is 166.2 
		Weight = Weight + randomArbitrary(0,9)/10.0; //Possible weights range from 140 and 180.9
	}
	else{
		Weight = randomArbitrary(180, 215); //The average weight of an american male is 195.2 lbs
		Weight = Weight + randomArbitrary(0,9)/10.0; //Possible weights range from 180.0 to 215.9
	}
	
	//Goal
	Goal = Weight - randomArbitrary(0, 30) + randomArbitrary(0,9)/10.0; //Possible goals range from losing 0.0 to 30.9 lbs
	
	//First Name 
	if(RandNum = 0){
		RandNum = randomArbitrary(0, USERS_FFIRST_NAME_TO_GO_TO);
		FName = importFromFile(USER_FFIRSTNAME_FILENAME,NameNum);
	}
	else{
		RandNum = randomArbitrary(0, USERS_MFIRST_NAME_TO_GO_TO); 
		FName = importFromFile(USER_MFIRSTNAME_FILENAME, NameNum);
	}
	
	//Middle Initial 
	Minit = 'A' + rand()%26; 
	
	//Last Name 
	NameNum = randomArbitrary(0,USERS_LNAME_TO_GO_TO);
	Lname = importFromFile(USER_LNAME_FILE, NameNum);
}

void Users::printInsert(){
	cout << "INSERT INTO " << USER_TABLE_NAME_ATTRIBUTE << "("; 
	cout << USER_UID_ATTRIBUTE << "," << USER_USERNAME_ATTRIBUTE << ","; 
	cout << USER_HEIGHT_FEET_ATTRIBUTE << "," << USER_HEIGHT_INCHES_ATTRIBUTE << ","; 
	cout << USER_BIRTHDATE_ATTRIBUTE << "," << USER_STARTING_WEIGHT_ATTRIBUTE << ","; 
	cout << USER_GOAL_WEIGHT_ATTRIBUTE << "," << USER_PASSWORD_ATTRIBUTE << ",";
	cout << USER_JOINDATE_ATTRIBUTE << "," << USER_GENDER_ATTRIBUTE << ",";
	cout << USER_FNAME_ATTRIBUTE << "," << USER_MINIT_ATTRIBUTE << "," << USER_LNAME_ATTRIBUTE;
	cout << ") VALUES";  
}
void Users::printAttributes(bool isLastPrint){
	cout << setw(TAB_LENGTH) << "(" << UiD << "," << Username << ","; 
	cout << setw(TAB_LENGTH) << HeightFeet << "," << HeightInches << ","; 
	cout << setw(TAB_LENGTH) << Birthdate << "," << Weight << "," << Goal << ",";
	cout << setw(TAB_LENGTH) << Password << "," << JoinDate << "," << Gender << ",";
	cout << setw(TAB_LENGTH) << FName << "," << Minit << "<" << Lname << ")";
	isLastPrint ? (cout << "; \n";):(cout << ", \n";); 
}

int Users::createID(){
	static int ID = 0; 
	return ID++;
}