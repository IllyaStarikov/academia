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

using namespace std; 

Users::Users () { 
	int rand, NameNum; 
	//UiD = ; 
	//Username = ; 
	//Height = ; 
	//Birthdate = ; 
	//Goal = ; 
	//Password = ; 
	//JoinDate
	
	//Gender 
	rand = rand()% 2; 
	if(rand == 0){ Gender = 'F'; }
	else{ Gender = 'M';}
	
	//First Name 
	if(rand = 0){
		NameNum = randomArbitrary(0, USERS_FFIRST_NAME_TO_GO_TO);
		FName = importFromFile(USER_FFIRSTNAME_FILENAME,NameNum);
	}
	else{
		NameNum = randomArbitrary(0, USERS_MFIRST_NAME_TO_GO_TO); 
		FName = importFromFile(USER_MFIRSTNAME_FILENAME, NameNum);
	}
	
	//Middle Initial 
	Minit = 'a' + rand()%26; 
	
	//Last Name 
	NameNum = randomArbitrary(0,USERS_LNAME_TO_GO_TO);
	Lname = importFromFile(USER_LNAME_FILE, NameNum);
}