//
//  main.c
//  Program V
//
//  Created by Illya Starikov on 5/2/14.
//  Copyright (c) 2014 iTz iLLi Production. All rights reserved.
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

typedef struct Cards
{
    char Suit[10];
    int Value;
    char Delt;
}aDeck;

aDeck myDeck[52];

int main(void)
{
    int Value;
    char charDelt = 'Y';
    char Diamonds, Hearts, Spades, Clubs;
    char myDeck, aDeck;
    int x=0, y=0, i = 0;
    
    
    for (int x=0; x < 4; x++)
    {
        for(int y=0; y < 13; y++)
        {
            switch (x)
            {
                case 0:
                    strcpy(myDeck[y].Suit, “Diamonds”);
                    myDeck[y].Value = y;
                    myDeck[y].Delt = 'y';
                    break;
                    
                case 1:
                    strcpy(myDeck[y].Suit, “Clubs”);
                    myDeck[y].Value = y;
                    myDeck[y].Delt = "y";
                    break;
                    
                case 2:
                    strcpy(myDeck[y].Suit, “Spades”);
                    myDeck[y].Value = "y";
                    myDeck[y].Delt = "y";
                    break;
                    
                case 3:
                    strcpy(myDeck[y].Suit, “Hearts”);
                    myDeck[y].Value = "y";
                    myDeck[y].Delt = "y";
                    break;
            }
            printf("Your Hand Is:");
        }
