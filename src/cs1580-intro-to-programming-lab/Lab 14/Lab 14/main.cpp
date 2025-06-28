// Programmer: Illya Starikov
// Section: 3E
// File: main.cpp
// Description: To calculate with arrays.

#include <iostream>
#include "Array.h"

using namespace std;

int main()
{
    Array_Class<int> A(1,2,3,4);
    int arr[4]={3,2,3,5};
    Array_Class<int> B(arr);
    Array_Class<int> C;
    cout << "A: "<<A<<"B: "<<B<<"C: "<<C;
    B *= A;
    C = A + B;
    cout << "A: "<<A<<"B: "<<B<<"C: "<<C;
}
