//
// Measurements.hpp
// Random SQL Generator 
// Generates for weight, arm size, and chest size
// 
// Created by Claire Trebing on 4/20/2016
// 

#ifndef Measurements_hpp
#define Measurements_hpp 

#include <iostream> 

using namespace std; 

class Weight {
	int UiD; 
	float weight;
	string TimeStamp, DateStamp; 

public: 
	Weight() ;
	void printInsert(); 
	void printAttributes(bool isLastPrint);
	int createID();
};

class Arm {
	int UiD; 
	float arm;
	string TimeStamp, DateStamp; 

public: 
	Arm() ;
	void printInsert(); 
	void printAttributes(bool isLastPrint);
	int createID();
};

class Chest { 
	int UiD; 
	float chest;
	string TimeStamp, DateStamp; 

public: 
	Chest() ;
	void printInsert(); 
	void printAttributes(bool isLastPrint);
	int createID();
};
#endif /* Measurements_hpp */
