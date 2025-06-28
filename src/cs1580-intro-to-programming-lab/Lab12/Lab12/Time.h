// Programmer: Illya Starikov
// Section: 3E
// File: Time.h
// Description: Time class prototype

#ifndef Lab12__Time
#define Lab12__Time

/*
 Description: readIn. Read in data.
 Pre-Condition: None.
 Post-Condition: Gets the values for all member variables
 */

/*
 Description: printOut. Prints out the data.
 Pre-Condition: None.
 Post-Condition: None. Side affects.
 */

/*
 Description: nextSecond. Print out the next second.
 Pre-Condition: None.
 Post-Condition: Prints out the time incrememnted by one. Side affects.
 */

/*
 Description: previousSecond
 Pre-Condition: None.
 Post-Condition: Prints out previous second.
 */

class Time {
public:
  void readIn(); // get the hour, minute, second from the user
  // (make sure the input datare valid)
  void printOut()const; // print the time on the screen
  void nextSecond()const; // calculate time in the next second
  void previousSecond()const;// calculate time in the previous second


private:
  int hour;
  int minute;
  int second;
};
#endif /* defined(Lab12__Time) */
