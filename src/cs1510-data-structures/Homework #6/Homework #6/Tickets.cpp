// Programmer: Illya Starikov                                Date: 11/19/15
// File: Tickets.cpp                                         Class: CS1510A

//
//  Tickets.cpp
//  Homework #6
//
//  Created by Illya Starikov on 11/15/15.
//  Copyright © 2015 Illya Starikov. All rights reserved.
//

#include <iostream>

#include "Customer.hpp"
#include "ArrayQueue.hpp"

int main () {
    int numberOfCustomers, timeOfArrival, numberOfTicketsToPay, currentTime = 0;
    int shortestWaitTime = 10000, longestWaitTime = 0, temporary;
    string name, nameOfShortestWait, nameOfLongestWait;
    bool firstRunThroughLoop = true;
    
    ArrayQueue waiting;
    ArrayQueue lineA, lineB;
    Customer temporaryCustomer, topOfWaiting;
    
    // Gather data for the customers, throw into waiting queue
    cin >> numberOfCustomers;
    for (int i = 0; i < numberOfCustomers; i++) {
        cin >> timeOfArrival >> name >> numberOfTicketsToPay;
        temporaryCustomer.setUpCustomer(name, timeOfArrival, numberOfTicketsToPay);
        waiting.enqueue(temporaryCustomer);
    }
    
    while (!(lineA.isEmpty() && lineB.isEmpty() && waiting.isEmpty())) {
        topOfWaiting = waiting.front(); // temporary holder for front mutations
        
        // Checks to see if anyone is finished
        if (!lineA.isEmpty()) {
            if (lineA.front().isFinished(currentTime)) {
                // Two cases.
                
                // If front has more than the limit of tickets:
                //   - Get a mutatable customer
                //   - Take away the number of tickets, print his shameful actions
                //   - Enqueue him, and dequeue him, onto the next one
                //   - Profit.
                
                // Else: process accordingly
                if (lineA.front().numberOfTickets > LIMIT_OF_TICKETS) {
                    temporaryCustomer = lineA.front();
                    temporaryCustomer.numberOfTickets -= LIMIT_OF_TICKETS;
                    temporaryCustomer.printCustomerGoingToTheBack(currentTime, 'A');
                    lineA.enqueue(temporaryCustomer);
                    lineA.dequeue();
                    lineA.startProcessing(currentTime);
                } else {
                    temporary = lineA.frontMutatable().customerIsLeavingAndReturnWait(currentTime);
                    
                    // Get the shortest and longest wait times
                    // First if is takes care of the first assignment
                    if (firstRunThroughLoop) {
                        shortestWaitTime = temporary;
                        longestWaitTime = temporary;
                        firstRunThroughLoop = false;
                    } else {
                        if (temporary < shortestWaitTime) {
                            shortestWaitTime = temporary;
                            nameOfShortestWait = lineA.front().name;
                        }
                        if (temporary > longestWaitTime) {
                            longestWaitTime = temporary;
                            nameOfLongestWait = lineA.front().name;
                        }
                    }
                    
                    
                    lineA.dequeue();
                    lineA.startProcessing(currentTime);
                }
            }
        }
        
        // Line B shares parity with line A.
        if (!lineB.isEmpty()) {
            if (lineB.front().isFinished(currentTime)) {
                if (lineB.front().numberOfTickets > LIMIT_OF_TICKETS) {
                    temporaryCustomer = lineB.front();
                    temporaryCustomer.numberOfTickets -= LIMIT_OF_TICKETS;
                    temporaryCustomer.printCustomerGoingToTheBack(currentTime, 'A');
                    lineB.enqueue(temporaryCustomer);
                    lineB.dequeue();
                    lineB.startProcessing(currentTime);
                } else {
                    temporary = lineB.frontMutatable().customerIsLeavingAndReturnWait(currentTime);
                    
                    if (firstRunThroughLoop) {
                        shortestWaitTime = temporary;
                        longestWaitTime = temporary;
                    } else {
                        if (temporary < shortestWaitTime) {
                            shortestWaitTime = temporary;
                            nameOfShortestWait = lineB.front().name;
                        }
                        
                        if (temporary > longestWaitTime) {
                            longestWaitTime = temporary;
                            nameOfLongestWait = lineB.front().name;
                        }
                    }
                    
                    
                    lineB.dequeue();
                    lineB.startProcessing(currentTime);
                }
            }
        }
        
        // Process the waiting queue.
        // Assign to shortest or Line A by default. Dequeue.
        if (!waiting.isEmpty()) {
            if (currentTime == waiting.front().timeOfArrival) {
                if (lineA.size() <= lineB.size()) {
                    waiting.front().printJoiningCustomer('A');
                    topOfWaiting.timeStartedProcess = currentTime;
                    lineA.enqueue(topOfWaiting);
                } else {
                    waiting.front().printJoiningCustomer('B');
                    topOfWaiting.timeStartedProcess = currentTime;
                    lineB.enqueue(topOfWaiting);
                }
                waiting.dequeue();
            }
        }
        currentTime++;
    }
    
    cout << endl;
    cout << "Longest wait: " << nameOfLongestWait << ", " << longestWaitTime << " mins." << endl;
    cout << "Shortest wait: " << nameOfShortestWait << ", " << shortestWaitTime << " mins." << endl;
}