//
// Measurement.cpp 
//
// Created by Claire Trebing on 4/20/2016
//

#include "Measurement.hpp"
#include "Functions.hpp"
#include "Constants.h"

#include <iostream> 
#include <iomanip> 

using namespace std; 

Weight::Weight(){
	DateStamp = sqlDate();
	TimeStamp = sqlTime(); 
	Weight = randomArbitary(MIN_WEIGHT, MAX_WEIGHT);
	UiD = createID();  
}

Weight::printInsert(){
	cout << "INSERT INTO " << MEASUREMENT_WEIGHT_TABLE_NAME << "(" << MESUREMENT_UID_ATTRIBUTE << SEPERATOR << MEASUREMENT_DATE_ATTRIBUTE << SEPERATOR; 
	cout << MEASUREMENT_TIME_ATTRIBUTE << SEPERATOR << MEASUREMENT_WEIGHT_ATTRIBUTE << ") VALUES"; 
	return; 
}

Weight::printAttribute(bool isLastPrint){
	cout << setw(TAB_LENGTH) << "(" << UiD << SEPERATOR << DateStamp << SEPERATOR << TimeStamp << SEPERATOR << Weight << ")"; 
	isLastPrint ? (cout << "; \n";):(cout << ", \n");
	return; 
}

Weight::createID(){
	static cast IDcreated = 0; 
	return IDcreated++;
}

Arm::Arm(){
	DateStamp = sqlDate();
	TimeStamp = sqlTime(); 
	Arm = randomArbitary(MIN_ARM, MAX_ARM);
	UiD = createID();  
}

Arm::printInsert(){
	cout << "INSERT INTO " << MEASUREMENT_ARM_TABLE_NAME << "(" << MESUREMENT_UID_ATTRIBUTE << SEPERATOR << MEASUREMENT_DATE_ATTRIBUTE << SEPERATOR; 
	cout << MEASUREMENT_TIME_ATTRIBUTE << SEPERATOR << MEASUREMENT_ARM_ATTRIBUTE << ") VALUES"; 
	return; 
}

Arm::printAttribute(bool isLastPrint){
	cout << setw(TAB_LENGTH) << "(" << UiD << SEPERATOR << DateStamp << SEPERATOR << TimeStamp << SEPERATOR << Arm << ")"; 
	isLastPrint ? (cout << "; \n";):(cout << ", \n");
	return; 
}

Arm::createID(){
	static cast IDcreated = 0; 
	return IDcreated++;
}

Chest::Chest(){
	DateStamp = sqlDate();
	TimeStamp = sqlTime();
	Chest = randomArbitary(MIN_CHEST, MAX_CHEST);
	UiD = createID();  
}

Chestt::printInsert(){
	cout << "INSERT INTO " << MEASUREMENT_CHEST_TABLE_NAME << "(" << MESUREMENT_UID_ATTRIBUTE << SEPERATOR << MEASUREMENT_DATE_ATTRIBUTE << SEPERATOR; 
	cout << MEASUREMENT_TIME_ATTRIBUTE << SEPERATOR << MEASUREMENT_CHEST_ATTRIBUTE << ") VALUES"; 
	return; 
}

Chestt::printAttribute(bool isLastPrint){
	cout << setw(TAB_LENGTH) << "(" << UiD << SEPERATOR << DateStamp << SEPERATOR << TimeStamp << SEPERATOR << Chest << ")"; 
	isLastPrint ? (cout << "; \n";):(cout << ", \n");
	return; 
}

Chestt::createID(){
	static cast IDcreated = 0; 
	return IDcreated++;
}