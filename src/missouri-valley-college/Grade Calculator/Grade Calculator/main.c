//
//  main.c
//  Grade Calculator
//
//  Created by Illya Starikov on 2/19/14.
//  Copyright (c) 2014 iTz iLLi Production. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#define True 1
#define False 0
#define HomeworkPercent 0.15
#define FinalPercent 0.25

int main()
{
    int intChoice;
    int intHomeworkFlag1 = True, intHomeworkFlag2 = True, intHomeworkFlag3 = True;
    int intMidtermFlag1 = True, intMidtermFlag2 = True;
    int intFinalFlag = True, intGradeFlag = True;
    int Check;
    float floHomework1, floHomework2, floHomework3;
    float floMidTerm1, floMidTerm2;
    float floFinalExam, floFinalGrade;
    
    printf("\n\nGrade Calculation Program");
    printf("\nPlease Select the item to be Calculated: ");
    printf("\n(You will be asked to enter the others). \n\n");
    printf("Homework #1: (1)\n");
    printf("Homework #2: (2)\n");
    printf("Homework #3: (3)\n");
    printf("Midterm #1: (4)\n");
    printf("Midterm #2: (5)\n");
    printf("Final Exam : (6)\n");
    printf("Final Grade: (7) ");
    scanf("%d", &intChoice);
    if ((intChoice < 1) || (intChoice > 7))
    {
        printf("\n\nIncorrect intChoice !!!\n");
        return -1;
    }
    printf("\n\nYou Have Chosen To Calculate ");
    switch (intChoice)
    {
        case 1:
        {
            intHomeworkFlag1 = False;
            printf("HomeWork 1");
            break;
        }
        case 2:
        {
            intHomeworkFlag2 = False;
            printf("HomeWork 2");
            break;
        }
        case 3:
        {
            intHomeworkFlag3 = False;
            printf("HomeWork 3");
            break;
        }
        case 4:
        {
            intMidtermFlag1 = False;
            printf("Midterm 1");
            break;
        }
        case 5:
        {
            intMidtermFlag2 = False;
            printf("Midterm 2");
            break;
        }
        case 6:
        {
            intFinalFlag = False;
            printf("Final Exam");
            break;
        }
        case 7:
        {
            intGradeFlag = False;
            printf("Final Grade");
            break;
        }
    }
    printf("\n\n");
    if (intHomeworkFlag1)
    {
        printf("Please Enter homework #1: ");
        scanf("%f", &floHomework1);
    }
    if (intHomeworkFlag2)
    {
        printf("Please Enter homework #2: ");
        scanf("%f", &floHomework2);
    }
    if (intHomeworkFlag3)
    {
        printf("Please Enter homework #3: ");
        scanf("%f", &floHomework3);
    }
    if (intMidtermFlag1)
    {
        printf("Please Enter Midterm #1: ");
        scanf("%f", &floMidTerm1);
    }
    if (intMidtermFlag2)
    {
        printf("Please Enter Midterm #2: ");
        scanf("%f", &floMidTerm2);
    }
    if (intFinalFlag)
    {
        printf("Please Enter Final Exam: ");
        scanf("%f", &floFinalExam);
    }
    if (intGradeFlag)
    {
        printf("Please Enter Final Grade: ");
        scanf("%f", &floFinalGrade);
    }
    printf("\n\n");
    switch (intChoice)
    {
        case 1:
            floHomework1 = (floFinalGrade - (floHomework2 + floHomework3 + floMidTerm1 + floMidTerm2) * HomeworkPercent - floFinalExam * FinalPercent) / HomeworkPercent;
            printf("Homework #1 Score: %5.2f\n", floHomework1);
            break;
        case 2:
            floHomework2 = (floFinalGrade - (floHomework1 + floHomework3 + floMidTerm1 + floMidTerm2) * HomeworkPercent - floFinalExam * FinalPercent) / HomeworkPercent;
            Check = floFinalGrade - (floHomework1 + floHomework3 + floMidTerm1 + floMidTerm2) * HomeworkPercent - floFinalExam * FinalPercent;
            printf("Homework #2 Score: %5.2f\n", floHomework2);
            break;
        case 3:
            floHomework3 = (floFinalGrade - (floHomework1 + floHomework2 + floMidTerm1 + floMidTerm2) * HomeworkPercent - floFinalExam * FinalPercent) / HomeworkPercent;
            printf("Homework #3 Score: %5.2f\n", floHomework3);
            break;
        case 4:
            floMidTerm1 = (floFinalGrade - (floHomework1 + floHomework2 + floHomework3 + floMidTerm2) * HomeworkPercent - floFinalExam * FinalPercent) / HomeworkPercent;
            printf("Midterm #1 Score: %5.2f\n", floMidTerm1);
            break;
        case 5:
            floMidTerm2 = (floFinalGrade - (floHomework1 + floHomework2 + floHomework3 + floMidTerm1) * HomeworkPercent - floFinalExam * FinalPercent) / HomeworkPercent;
            printf("Midterm #2 Score: %5.2f\n", floMidTerm2);
            break;
        case 6:
            floFinalExam = (floFinalGrade - (floHomework1 + floHomework2 + floHomework3 + floMidTerm1 + floMidTerm2) * HomeworkPercent) / FinalPercent;
            printf("Final Exam Score: %5.2f\n", floFinalExam);
            break;
        case 7:
            floFinalGrade = (floHomework1 + floHomework2 + floHomework3 + floMidTerm1 + floMidTerm2) * HomeworkPercent + floFinalExam * FinalPercent;
            printf("Midterm #2 Score: %5.2f\n", floMidTerm2);
            break;
    }
    system("Pause");
    return 0;
}
#include <stdio.h>

