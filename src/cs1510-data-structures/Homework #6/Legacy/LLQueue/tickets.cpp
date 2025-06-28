//
//  main.cpp
//  Homework #6
//
//  Created by Illya Starikov on 11/14/15.
//  Copyright © 2015 Illya Starikov. All rights reserved.
//

#include <iostream>
#include "NNYTicketLine.h"

int main(int argc, const char * argv[]) {
    int numberOfCustomers;
    NNYTicketLine NewNewYorkTicketLine;
    
    cin >> numberOfCustomers;
    
    for (int i = 0; i < numberOfCustomers; i++) {
        NewNewYorkTicketLine.inputNewCustomer();
        
    }
}
