//
// main.c
// Procedural Programming Project 1
//
// Created by Illya Starikov on 2/3/14.
// Copyright (c) 2014 iTz iLLi Production. All rights reserved.
//

#include <stdio.h>

int main(void)
{
    int R1C1, R1C2, R1C3, R1C4, R1C5;
    int R2C1, R2C2, R2C3, R2C4, R2C5;
    int R3C1, R3C2, R3C3, R3C4, R3C5;
    int R4C1, R4C2, R4C3, R4C4, R4C5;
    int R5C1, R5C2, R5C3, R5C4, R5C5;
    
    int sumR1, sumR2, sumR3, sumR4, sumR5;
    int sumC1, sumC2, sumC3, sumC4, sumC5;
    int sumLR, sumRL;
    
    printf("The Amazing Column Calculator\n");
    
    printf("Enter 5 Set of Numbers - Seperate By Spaces: ");
    scanf(" %d %d %d %d %d", &R1C1, &R1C2, &R1C3, &R1C4, &R1C5);
    printf("Enter 5 Set of Numbers - Seperate By Spaces: ");
    scanf(" %d %d %d %d %d", &R2C1, &R2C2, &R2C3, &R2C4, &R2C5);
    printf("Enter 5 Set of Numbers - Seperate By Spaces: ");
    scanf(" %d %d %d %d %d", &R3C1, &R3C2, &R3C3, &R3C4, &R3C5);
    printf("Enter 5 Set of Numbers - Seperate By Spaces: ");
    scanf(" %d %d %d %d %d", &R4C1, &R4C2, &R4C3, &R4C4, &R4C5);
    printf("Enter 5 Set of Numbers - Seperate By Spaces: ");
    scanf(" %d %d %d %d %d", &R5C1, &R5C2, &R5C3, &R5C4, &R5C5);
    
    
    sumR1 = R1C1 + R1C2 + R1C3 + R1C4 + R1C5;
    sumR2 = R2C1 + R2C2 + R2C3 + R2C4 + R2C5;
    sumR3 = R3C1 + R3C2 + R3C3 + R3C4 + R3C5;
    sumR4 = R4C1 + R4C2 + R4C3 + R4C4 + R4C5;
    sumR5 = R5C1 + R5C2 + R5C3 + R5C4 + R5C5;
    
    sumC1 = R1C1 + R2C1 + R3C1 + R4C1 + R5C1;
    sumC2 = R1C2 + R2C2 + R3C2 + R4C2 + R5C2;
    sumC3 = R1C3 + R2C3 + R3C3 + R4C3 + R5C3;
    sumC4 = R1C4 + R2C4 + R3C4 + R4C4 + R5C4;
    sumC5 = R1C5 + R2C5 + R3C5 + R4C5 + R5C5;
    
    sumLR = R1C1 + R2C2 + R3C3 + R4C4 + R5C5;
    sumRL = R1C5 + R2C4 + R3C3 + R4C2 + R5C1;
    
    printf("\n-------------###-------------\n\n");
    printf(" %d %d %d %d %d | Sum: %d\n", R1C1, R1C2, R1C3, R1C4, R1C5, sumR1);
    printf(" %d %d %d %d %d | Sum: %d\n", R2C1, R2C2, R2C3, R2C4, R2C5, sumR2);
    printf(" %d %d %d %d %d | Sum: %d\n", R3C1, R3C2, R3C3, R3C4, R3C5, sumR3);
    printf(" %d %d %d %d %d | Sum: %d\n", R4C1, R4C2, R4C3, R4C4, R4C5, sumR4);
    printf(" %d %d %d %d %d | Sum: %d\n\n", R5C1, R5C2, R5C3, R5C4, R5C5, sumR5);
    
    printf(" %d %d %d %d %d | Sum: %d\n", R1C1, R1C2, R1C3, R1C4, R1C5, sumR1);
    printf(" %d %d %d %d %d\n", sumC1, sumC2, sumC3, sumC4, sumC5);
    printf("\n-------------###-------------\n");
    printf("Diagnol:%d\n", sumLR);
    printf("Diagnol:%d", sumRL);
}