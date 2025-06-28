// Programmer: Illya Starikov
// Section: 3E
// File: Time.cpp
// Description: Time class definition

#include <iostream>
#include "Time.h"

const int MAX_HOUR = 23;
const int MAX_MINUTE = 59;
const int MAX_SECOND = 59;

// No namespaces.

void Time::readIn()
{
  bool validData;

  do
  {
    std::cout << "Enter The Hour: ";
    std::cin >> hour;

    validData = (hour <= MAX_HOUR) ? true: false;

    if (validData == false)
      std::cout << "Invalid Hour" << std::endl;
  } while (validData == false);

  do
  {
    std::cout << "Enter The Minute: ";
    std::cin >> minute;

    validData = (minute <= MAX_MINUTE) ? true: false;

    if (validData == false)
      std::cout << "Invalid Minute"  << std::endl;
  } while (validData == false);

  do
  {
    std::cout << "Enter The Second: ";
    std::cin >> second;

    validData = (second <= MAX_SECOND) ? true: false;

    if (validData == false)
      std::cout << "Invalid Minute"  << std::endl;
  } while (validData == false);
}

void Time::printOut()const
{
  std::cout << "Time: " << hour << ":" << minute << ":" << second
  << std::endl;
}

void Time::nextSecond()const
{
  // Previous and Next Second are not elegant solution, but it works well
  // and is easy to follow.
  // Something I have diffulty with — Overcomplicating htings.
  int
  localSecond = second,
  localMinute = minute,
  localHour = hour;

  localSecond += 1;

  if (localSecond == 60)
  {
    localSecond = 0;
    localMinute += 1;
    if (localMinute == 60)
    {
      localMinute = 0;
      localHour += 1;
      if (localHour == 24)
      {
        localHour = 0;
      }
    }
  }

  std::cout << "Next Second: " << localHour << ":" << localMinute << ":"
    << localSecond << std::endl;
}
void Time::previousSecond()const
{
  int
  localSecond = second,
  localMinute = minute,
  localHour = hour;
  localSecond -= 1;

  if (localSecond == - 1)
  {
    localSecond = 59;
    localMinute -= 1;
    if (localMinute == - 1)
    {
      localMinute = 59;
      localHour -= 1;
      if (localHour == -1)
      {
        localHour = 23;
      }
    }
  }

  std::cout << "Previous Second: " << localHour << ":" << localMinute
    << ":" << localSecond << std::endl;
}