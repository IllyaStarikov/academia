/* parser.h
   Alex Berry
   CS 236 Program 5
   12/13/02
   Ins. Dr F. Xia.

   This file decalers the Parser class

   Program Updateded for attrib grammars.

   */

#ifndef PARSER_H_42431
#define PARSER_H_42431

#include "tokenlist.h"
#include "enTokens.h"
#include "Amatrix.h"

typedef int UINT;
typedef Amatrix<float> DenseMatrix;
#define MAXSIZE 10

class Parser
{
private:
   CToken_List tkl;  // Storage for the token list
   enTokens cur_tok; // the current token
   char sig[80];     // A temp string i used
   DenseMatrix m_dm;
   UINT m_Crow,m_Ccol;

public:
   /* Purpose: Default Cons.
      Pre:     None
      Post:    clears the token_list;
      */
   Parser(): m_dm(MAXSIZE,MAXSIZE) { tkl.clear(); }

   /* Purpose: Parses the program looking for errors
      Pre:     A valid list
      Post:    If there is no throw, all tokens have been matched and the
               program is valid
      */
   void parse(CToken_List & tl);


private:
   /* Purpose: Matches Tok to cur_tok
      Pre:     None
      Post:    If Tok==cur_tok it updates the list and
               goes on otherwise error
      */
   void match(const enTokens Tok);

   /* Purpose: These are all the functions of teh recursive descent parser
               Each one is a production from the grammer
      Pre:     None
      Post:    Error if there is no match or no case for the cur_tok otherwise
               everything should be fine.
      */
   void program();
   void stmt_list();
   void stmt();
   void expr(UINT &es_row,UINT &es_col,DenseMatrix &es_val);
   void term_tail(UINT tti_row, UINT tti_col,DenseMatrix& tti_val,
      UINT &tts_row, UINT &tts_col, DenseMatrix& tts_val);
   void term(UINT &ts_row,UINT &ts_col,DenseMatrix& ts_val);
   void factor_tail(UINT fti_row, UINT fti_col,DenseMatrix &fti_val,
      UINT &fts_row, UINT &fts_col, DenseMatrix& fts_val);
   void factor(UINT &fs_row,UINT &fs_col,DenseMatrix &fs_val);
   void matrix(UINT &ms_row,UINT &ms_col,DenseMatrix &ms_val);
   void row_tail(UINT rti_row,UINT rti_col,UINT &rts_row);
   void row(UINT &rs_col);
   void lit_tail(UINT lti_col,UINT &lts_col);
   void command();
};


#endif /*PARSER_H_42431*/

