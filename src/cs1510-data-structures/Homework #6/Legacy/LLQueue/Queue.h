//
//  abstractqueue.cpp
//  Homework #6
//
//  Created by Illya Starikov on 11/14/15.
//  Copyright © 2015 Illya Starikov. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "abstractqueue.h"

using namespace std;

class Queue : public AbstractQueue<string> {
    string name;
    int arrivalTime, ticketsToPay;
    
    Queue *next;
    
public:
    virtual bool isEmpty() const {
        
        return next == nullptr;
    }
    
    virtual const string& front() const throw (Oops) {
        try {
            if (isEmpty()) {
                Oops emptyQueue("Empty Queue");
                throw emptyQueue;
            }
        } catch (Oops) {
            
        }
        return next -> next -> name;
    }
    
    virtual const string& back() const throw (Oops) {
        return next -> name;
    }
    
    virtual void enqueue(const string& x) {
        Queue *itemToEnqueue = new Queue;
        itemToEnqueue -> name = x;
        
        if (isEmpty()) {
            next = itemToEnqueue;
            itemToEnqueue -> next = itemToEnqueue;
        } else {
            itemToEnqueue -> next = next -> next;
            next -> next = itemToEnqueue;
            next = itemToEnqueue;
        }
        
    }
    
    virtual void dequeue() {
        if (!isEmpty()) {
            Queue *temporary = next -> next;
            
            if (next != temporary) {
                next -> next = temporary -> next;
                delete temporary;
                temporary = nullptr;
            } else {
                next -> next = temporary -> next;
                delete temporary;
                temporary = nullptr;
            }
        }
    }
    
    virtual void clear() {
        while (!isEmpty()) {
            dequeue();
        }
    }
//    
//    int size()const {
//        cout << isEmpty();
//        if (isEmpty()) { return 0;  }
//        
//        int counter = 0;
//        const Queue *runner = this;
//        
//        while (runner -> next != nullptr) {
//            counter++;
//            runner = runner -> next;
//        }
//        
//        return counter;
//    }
//    
    void addCustomer(const int timeOfArrival, const string nameOfCustomer, const int numberOfTicketsToPay) {
        enqueue(nameOfCustomer);
        arrivalTime = timeOfArrival;
        ticketsToPay = numberOfTicketsToPay;
    }
    
};