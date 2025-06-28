// Programmer: Illya Starikov                                Date: 11/19/15
// File: ArrayQueue.hpp                                      Class: CS1510A

//
//  ArrayQueue.hpp
//  Homework #6
//
//  Created by Illya Starikov on 11/15/15.
//  Copyright © 2015 Illya Starikov. All rights reserved.
//

#ifndef ArrayQueue_hpp
#define ArrayQueue_hpp

#include <iostream>
#include <string.h>

#include "Customer.hpp"
#include "abstractqueue.h"

using namespace std;

class ArrayQueue : public AbstractQueue<Customer> {
    Customer *customers;
    int max, frontOfQueue, backOfQueue;
    
public:
    ArrayQueue();
    
    virtual bool isEmpty() const;
    virtual const Customer& front() const throw (Oops);
    virtual Customer frontMutatable() const throw (Oops);
    virtual const Customer& back() const throw (Oops);
    virtual void enqueue(const Customer& x);
    virtual void dequeue();
    virtual void clear();
    
    const int size()const;
    void addCustomer(const int timeOfArrival, const string nameOfCustomer, const int numberOfTicketsToPay);
    void startProcessing(const int timeStarted);
    
    ~ArrayQueue();
};


#endif /* ArrayQueue_hpp */
