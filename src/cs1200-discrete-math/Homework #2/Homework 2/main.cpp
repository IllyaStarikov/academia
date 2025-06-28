// COMP SCI 1200 Section B FS2015 Assignment 1b
// Illya Starikov

#include <iostream>

using namespace std;

int main() {
    int upperLimit, lowerLimit;
    bool counterExampleHasBeenFound = false;
    
    cout << "Lower Limit? ";
    cin >> lowerLimit;
    
    cout << "Upper Limit? ";
    cin >> upperLimit;
    
    if (lowerLimit < 2) { lowerLimit = 2; } // The shortcut requires that lowerLimit starts at 2;
    if (upperLimit < 1) { upperLimit = 1; } // and since we can easily prove 1 is magic, we can safely skip
    
    int numberOfIteration = lowerLimit, instanceOfCounter = 0; // Save some speed by calling resources on demand
    for (int i = lowerLimit; i <= upperLimit; ++i) {
        instanceOfCounter = i; // need an instance of i so i doesn't  get stuck in an infinite loop
        ++numberOfIteration; // number of iterations to determine if the loop is likely to be infinite
        
        do {
            instanceOfCounter % 2 == 0 ? instanceOfCounter /= 2 : (instanceOfCounter *= 3) += 1; // determine if the variable is even, then do math
            if (numberOfIteration > i * 10) { counterExampleHasBeenFound = true; } // determine if the variable is going to probably continue indefinitly
        } while (instanceOfCounter > i - 1 && !counterExampleHasBeenFound); // continue this until you reach a number you have proven to be a magic number
        // with the exception of if this thereom is proved wrong. With an exception, one is not magic.

    }
    
    (!counterExampleHasBeenFound) ? cout << "\nAll positive integers in this set are magic.\n" : cout << "\nOne or more positive integers in this set are not magic.\n";
    // output the results.
}