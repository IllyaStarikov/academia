// Programmer:  Illya Starikov
// Section:     3E
// File:        main.cpp
// Description: To determine if a number is an armstrong number.

#include <iostream>
#include <math.h>

using namespace std;

/*
 Description:    Get valid user input.
 Pre-Condition:  None.
 Post-Condition: Returns a valid int that is type checked.
 */
int getUserInput();

/*
 Description:    to determine the length of a number (10s, hundreds, etc.)
 Pre-Condition:  a number must be passed.
 Post-Condition: A number is returned that represents the length of the number 
 passed.
 */
int determineLength(int number);

/*
 Description:     determins if the number is an armstrong number.
 Pre-Condition:   the number and it's length must be passed.
 Post-Condition:  a bool is returned to determine if the number is armstrong.
 */
bool isArmstrong(const int number, const int numberLength);

/*
 Description:     prints out the results.
 Pre-Condition:   isArmstrong must be passed and the original number.
 Post-Condition:  Nothing. Side effects.
 */
void printResults(const bool isArmstrong, const int number);

/*
 Description:
 Pre-Condition:
 Post-Condition:
 */
int shiftRight(const int numberToShift);

/*
 Description:
 Pre-Condition:
 Post-Condition:
 */
int firstDigit(const int number, const int numberLength);

int main()
{
    int mainNumber = getUserInput();
    int numberLength = determineLength(mainNumber);
    bool armstrong = isArmstrong(mainNumber, numberLength);
    
    printResults(armstrong, mainNumber);
    
    return 0;
}


int getUserInput()
{
    bool validInput = false, prompt = false;
    int input;
    char inputChar = '\0';
    
    do {
        cout << "Input: ";
        cin >> input;
        
        try
        {
            cin.good() ? validInput = true : throw 0;
        }
        catch (int e) {
            cout << "Invalid Input!" << endl;
            cin.clear();
            cin.ignore(10000,'\n');
            cin.clear();
            validInput = false;
            
            cout << "Would you like to put in a valid number (y/n)? ";
            cin >> inputChar;
            
        }
        
        prompt = (inputChar == 'Y' || inputChar == 'y');
        
    } while (!validInput && prompt);
    
    return input;
}

int determineLength(int number)
{
    int length = 0;
    
    do
    {
        number = number / 10;
        length++;
    } while (number > 0);
    
    return length;
}

bool isArmstrong(const int number, const int numberLength)
{
    int total = 0, numberCopy = number;
    
    for (int i = 0; i < numberLength; ++i)
    {
        total += pow(firstDigit(numberCopy, numberLength), numberLength);
        numberCopy = shiftRight(numberCopy);
    }
    
    return total == number;
}

void printResults(const bool isArmstrong, const int number)
{
    isArmstrong ?
    cout << number << " is an armstrong number!" :
    cout << number << " is not an armstrong number!";
    
    return;
}

int shiftRight(const int numberToShift) {
    return static_cast<int>(numberToShift / 10.0);
}

int firstDigit(const int number, const int numberLength) {
    return static_cast<int>(number % 10);
}

/*
        --------------------
 Thank you for the great semester! :-)
        --------------------
*/