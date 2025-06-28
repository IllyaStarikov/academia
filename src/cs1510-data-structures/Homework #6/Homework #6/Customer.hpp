// Programmer: Illya Starikov                                Date: 11/19/15
// File: Customer.hpp                                        Class: CS1510A

//
//  Customer.hpp
//  Homework #6
//
//  Created by Illya Starikov on 11/19/15.
//  Copyright © 2015 Illya Starikov. All rights reserved.
//

#ifndef Customer_hpp
#define Customer_hpp

const int LIMIT_OF_TICKETS = 3;
const int TIME_TO_PROCESS_TICKET = 5;

#include <iostream>

using namespace::std;

struct Customer {
    string name;
    int timeOfArrival, numberOfTickets;
    int timeStartedProcess;
    
    void setUpCustomer(const string nameOfCustomer, const int arrivalOfCustomer, const int ticketNumber);
    const Customer& operator= (const Customer &rhs);
    int timeToLeave()const;
    bool isFinished(const int currentTime)const;
    
    int customerIsLeavingAndReturnWait(const int currentTime);
    void printLeavingCustomer(const int currentTime);
    void printCustomerGoingToTheBack(const int currentTime, const char lineName);
    void printJoiningCustomer(const char lineName)const;
    

};

#endif /* Customer_hpp */
