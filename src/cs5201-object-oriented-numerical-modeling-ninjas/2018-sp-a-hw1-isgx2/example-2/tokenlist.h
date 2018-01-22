//   File Name: tokenlist.h
//   Function:  Define the token list class
//              A standard template library list is used to store the token list.
//              The current position in the list is held is an iterator of the list
//   Interface:   1. get_current_token() returns the current token in the list
//                2. get_ccurent_token_type() returns the token type of the current lexeme
//                3. get_current_lex() returns the lexeme in the current token
//                4. next_token_type_peek() returns the token type of the next lexeme
//                   but current position in the list remain unchanged
//                5. is_end_of_list() test if the end of token list is reached
//                     the return value is Boolean
//                6. insert() push a new token in the end of the list 
//                7. moveahead() advances the current position in the list to the next token
//                8. set_at_start() sets the current position to the starting node of the list
//                9. clear() cleans the list 
//                10. << operator has been overloaded for a whole token list
//   Author:    Franck Xia
//   Creation:  Oct. 10, 2001

#ifndef TOKEN_LIST_H_42431
#define TOKEN_LIST_H_42431

#include <list>
#include <iterator>
#include "token.h"

class CToken_List
{
   public:
      CToken_List();
      void moveahead();    // equivalent of advance()
      void clear();
      void set_at_start();
      
      void insert( enTokens t, std::string s );
      void insert( CToken t );
      
      CToken get_current_token() const;
      enTokens get_current_token_type() const;
      std::string get_current_lex() const;
      enTokens next_token_type_peek();
      bool is_end_of_list() const;

   private:
      std::list<CToken> tokList;
      std::list<CToken>::iterator cur;
      
      friend ostream& operator<<( ostream& o, CToken_List tl );
};

#endif

