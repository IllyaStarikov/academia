//   File Name: enTokens.h
//   Function:  Define the enumeration types for tokens
//              and struct for single character lexeme with token type
//   Author:    Franck Xia
//   Creation:  Oct. 10, 2001

#ifndef ENTOKENS_H_42431
#define ENTOKENS_H_42431

enum enTokens
{
   ADDOP = 0,
   MULTOP,
   SUBOP,
   DIVOP,
   ASSIGNOP,
   FLOATLIT,
   ID,
   LPAREN,
   RPAREN,
   LBRACK,
   RBRACK,
   PERIOD,
   SEMICOL,
   COMMA,
   LESS,
   EQUAL,
   GREAT,
   QUEST,
   QUIT,
   CLEAR,
   WHO,
   WHOS,
   SCANEOF,
   U          // undefined
};

// type for record with single chracter lexeme and its token type

typedef struct
{
   char     lexeme;
   enTokens lex_type;
}  lexeme_type_t;

#endif

