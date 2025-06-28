//
//  main.c
//  Distance Calculator
//
//  Created by Illya Starikov on 1/29/14.
//  Copyright (c) 2014 iTz iLLi Production. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#define conMinutesPerHour 60;

int main(void)
{
    float floDistance, floSpeed, floTravelTime;;
    int intDepartureHours, intDepartureMinutes, intArrivalHours, intArrivalMinutes, intHours, intMinutes;
    
    printf("The Amazing Time Estimater\n\n");
   
//  Enter Program Data
    printf("What is the Total Distance: ");
    scanf("%f", &floDistance);
    printf("What is the Speed: ");
    scanf("%f", &floSpeed);
    printf("Your Departure Time(Hours:Mins): ");
    scanf("%d:%d", &intDepartureHours, &intDepartureMinutes);
    
//Calculate Travel Time
    floTravelTime = floDistance / floSpeed;
    intHours = floTravelTime;
    intMinutes = (floTravelTime - intHours) * conMinutesPerHour;
    intArrivalHours = (intDepartureHours + intHours + (intDepartureMinutes + intMinutes) / 60) % 24;
    intArrivalMinutes = (intDepartureMinutes + intMinutes) % conMinutesPerHour;
    
    
// Print the Results
    printf("\n\nArrival Time: %2d:%2d", intArrivalHours, intArrivalMinutes);
    return 0;
}