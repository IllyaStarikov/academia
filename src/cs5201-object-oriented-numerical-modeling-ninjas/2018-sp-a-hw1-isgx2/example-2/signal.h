//   File Name: signal.h
//   Function:  Define the class for exception message
//   Author:    Franck Xia
//   Creation:  Oct. 10, 2001

#ifndef SIGNAL_H_42431
#define SIGNAL_H_42431

class CSignal
{
   private:
      char message[80];
   public:
      CSignal(const char* s );
      char* get_message() const;
};

#endif

