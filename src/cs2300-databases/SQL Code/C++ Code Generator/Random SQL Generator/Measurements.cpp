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
	DateStamp = sqlDate(CURRENT_YEAR - 5, CURRENT_YEAR);
	TimeStamp = sqlTime(); 
	weight = randomArbitrary(MIN_WEIGHT, MAX_WEIGHT);
	UiD = createID();  
}

void Weight::printInsert(){
	cout << "INSERT INTO " << MEASUREMENT_WEIGHT_TABLE_NAME << "(" << MEASUREMENT_UID_ATTRIBUTE << SEPERATOR << MEASUREMENT_DATE_ATTRIBUTE << SEPERATOR;
	cout << MEASUREMENT_TIME_ATTRIBUTE << SEPERATOR << MEASUREMENT_WEIGHT_ATTRIBUTE << ") VALUES" << endl;
	return; 
}

void Weight::printAttributes(bool isLastPrint){
	cout << setw(TAB_LENGTH) << "(" << UiD << SEPERATOR << DELIMETER << DateStamp << DELIMETER << SEPERATOR << TimeStamp << SEPERATOR << weight << ")";
    isLastPrint ? (cout << "; \n"):(cout << ", \n");
	return; 
}

int Weight::createID(){
	static int IDcreated = 0;
	return ++IDcreated;
}

Arm::Arm(){
	DateStamp = sqlDate(CURRENT_YEAR - 5, CURRENT_YEAR);
	TimeStamp = sqlTime(); 
	arm = randomArbitrary(MIN_ARM, MAX_ARM);
	UiD = createID();  
}

void Arm::printInsert(){
	cout << "INSERT INTO " << MEASUREMENT_ARM_TABLE_NAME << "(" << MEASUREMENT_UID_ATTRIBUTE << SEPERATOR << MEASUREMENT_DATE_ATTRIBUTE << SEPERATOR;
	cout << MEASUREMENT_TIME_ATTRIBUTE << SEPERATOR << MEASURMENT_ARM_ATTRIBUTE << ") VALUES" << endl;
	return; 
}

void Arm::printAttributes(bool isLastPrint){
	cout << setw(TAB_LENGTH) << "(" << UiD << SEPERATOR << DELIMETER << DateStamp << DELIMETER << SEPERATOR << TimeStamp << SEPERATOR << arm << ")";
	isLastPrint ? (cout << "; \n"):(cout << ", \n");
	return; 
}

int Arm::createID(){
	static int IDcreated = 0;
	return ++IDcreated;
}

Chest::Chest(){
	DateStamp = sqlDate(CURRENT_YEAR - 5, CURRENT_YEAR);
	TimeStamp = sqlTime();
	chest = randomArbitrary(MIN_CHEST, MAX_CHEST);
	UiD = createID();  
}

void Chest::printInsert(){
	cout << "INSERT INTO " << MEASUREMENT_CHEST_TABLE_NAME << "(" << MEASUREMENT_UID_ATTRIBUTE << SEPERATOR << MEASUREMENT_DATE_ATTRIBUTE << SEPERATOR;
	cout << MEASUREMENT_TIME_ATTRIBUTE << SEPERATOR << MEASURMENT_CHEST_ATTRIBUTE << ") VALUES" << endl;
	return; 
}

void Chest::printAttributes(bool isLastPrint){
	cout << setw(TAB_LENGTH) << "(" << UiD << SEPERATOR << DELIMETER << DateStamp << DELIMETER << SEPERATOR << TimeStamp << SEPERATOR << chest << ")";
	isLastPrint ? (cout << "; \n"):(cout << ", \n");
	return; 
}

int Chest::createID(){
	static int IDcreated = 0;
	return ++IDcreated;
}