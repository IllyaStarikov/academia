// Programmer: Illya Starikov                                Date: 10/25/15
// File: Main.cpp                                            Class: CS1510A

#include <iomanip>
#include <iostream>

#include "packages.h"


using namespace std;
int main() {
    int numberOfPackages, numberOfDimensions, userInput;
    float totalProfit = 0;
    //    int length, width, height, weight, time;
    string from, to;

    cin >> numberOfPackages;
    for (int i = 0; i < numberOfPackages; i++) {
        cin >> numberOfDimensions >> from >> to;

        if (numberOfDimensions == 2) {
            TwoDimensionalPackage main2DPackage(from, to);

            cin >> userInput;
            main2DPackage.setLength(userInput);

            cin >> userInput;
            main2DPackage.setWidth(userInput);

            cout << "#" << i << ": ";
            main2DPackage.outputTheCharge();
            totalProfit += main2DPackage.getCharge();

        } else if (numberOfDimensions == 3) {
            ThreeDimensionalPackage main3DPackage(from, to);

            cin >> userInput;
            main3DPackage.setLength(userInput);

            cin >> userInput;
            main3DPackage.setWidth(userInput);

            cin >> userInput;
            main3DPackage.setHeight(userInput);

            cin >> userInput;
            main3DPackage.setWeight(userInput);

            cout << "#" << i << ": ";
            main3DPackage.outputTheCharge();
            totalProfit += main3DPackage.getCharge();

        } else if (numberOfDimensions == 4) {
            FourDimensionalPackage main4DPackage(from, to);

            cin >> userInput;
            main4DPackage.setLength(userInput);

            cin >> userInput;
            main4DPackage.setWidth(userInput);

            cin >> userInput;
            main4DPackage.setHeight(userInput);

            cin >> userInput;
            main4DPackage.setTime(userInput);

            cin >> userInput;
            main4DPackage.setWeight(userInput);

            cout << "#" << i << ": ";
            main4DPackage.outputTheCharge();
            totalProfit += main4DPackage.getCharge();
        }
    }

    cout << fixed << setprecision(2) << "TOTAL PROFIT = $" << totalProfit << endl << "AVERAGE = $" <<  totalProfit / numberOfPackages << endl;
}
