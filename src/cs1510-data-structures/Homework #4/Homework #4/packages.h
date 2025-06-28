// Programmer: Illya Starikov                                Date: 10/25/15
// File: Packages.cpp                                        Class: CS1510A

#include "Constants.h"
#include "abstractpackage.h"

#include <iomanip>
#include <iostream>

using namespace std;

#ifndef packages_h
#define packages_h

class TwoDimensionalPackage : public AbstractPackage {
protected:
    int length, width;

public:
    TwoDimensionalPackage(string f, string t): AbstractPackage(f,t) {};
    
    virtual void setLength(const int lengthToSet);
    virtual void setWidth(const int widthToSet);

    virtual float getCharge()const;
    virtual const string& getFrom()const;
    virtual const string& getTo()const;

    virtual void outputTheCharge()const;

};

class ThreeDimensionalPackage : public TwoDimensionalPackage {
protected:
    int height, weight;

public:
    ThreeDimensionalPackage(string f, string t): TwoDimensionalPackage(f,t) {};
    
    virtual void setWeight(const int weightToSet);
    virtual void setHeight(const int heightToSet);

    virtual float getCharge()const;
};

class FourDimensionalPackage : public ThreeDimensionalPackage {
protected:
    int time;

public:
    FourDimensionalPackage(string f, string t): ThreeDimensionalPackage(f,t) {};
    virtual void setTime(const int timeToSet);

    virtual float getCharge()const;
};

#endif /* Header_h */
