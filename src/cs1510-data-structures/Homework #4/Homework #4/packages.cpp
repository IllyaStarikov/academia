//
//  packages.cpp
//  Homework #4
//
//  Created by Illya Starikov on 10/26/15.
//  Copyright © 2015 Illya Starikov. All rights reserved.
//

#include "packages.h"

/*--------------------Two Dimensional Package--------------------*/
void TwoDimensionalPackage::setLength(const int lengthToSet) { length = lengthToSet; }
void TwoDimensionalPackage::setWidth(const int widthToSet) { width = widthToSet; }
float TwoDimensionalPackage::getCharge()const { return static_cast<float>(length * width) * twoDimensionalPackageCharge; }
const string& TwoDimensionalPackage::getFrom()const { return m_from; }
const string& TwoDimensionalPackage::getTo() const { return m_to; }
void TwoDimensionalPackage::outputTheCharge()const {
    cout << "From " << m_from << " to " << m_to << " $" << fixed << setprecision(2) << getCharge() << endl;
}

/*--------------------Three Dimensional Package--------------------*/
void ThreeDimensionalPackage::setWeight(const int weightToSet) { weight = weightToSet; }
void ThreeDimensionalPackage::setHeight(const int heightToSet) { height = heightToSet; }

float ThreeDimensionalPackage::getCharge()const { return (static_cast<float>(length * width * height) * threeDimensionalPackageCharge) + (static_cast<float>(weight) * threeDimensionalWeightCharge); }


/*--------------------Four Dimensional Package--------------------*/
void FourDimensionalPackage::setTime(const int timeToSet) { time = timeToSet; }
float FourDimensionalPackage::getCharge()const { return (static_cast<float>(length * width * height * time) * fourDimensionalPackageCharge) + (static_cast<float>(weight) * fourDimensionalWeightCharge) + extraDimensionalHandling ;}