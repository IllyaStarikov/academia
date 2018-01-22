//   File Name: signal.cpp
//   Function:  Implement the class for exception message
//   Author:    Franck Xia
//   Creation:  Oct. 10, 2001

#include "signal.h"
#include <string.h>

CSignal::CSignal(const char* s )
{
   strcpy( message, s );
}
      
char* CSignal::get_message() const
{
   return (char*)message;
}

