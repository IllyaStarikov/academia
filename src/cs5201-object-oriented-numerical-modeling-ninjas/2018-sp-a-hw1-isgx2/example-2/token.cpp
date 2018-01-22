//   File Name:    token.cpp
//   Function:     Define the token class member functions
//   Related Doc:  token.h contains the definition of the class
//   Author:       Franck Xia
//   Creation:     Oct. 10, 2001

#include "token.h"

extern char str_token_type[30][10];      // declared in driver.cpp as global

CToken::CToken()
{
   sLex = "";
   tokType = U;
}
      
CToken::CToken( enTokens t, std::string s )
{
   sLex = s;
   tokType = t;
}
     
enTokens CToken::get_token_type() const
{
   return tokType;
}

std::string CToken::get_lex() const
{
   return sLex;
}

char* CToken::type_convert( enTokens type )
{
   // use the global array for token type conversion
   return (char*)str_token_type[type];
}


ostream & operator<<( ostream & display, CToken token )
{
   // as a friend method, private data in CToken can be accessed dircetly
   display << "(" << token.type_convert(token.tokType) << "," << token.sLex << ")";
   return display;
}
