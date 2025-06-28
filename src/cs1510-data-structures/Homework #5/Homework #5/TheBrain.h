// Programmer: Illya Starikov                                Date: 11/08/15
// File: The Brain.h                                         Class: CS1510A
//
//  TheBrain.h
//  Homework #5
//
//  Created by Illya Starikov on 11/5/15.
//  Copyright © 2015 Illya Starikov. All rights reserved.
//

#ifndef TheBrain_H
#define TheBrain_H

#include "abstractstack.h"
#include <iostream>

using namespace::std;

class TheBrain : public AbstractStack<int> {
protected:
    int *data;
    int max, topOfStack;
    
public:
    TheBrain();
    virtual bool isEmpty() const;
    virtual const int& top() const throw ( Oops );
    virtual void push(const int& x);
    virtual void pop();
    
    virtual int popAndReturn();
    
    
    virtual void clear();
    virtual void print();
    
    virtual void sum();
    virtual void product();
    
    virtual ~TheBrain();
};


#endif