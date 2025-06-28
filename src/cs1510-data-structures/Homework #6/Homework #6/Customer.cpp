// Programmer: Illya Starikov                                Date: 11/19/15
// File: Customer.cpp                                        Class: CS1510A

//
//  Customer.cpp
//  Homework #6
//
//  Created by Illya Starikov on 11/19/15.
//  Copyright © 2015 Illya Starikov. All rights reserved.
//

#include "Customer.hpp"

void Customer::setUpCustomer(const string nameOfCustomer, const int arrivalOfCustomer, const int ticketNumber) {
    name = nameOfCustomer;
    timeOfArrival = arrivalOfCustomer;
    numberOfTickets = ticketNumber;
}

const Customer& Customer::operator= (const Customer &rhs) {
    if (this != &rhs){
        name = rhs.name;
        timeOfArrival = rhs.timeOfArrival;
        numberOfTickets = rhs.numberOfTickets;
        timeStartedProcess = rhs.timeStartedProcess;
    }
    
    return *this;
}

int Customer::timeToLeave()const {
    return timeStartedProcess + TIME_TO_PROCESS_TICKET * ((numberOfTickets > LIMIT_OF_TICKETS) ? LIMIT_OF_TICKETS : numberOfTickets);
}

bool Customer::isFinished(const int currentTime)const {
    return currentTime == timeToLeave();
}

int Customer::customerIsLeavingAndReturnWait(const int currentTime) {
    printLeavingCustomer(currentTime);
    return currentTime - timeOfArrival;
}

void Customer::printLeavingCustomer(const int currentTime) {
    cout << "At time " << currentTime << " " << name << " is done!" << endl;
}

void Customer::printCustomerGoingToTheBack(const int currentTime, const char lineName) {
    cout << "At time " << currentTime << " " << name << " goes to the back of line " << lineName << "." << endl;
}

void Customer::printJoiningCustomer(const char lineName)const {
    cout << "At time " << timeOfArrival << " " << name << " joins " << lineName << "." << endl;
}


