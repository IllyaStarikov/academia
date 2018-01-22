//  File Name:  scanner.h
//  Function:   Define CScanner class
//  Author:     Franck Xia
//  Creation:   Nov. 3, 2001
//  Modified:   Nov. 10, 2002
//  Modified:   Nov. 17, 2002 AJB

#ifndef SCANNER_H_42431
#define SCANNER_H_42431
#include <string>
#include "enChar.h"
#include "tokenlist.h"

const int MAX_LEX_SIZE = 30;
const int MAX_STT_LENGTH = 80;

class CScanner
{
   public:
      CScanner();
      void generate_token_list( std::string );
      CToken_List get_token_list() const;
   
   private:
      std::string m_strCommand;
      CToken_List m_IToken;
      std::string lexeme;
      enTokens lex_type;
      char next_char;
      enChar next_char_type;
      int next_pos_in_lex;
      int next_pos_in_cmd;
      int no_char_in_cmd;
      
      void get_char_set_type();
      void add_char();
      void lex();
};

#endif


