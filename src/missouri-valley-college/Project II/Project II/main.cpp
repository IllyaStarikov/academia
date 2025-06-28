//

// main.c
// GPA Calculator
//
// Created by Illya Starikov on 2/14/14.
// Copyright (c) 2014 iTz iLLi Production. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void)
{
    int intTotalCredits, intCurrentCredits = 0, intTotalHours;
    char strClass1[15], strClass2[15], strClass3[15], strClass4[15], strClass5[15], strClass6[15], strClass7[15];
    char strID1[15], strID2[15], strID3[15], strID4[15], strID5[15], strID6[15], strID7[15];
    int intCredits1, intCredits2, intCredits3, intCredits4, intCredits5, intCredits6, intCredits7;
    float floGPAValue1, floGPAValue2, floGPAValue3, floGPAValue4, floGPAValue5, floGPAValue6, floGPAValue7;
    float floGPA;
    
    printf("Enter Total Credit Hours: ");
    scanf("%d", &intTotalCredits);
    fflush(stdin);
    
    //SECTION ONE
    printf("Enter Class Name: ");
    gets(strClass1);
    printf("Enter Class ID: ");
    gets(strID1);
    printf("Enter Class Credit Hours: ");
    scanf("%d", &intCredits1);
    printf("Enter Class Grade Percentage: ");
    scanf("%f", &floGPAValue1);
    if (floGPAValue1 >= 90)
        floGPAValue1 = 4;
    else if (floGPAValue1 < 90 && floGPAValue1 >= 80)
        floGPAValue1 = 3;
    else if (floGPAValue1 < 80 && floGPAValue1 >= 70)
        floGPAValue1 = 2;
    else if (floGPAValue1 < 70 && floGPAValue1 >= 60)
        floGPAValue1 = 1;
    else floGPAValue1 = 0;
    floGPAValue1 = floGPAValue1 * intCredits1;
    intCurrentCredits = intCurrentCredits + intCredits1;
    if (intCurrentCredits == intTotalCredits)
    {
        intTotalHours = floGPAValue1;
        floGPA = intTotalHours / intTotalCredits;
        printf("Class #1: %s\n", strClass1);
        printf("Class ID: %s\n", strID1);
        printf("Your GPA Is: %f", floGPA);
        system("pause");
    }
    
    //SECTION TWO
    fflush(stdin);
    printf("Enter Class Name: ");
    gets(strClass2);
    printf("Enter Class ID: ");
    gets(strID2);
    printf("Enter Class Credit Hours: ");
    scanf("%d", &intCredits2);
    printf("Enter Class Grade Percentage: ");
    scanf("%f", &floGPAValue2);
    if (floGPAValue2 >= 90)
        floGPAValue2 = 4;
    else if (floGPAValue2 < 90 && floGPAValue2 >= 80)
        floGPAValue2 = 3;
    else if (floGPAValue2 < 80 && floGPAValue2 >= 70)
        floGPAValue2 = 2;
    else if (floGPAValue2 < 70 && floGPAValue2 >= 60)
        floGPAValue2 = 1;
    else floGPAValue2 = 0;
    floGPAValue2 = floGPAValue2 * intCredits2;
    intCurrentCredits = intCurrentCredits + intCredits2;
    if (intCurrentCredits == intTotalCredits)
    {
        intTotalHours = floGPAValue1 + floGPAValue2;
        floGPA = intTotalHours / intTotalCredits;
        printf("Class #1: %s\n", strClass1);
        printf("Class ID: %s\n", strID1);
        printf("Class #2: %s\n", strClass2);
        printf("Class ID: %s\n", strID2);
        printf("Your GPA Is: %f", floGPA);
        system("pause");
    }
    
    //SECTION THREE
    fflush(stdin);
    printf("Enter Class Name: ");
    gets(strClass3);
    printf("Enter Class ID: ");
    gets(strID3);
    printf("Enter Class Credit Hours: ");
    scanf("%d", &intCredits3);
    printf("Enter Class Grade Percentage: ");
    scanf("%f", &floGPAValue3);
    if (floGPAValue3 >= 90)
        floGPAValue3 = 4;
    else if (floGPAValue3 < 90 && floGPAValue3 >= 80)
        floGPAValue3 = 3;
    else if (floGPAValue3 < 80 && floGPAValue3 >= 70)
        floGPAValue3 = 2;
    else if (floGPAValue3 < 70 && floGPAValue3 >= 60)
        floGPAValue3 = 1;
    else floGPAValue3 = 0;
    floGPAValue3 = floGPAValue3 * intCredits3;
    intCurrentCredits = intCurrentCredits + intCredits3;
    if (intCurrentCredits == intTotalCredits)
    {
        intTotalHours = floGPAValue1 + floGPAValue2 + floGPAValue3;
        floGPA = intTotalHours / intTotalCredits;
        printf("Class #1: %s\n", strClass1);
        printf("Class ID: %s\n", strID1);
        printf("Class #2: %s\n", strClass2);
        printf("Class ID: %s\n", strID2);
        printf("Class #3: %s\n", strClass3);
        printf("Class ID: %s\n", strID3);
        printf("Your GPA Is: %f", floGPA);
        system("pause");
    }
    
    //SECTION FOUR
    fflush(stdin);
    printf("Enter Class Name: ");
    gets(strClass4);
    printf("Enter Class ID: ");
    gets(strID4);
    printf("Enter Class Credit Hours: ");
    scanf("%d", &intCredits4);
    printf("Enter Class Grade Percentage: ");
    scanf("%f", &floGPAValue4);
    if (floGPAValue4 >= 90)
        floGPAValue4 = 4;
    else if (floGPAValue4 < 90 && floGPAValue4 >= 80)
        floGPAValue4 = 3;
    else if (floGPAValue4 < 80 && floGPAValue4 >= 70)
        floGPAValue4 = 2;
    else if (floGPAValue4 < 70 && floGPAValue4 >= 60)
        floGPAValue4 = 1;
    else floGPAValue4 = 0;
    floGPAValue4 = floGPAValue4 * intCredits4;
    intCurrentCredits = intCurrentCredits + intCredits4;
    if (intCurrentCredits == intTotalCredits)
    {
        intTotalHours = floGPAValue1 + floGPAValue2 + floGPAValue3 + floGPAValue4;
        floGPA = intTotalHours / intTotalCredits;
        printf("Class #1: %s\n", strClass1);
        printf("Class ID: %s\n", strID1);
        printf("Class #2: %s\n", strClass2);
        printf("Class ID: %s\n", strID2);
        printf("Class #3: %s\n", strClass3);
        printf("Class ID: %s\n", strID3);
        printf("Class #4: %s\n", strClass4);
        printf("Class ID: %s\n", strID4);
        printf("Your GPA Is: %f", floGPA);
        system("pause");
    }
    
    //SECTION FIVE
    fflush(stdin);
    printf("Enter Class Name: ");
    gets(strClass5);
    printf("Enter Class ID: ");
    gets(strID5);
    printf("Enter Class Credit Hours: ");
    scanf("%d", &intCredits5);
    printf("Enter Class Grade Percentage: ");
    scanf("%f", &floGPAValue5);
    if (floGPAValue5 >= 90)
        floGPAValue5 = 4;
    else if (floGPAValue5 < 90 && floGPAValue5 >= 80)
        floGPAValue5 = 3;
    else if (floGPAValue5 < 80 && floGPAValue5 >= 70)
        floGPAValue5 = 2;
    else if (floGPAValue5 < 70 && floGPAValue5 >= 60)
        floGPAValue5 = 1;
    else floGPAValue5 = 0;
    floGPAValue5 = floGPAValue5 * intCredits5;
    intCurrentCredits = intCurrentCredits + intCredits5;
    if (intCurrentCredits == intTotalCredits)
    {
        intTotalHours = floGPAValue1 + floGPAValue2 + floGPAValue3 + floGPAValue4 + floGPAValue5;
        floGPA = intTotalHours / intTotalCredits;
        printf("Class #1: %s\n", strClass1);
        printf("Class ID: %s\n", strID1);
        printf("Class #2: %s\n", strClass2);
        printf("Class ID: %s\n", strID2);
        printf("Class #3: %s\n", strClass3);
        printf("Class ID: %s\n", strID3);
        printf("Class #4: %s\n", strClass4);
        printf("Class ID: %s\n", strID4);
        printf("Class #5: %s\n", strClass5);
        printf("Class ID: %s\n", strID5);
        printf("Your GPA Is: %f", floGPA);
        system("pause");
    }
    
    //SECTION SIX
    fflush(stdin);
    printf("Enter Class Name: ");
    gets(strClass6);
    printf("Enter Class ID: ");
    gets(strID6);
    printf("Enter Class Credit Hours: ");
    scanf("%d", &intCredits6);
    printf("Enter Class Grade Percentage: ");
    scanf("%f", &floGPAValue6);
    if (floGPAValue6 >= 90)
        floGPAValue6 = 4;
    else if (floGPAValue6 < 90 && floGPAValue6 >= 80)
        floGPAValue6 = 3;
    else if (floGPAValue6 < 80 && floGPAValue6 >= 70)
        floGPAValue6 = 2;
    else if (floGPAValue6 < 70 && floGPAValue6 >= 60)
        floGPAValue6 = 1;
    else floGPAValue6 = 0;
    floGPAValue6 = floGPAValue6 * intCredits6;
    intCurrentCredits = intCurrentCredits + intCredits6;
    if (intCurrentCredits == intTotalCredits)
    {
        intTotalHours = floGPAValue1 + floGPAValue2 + floGPAValue3 + floGPAValue4 + floGPAValue5 + floGPAValue6;
        floGPA = intTotalHours / intTotalCredits;
        printf("Class #1: %s\n", strClass1);
        printf("Class ID: %s\n", strID1);
        printf("Class #2: %s\n", strClass2);
        printf("Class ID: %s\n", strID2);
        printf("Class #3: %s\n", strClass3);
        printf("Class ID: %s\n", strID3);
        printf("Class #4: %s\n", strClass4);
        printf("Class ID: %s\n", strID4);
        printf("Class #5: %s\n", strClass5);
        printf("Class ID: %s\n", strID5);
        printf("Class #6: %s\n", strClass6);
        printf("Class ID: %s\n", strID6);
        printf("Your GPA Is: %f", floGPA);
        system("pause");
    }
    
    //SECTION SEVEN
    fflush(stdin);
    printf("Enter Class Name: ");
    gets(strClass7);
    printf("Enter Class ID: ");
    gets(strID7);
    printf("Enter Class Credit Hours: ");
    scanf("%d", &intCredits7);
    printf("Enter Class Grade Percentage: ");
    scanf("%f", &floGPAValue7);
    if (floGPAValue7 >= 90)
        floGPAValue7 = 4;
    else if (floGPAValue7 < 90 && floGPAValue7 >= 80)
        floGPAValue7 = 3;
    else if (floGPAValue7 < 80 && floGPAValue7 >= 70)
        floGPAValue7 = 2;
    else if (floGPAValue7 < 70 && floGPAValue7 >= 60)
        floGPAValue7 = 1;
    else floGPAValue7 = 0;
    floGPAValue7 = floGPAValue7 * intCredits7;
    intCurrentCredits = intCurrentCredits + intCredits7;
    if (intCurrentCredits == intTotalCredits)
    {
        intTotalHours = floGPAValue1 + floGPAValue2 + floGPAValue3 + floGPAValue4 + floGPAValue5 + floGPAValue6 + floGPAValue7;
        floGPA = intTotalHours / intTotalCredits;
        printf("Class #1: %s\n", strClass1);
        printf("Class ID: %s\n", strID1);
        printf("Class #2: %s\n", strClass2);
        printf("Class ID: %s\n", strID2);
        printf("Class #3: %s\n", strClass3);
        printf("Class ID: %s\n", strID3);
        printf("Class #4: %s\n", strClass4);
        printf("Class ID: %s\n", strID4);
        printf("Class #5: %s\n", strClass5);
        printf("Class ID: %s\n", strID5);
        printf("Class #6: %s\n", strClass6);
        printf("Class ID: %s\n", strID6);
        printf("Class #7: %s\n", strClass7);
        printf("Class ID: %s\n", strID7);
        printf("Your GPA Is: %f", floGPA);
        system("pause");
    }
    
    //END OF CODE

    system("pause");
    return 0;
}