//   File Name: token.h
//   Function:  Define the token class
//   Interface: The class has only two public interface methods
//               1. get_lex() returns the lexeme 
//               2. get_token_type() returns the token type of the lexeme
//   Author:    Franck Xia
//   Creation:  Oct. 10, 2001


#ifndef TOKEN_H_42431
#define TOKEN_H_42431
#include <iostream>
using std::ostream;

#include <string>
#include "enTokens.h"

class CToken
{
   public:
      CToken();
      CToken( enTokens, std::string );   
      enTokens  get_token_type() const;
      std::string get_lex() const;
      
   private:
      std::string sLex;      // string for lexeme
      enTokens   tokType;    // token type for the lexeme
      //  the following converts the enumeration token type into string
      char* type_convert( enTokens );
      
      friend ostream & operator<<( ostream & os, CToken t );
};

#endif
