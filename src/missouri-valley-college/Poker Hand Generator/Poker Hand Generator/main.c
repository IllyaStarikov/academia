//
//  main.c
//  Poker Hand Generator
//
//  Created by Illya Starikov on 5/1/14.
//  Copyright (c) 2014 iTz iLLi Production. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define definedNumberOfintSuits 4
#define definedNumberOfintRanks 13

int main(void)
{
    bool boolInHand[definedNumberOfintSuits][definedNumberOfintRanks] = {false};
    int intNumberOfCards, intRank, intSuit;
    const char intRank_code[] = {'2' , '3' , '4' , '5', '6' , '7' , '8', '9' , 't' , 'j' , 'q' , 'k', 'a'};
    const char intSuit_code[] = {'c', 'd' , 'h' , 's'};
    
    srand((unsigned) time(NULL));
    
    printf("Enter Number of Cards In Hand: ");
    scanf("%d", &intNumberOfCards);
    
    printf("Your Hand:");
    while (intNumberOfCards > 0) {
        intSuit = rand() % definedNumberOfintSuits;
        intRank = rand() % definedNumberOfintRanks;
        if (!boolInHand[intSuit][intRank]) {
            intNumberOfCards--;
            printf(" %c%c", intRank_code[intRank], intSuit_code[intSuit]);
        }
    }
    printf("\n");
    
    return 0;
}

