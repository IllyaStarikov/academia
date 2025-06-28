//
//  main.c
//  Project IV
//
//  Created by Illya Starikov on 4/4/14.
//  Copyright (c) 2014 iTz iLLi Production. All rights reserved.
//

#include <stdio.h>
#include <string.h>

int main(void)
{
    char strStudent[25][25];
    int intScores[25];
    
    char strTemporaryName[20];
    int intTemporaryScore;
    
    char strName[25];
    int intScr = 0;
    int intCounter = 0;
    int intMean, intMedian, intMode;
    char Trans = "Y";
    int intTotalScore;
    
    do
    {
      printf("Enter Student Name: ");
      gets(strName);
        
      if(strName != "")
      {
          strcpy(strStudent[intCounter], strName);
          printf("Enter Score: ");
          scanf("%d", intScr);
          if (intScr >= 0 && intScr <= 100)
              intScores[intCounter] = intScr;
          intCounter += 1;
      }
    } while (strName != "");
    
    while (Trans == "Y")
    {
        Trans == "N";
        for (int i=0, i < intCounter - 2; i++)
        {
        if (intScores[i] < intScores [i+1])
            intTemporaryScore = intScores[i];
            intScores[i] = intScores[i+1];
            intScores[i] = intTemporaryScore;
            strTemporaryName = strStudent[i];
            strStudent[i] = strStudent[i+1];
            strStudent[i+1] = strTemporaryName;
            Trans = "Y";
        }
        
        
        for (int i=0; i < intCounter; i++)
            if Score[i] != 0
                mode[intScores[i]] += 1;
        
        for (int i = 0; i < intCounter; i++)
            intTotalScore += intScores[i];
        intMean = intTotalScore / intCounter;
        
        
        printf("Mean: %d", intMean);
        printf("Median: %d", intMedian);
        printf("Mode: %d", intMedian);
}