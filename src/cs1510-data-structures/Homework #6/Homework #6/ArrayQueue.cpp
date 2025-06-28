// Programmer: Illya Starikov                                Date: 11/19/15
// File: ArrayQueue.cpp                                      Class: CS1510A

//
//  ArrayQueue.cpp
//  Homework #6
//
//  Created by Illya Starikov on 11/15/15.
//  Copyright © 2015 Illya Starikov. All rights reserved.
//

#include "ArrayQueue.hpp"

ArrayQueue::ArrayQueue() {
    max = 2;
    frontOfQueue = 0;
    backOfQueue = 0;
    
    customers = new Customer [max];
}

bool ArrayQueue::isEmpty() const {
    return frontOfQueue == backOfQueue;
}

const Customer& ArrayQueue::front() const throw (Oops) {
    try {
        if (isEmpty()) {
            Oops emptyQueue("Empty Queue");
            throw emptyQueue;
        }
    } catch (Oops errorObject) {
        Customer emptyCustomer;
        emptyCustomer.setUpCustomer("Null", 0, 100);
        return emptyCustomer;
    }
    
    return customers[frontOfQueue];
}

Customer ArrayQueue::frontMutatable() const throw (Oops) {
    try {
        if (isEmpty()) {
            Oops emptyQueue("Empty Queue");
            throw emptyQueue;
        }
    } catch (Oops errorObject) {
        Customer emptyCustomer;
        emptyCustomer.setUpCustomer("Null", 0, 100);
        return emptyCustomer;
    }
    
    return customers[frontOfQueue];
}


const Customer& ArrayQueue::back() const throw (Oops) {
    try {
        if (isEmpty()) {
            Oops emptyQueue("Empty Queue");
            throw emptyQueue;
        }
    } catch (Oops errorObject) {
        Customer emptyCustomer;
        emptyCustomer.setUpCustomer("Null", 0, 100);
        return emptyCustomer;
    }
    
    return customers[backOfQueue];
}

void ArrayQueue::enqueue(const Customer& x) {
    if (((backOfQueue + 1) % max) == frontOfQueue) {
        Customer* temporary = new Customer [max * 2];
        
        for (int i = 0; i < max; i++) {
            temporary[i] = customers[(frontOfQueue + i) % max];
        }
        
        delete[] customers;
        customers = NULL;
        customers = temporary;
        
        backOfQueue = max - 1;
        frontOfQueue = 0;
        max = max * 2;
    }
    
    customers[backOfQueue] = x;
    backOfQueue = (backOfQueue + 1) % max;
}

void ArrayQueue::dequeue() {
    if (!isEmpty()) {
        frontOfQueue = (frontOfQueue + 1) % max;
    }
}

void ArrayQueue::clear() {
    frontOfQueue = 0;
    backOfQueue = 0;
}

const int ArrayQueue::size()const {
    return frontOfQueue > backOfQueue ? (max - frontOfQueue + backOfQueue + 1) : (backOfQueue - frontOfQueue + 1);
}

void ArrayQueue::addCustomer(const int timeOfArrival, const string nameOfCustomer, const int numberOfTicketsToPay) {
    Customer toEnqueue;
    toEnqueue.setUpCustomer(nameOfCustomer, timeOfArrival, numberOfTicketsToPay);
    enqueue(toEnqueue);
}

void ArrayQueue::startProcessing(const int timeStarted) {
    customers[frontOfQueue].timeStartedProcess = timeStarted;
}

ArrayQueue::~ArrayQueue() {
    delete []customers;
    customers = NULL;
}