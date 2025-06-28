////
////  NNYTicketLine.hpp
////  Homework #6
////
////  Created by Illya Starikov on 11/15/15.
////  Copyright © 2015 Illya Starikov. All rights reserved.
////
//const int MAX_NUMBER_OF_TICKETS = 3;
///Users/Illya/Dropbox/School/Development/CS1510/Homework #6/Homework #6/NNYTicketLine.hpp
//#ifndef NNYTicketLine_h
//#define NNYTicketLine_h
//
//#include "ArrayQueue.hpp"
//#include <iostream>
//
//using namespace std;
//
//class NNYTicketLine {
//    ArrayQueue lineA, lineB;
//    
//public:
//    void inputNewCustomer() {
//        static int timeOfArrival, numberOfTicketsToPay;
//        static string name;
//        
//        cin >> timeOfArrival >> name >> numberOfTicketsToPay;
//        determineIfSomeoneIsFinished(timeOfArrival);
//        addNewCustomerToQueue(timeOfArrival, name, numberOfTicketsToPay);
// 
//    }
//    
//    void outputJoiningTheQueue(const int timeOfArrival, const string nameOfCustomer, const char lineToJoin) {
//        cout << "At time " << timeOfArrival << " " << nameOfCustomer << " joins line "<< lineToJoin << "." << endl;
//    }
//    
//    void addNewCustomerToQueue(const int timeOfArrival, const string nameOfCustomer, const int numberOfTicketsToPay) {
//       // cout << "Line A: " << lineA.backOfQueue << "Max: " << lineA.max<< endl;
//       // cout << "Line B: " << lineB.backOfQueue << "Max: " << lineB.max << endl;
//        // cout << lineA.isEmpty() << lineB.isEmpty();
//        
//        if (lineB.size() >= lineA.size()) {
//            lineA.addCustomer(timeOfArrival, nameOfCustomer, numberOfTicketsToPay);
//            outputJoiningTheQueue(timeOfArrival, nameOfCustomer, 'A');
//        } else {
//            lineB.addCustomer(timeOfArrival, nameOfCustomer, numberOfTicketsToPay);
//            outputJoiningTheQueue(timeOfArrival, nameOfCustomer, 'B');
//        }
//        
//    }
//    
//
//};
//
//#endif /* NNYTicketLine_hpp */
