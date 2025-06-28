//
//  NNYTicketLine.hpp
//  Homework #6
//
//  Created by Illya Starikov on 11/15/15.
//  Copyright © 2015 Illya Starikov. All rights reserved.
//
const int MAX_NUMBER_OF_TICKETS = 3;

#ifndef NNYTicketLine_h
#define NNYTicketLine_h

#include "Queue.h"
#include <iostream>

using namespace std;

class NNYTicketLine {
    Queue lineA, lineB;
    int sizeOfA, sizeOfB;
    int currentTime;
    
public:
    NNYTicketLine() {
        sizeOfA = 0;
        sizeOfB = 0;
        currentTime = 0;
    }
    
    void inputNewCustomer() {
        static int timeOfArrival, numberOfTicketsToPay;
        static string name;
        
        cin >> timeOfArrival >> name >> numberOfTicketsToPay;
        addNewCustomerToQueue(timeOfArrival, name, numberOfTicketsToPay);
    }
    
    void outputJoiningTheQueue(const int timeOfArrival, const string nameOfCustomer, const char lineToJoin) {
        cout << "At time " << timeOfArrival << " " << nameOfCustomer << " joins line "<< lineToJoin << ".";
    }
    
    void addNewCustomerToQueue(const int timeOfArrival, const string nameOfCustomer, const int numberOfTicketsToPay) {

        if (sizeOfA >= sizeOfB) {
            lineA.addCustomer(timeOfArrival, nameOfCustomer, numberOfTicketsToPay);
            outputJoiningTheQueue(timeOfArrival, nameOfCustomer, 'A');
            sizeOfA++;
            
        } else {
            lineB.addCustomer(timeOfArrival, nameOfCustomer, numberOfTicketsToPay);
            outputJoiningTheQueue(timeOfArrival, nameOfCustomer, 'B');
            sizeOfB++;
        }
        
    }
};

#endif /* NNYTicketLine_hpp */
