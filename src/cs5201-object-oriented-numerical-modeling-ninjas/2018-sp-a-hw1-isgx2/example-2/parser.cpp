/* parser.cpp
   Alex Berry
   CS 236 Program 5
   12/13/02
   Ins. Dr F. Xia.

   This file defines the Parser class
   */

#include "parser.h"
#include "signal.h"
#include "stdio.h"
#include <iostream>
#include <stdlib.h>
using std::cout;
using std::endl;

//#define OUTPUT
// Compiling with -DOUTPUT will make the program show each time
// a productions is applied.  Compiling without it supresses the
// output
#ifdef OUTPUT
#define _OUT(exp); exp
#else
#define _OUT(exp); ;
#endif

extern char str_token_type[30][10];
void Parser::parse(CToken_List & tl)
{
      /* Update all of the local vars */
   tkl=tl;
   tkl.set_at_start();
   cur_tok=tkl.get_current_token_type();
   m_Crow=m_Ccol=0;
      /* Start the parsing */
   _OUT(cout<<"calling program()"<<endl;);
   program();
      /* Match the last token */
   match(SCANEOF);
}

void Parser::match(const enTokens Tok)
{
   if(cur_tok == Tok)
   {
      if(cur_tok==FLOATLIT)
      {
         if(m_Crow >= MAXSIZE || m_Ccol >= MAXSIZE)
         {
            sprintf(sig,"Matrix bigger than max size: %d",MAXSIZE);
            throw(CSignal(sig));
         }
         m_dm(m_Crow-1,m_Ccol-1,atof(&(tkl.get_current_lex())[0]));
      }
      try   /* To moveahead */
      {
         tkl.moveahead();
         cur_tok=tkl.get_current_token_type();
      }
      catch(CSignal signal)   // if move ahead fails
      {
            // if its not the end fo the program throw an error */
         if(cur_tok != SCANEOF)
         {
            sprintf(sig,"Ran Out of input tokens after: %s",str_token_type[cur_tok]);
            throw(CSignal(sig));
         }
      }
   }
   else
   {
         // Error if the tokens do not match
      sprintf(sig,"Found: %s Looking for: %s",str_token_type[cur_tok],
                                            str_token_type[Tok]);
      throw(CSignal(sig));
   }
}

void Parser::program()
{
   switch (cur_tok)
   {
         // P -> SL
   case ID:   case QUIT: case CLEAR:
   case WHOS: case WHO:  case SCANEOF:
      _OUT(cout<<"program -> stmt_list"<<endl;);
      stmt_list();
      break;
   default:
      sprintf(sig,"program() parse error before: %s",str_token_type[cur_tok]);
      throw(CSignal(sig));
   }
}
void Parser::stmt_list()
{
   switch(cur_tok)
   {  // SL -> S
   case ID:   case QUIT: case CLEAR:
   case WHOS: case WHO:
      _OUT(cout<<"stmt_list -> stmt"<<endl;);
      stmt(); match(SEMICOL); stmt_list();
      break;
   case SCANEOF:     //SL -> ep
      _OUT(cout<<"stmt_list -> ep"<<endl;);
      break;
   default:
      sprintf(sig,"stmt_list() parse error before: %s",str_token_type[cur_tok]);
      throw(CSignal(sig));
   }
}

void Parser::stmt()
{ 
   UINT row=0,col=0;
   DenseMatrix DM;
   switch(cur_tok)
   {
   case ID: //S -> id = expr
      _OUT(cout<<"stmt -> id = expr"<<endl;);
      match(ID); match(ASSIGNOP); expr(row,col,DM);
         /* here we output the val of expr since we cant do the
            assignment. */
      cout<<"Result of expr:\n"<<DM;
      break;
   case QUIT:  case CLEAR: //S -> command
   case WHO:   case WHOS:
      _OUT(cout<<"stmt -> command"<<endl;);
      command();
      break;
   default:
      sprintf(sig,"stmt() parse error before: %s",str_token_type[cur_tok]);
      throw(CSignal(sig));
   }
}

void Parser::expr(UINT &es_row,UINT &es_col,DenseMatrix &es_val)
{  
   UINT ts_row,ts_col;
   DenseMatrix ts_val;

   switch(cur_tok)
   {
   case ID:       case FLOATLIT: // expr -> term term_tail
   case LPAREN:   case LBRACK:
      _OUT(cout<<"expr -> term term_tail"<<endl;);
      term(ts_row,ts_col,ts_val);
      term_tail(ts_row,ts_col,ts_val,es_row,es_col,es_val);
      break;
   default:
      sprintf(sig,"expr() parse error before: %s",str_token_type[cur_tok]);
      throw(CSignal(sig));
   }
}

void Parser::term_tail(UINT tti_row, UINT tti_col,DenseMatrix &tti_val,
                       UINT &tts_row, UINT &tts_col,DenseMatrix &tts_val)
{  
   UINT t2s_row,t2s_col;
   DenseMatrix t2s_val;

   switch(cur_tok)
   {
   case ADDOP:       //term_tail -> + term term_tail
      _OUT(cout<<"term_tail -> + term term_tail"<<endl;);
      match(ADDOP); 
      term(t2s_row,t2s_col,t2s_val);
         //First two if's for lit + mat and mat + lit and
         //the seconed two check for attrib errors.
      if(t2s_row == t2s_col && t2s_row == MAXSIZE+1)
      {
         t2s_val=tti_val+t2s_val(0,0);
         t2s_row=tti_row;
         t2s_col=tti_col;
      }
      else if(tti_row == tti_col && tti_row == MAXSIZE+1)
         t2s_val=t2s_val+tti_val(0,0);
      else if(tti_row != t2s_row)
      {
         sprintf(sig,"term_tail() attribute error (+op) rows: %d != %d",
            tti_row,t2s_row);
         throw(CSignal(sig));
      }
      else if(tti_col != t2s_col)
      {
         sprintf(sig,"term_tail() attribute error (+op) cols: %d != %d",
            tti_col,t2s_col);
         throw(CSignal(sig));
      }
      else
         t2s_val=tti_val+t2s_val;

      term_tail(t2s_row,t2s_col,t2s_val,tts_row,tts_col,tts_val);
      break;
   case SUBOP:       //term_tail -> - term term_tail
      _OUT(cout<<"term_tail -> - term term_tail"<<endl;);
      match(SUBOP); 
      term(t2s_row,t2s_col,t2s_val); 
         //First two if's for lit - mat and mat - lit and
         //the seconed two check for attrib errors.
      if(t2s_row == t2s_col && t2s_row == MAXSIZE+1)
      {
         t2s_val=tti_val-t2s_val(0,0);
         t2s_row=tti_row;
         t2s_col=tti_col;
      }
      else if(tti_row == tti_col && tti_row == MAXSIZE+1)
      {
         for(UINT i=0,j;i<t2s_row;i++)
            for(j=0;j<t2s_col;j++)
               t2s_val(i,j,tti_val(0,0)-t2s_val(i,j));
      }
      else if(tti_row != t2s_row)
      {
         sprintf(sig,"term_tail() attribute error (-op) rows: %d != %d",
            tti_row,t2s_row);
         throw(CSignal(sig));
      }
      else if(tti_col != t2s_col)
      {
         sprintf(sig,"term_tail() attribute error (-op) cols: %d != %d",
            tti_col,t2s_col);
         throw(CSignal(sig));
      }
      else
         t2s_val=tti_val+t2s_val;
      term_tail(t2s_row,t2s_col,t2s_val,tts_row,tts_col,tts_val);
      break;
   case RPAREN:   case SEMICOL:  // term_tail -> ep
      _OUT(cout<<"term_tail -> ep"<<endl;);
      tts_row=tti_row;
      tts_col=tti_col;
      tts_val=tti_val;
      break;
   default:
      sprintf(sig,"term_tail() parse error before: %s",
         str_token_type[cur_tok]);
      throw(CSignal(sig));
   }

}

void Parser::term(UINT &ts_row,UINT &ts_col,DenseMatrix &ts_val)
{  
   UINT fs_row,fs_col;
   DenseMatrix fs_val;

   switch(cur_tok)
   {     // term -> factor factor_tail
   case ID: case FLOATLIT: case LPAREN: case LBRACK:
      _OUT(cout<<"term -> factor factor_tail"<<endl;);
      factor(fs_row,fs_col,fs_val); 
      factor_tail(fs_row,fs_col,fs_val,ts_row,ts_col,ts_val);
      break;
   default:
      sprintf(sig,"term() parse error before: %s",str_token_type[cur_tok]);
      throw(CSignal(sig));
   }
}
 
void Parser::factor_tail(UINT fti_row, UINT fti_col,DenseMatrix &fti_val
                         ,UINT &fts_row, UINT &fts_col,DenseMatrix &fts_val)
{  
   UINT f2s_row,f2s_col;
   DenseMatrix f2s_val;
   switch(cur_tok)
   {
   case MULTOP:   // factor_tail -> * factor factor_tail
      _OUT(cout<<"factor_tail -> * factor factor_tail"<<endl;);
      match(MULTOP); 
      factor(f2s_row,f2s_col,f2s_val);
         //First two if's for lit * mat and mat * lit and
         //the last checks for attrib errors.
      if(f2s_row == f2s_col && f2s_row == MAXSIZE+1)
      {
         f2s_val=fti_val*f2s_val(0,0);
         f2s_row=fti_row;
         f2s_col=fti_col;
      }
      else if(fti_row == fti_col && fti_row == MAXSIZE+1)
         f2s_val=f2s_val*fti_val(0,0);
      else if(fti_col != f2s_row)
      {
         sprintf(sig,"factor_tail() attribute error (*op) cols1 != rows2: %d != %d",
            fti_col,f2s_row);
         throw(CSignal(sig));
      }
      else 
         f2s_val=fti_val*f2s_val;
      factor_tail(f2s_row,f2s_col,f2s_val,fts_row,fts_col,fts_val);
      break;
   case ADDOP: case SUBOP: case RPAREN: case SEMICOL: //factor_tail-> ep
      _OUT(cout<<"factor_tail -> ep"<<endl;);
      fts_row=fti_row;
      fts_col=fti_col;
      fts_val=fti_val;
      break;
   default:
      sprintf(sig,"factor_tail() parse error before: %s",str_token_type[cur_tok]);
      throw(CSignal(sig));
   }
}
 
void Parser::factor(UINT &fs_row,UINT &fs_col,DenseMatrix &fs_val)
{  
   switch(cur_tok)
   {
   case ID:       //factor -> id
      _OUT(cout<<"factor -> id"<<endl;);
      match(ID);
      fs_row=fs_col=MAXSIZE+2;
      fs_val.ReSize(1,1);
      break;
   case FLOATLIT: //factor -> literal
      _OUT(cout<<"factor -> literal"<<endl;);
      m_Crow=m_Ccol=1;
      match(FLOATLIT);
      fs_row=fs_col=MAXSIZE+1;
      fs_val.ReSize(1,1);
      fs_val(0,0,m_dm(0,0));
      break;
   case LPAREN:   //factor -> (expr)
      _OUT(cout<<"factor -> (expr)"<<endl;);
      match(LPAREN); expr(fs_row,fs_col,fs_val); match(RPAREN);
      break;
   case LBRACK:   //factor -> matrix
      _OUT(cout<<"factor -> matrix"<<endl;);
      matrix(fs_row,fs_col,fs_val);
      break;
   default:
      sprintf(sig,"factor() parse error before: %s",str_token_type[cur_tok]);
      throw(CSignal(sig));
   }
}
 
void Parser::matrix(UINT &ms_row,UINT &ms_col,DenseMatrix &ms_val)
{  
   UINT rti_row=1;
   switch(cur_tok)
   {
   case LBRACK:   //matrix -> [ row row_tail ]
      _OUT(cout<<"matrix -> [ row row_tail ]"<<endl;);
      match(LBRACK);
      m_Crow=1;
      row(ms_col); 
      row_tail(rti_row,ms_col,ms_row);
      ms_val.ReSize(ms_row,ms_col);
      for(UINT i=0,j;i<ms_row;i++)
         for(j=0;j<ms_col;j++)
            ms_val(i,j,m_dm(i,j));
      match(RBRACK);
      break;
   default:
      sprintf(sig,"matrix() parse error before: %s",str_token_type[cur_tok]);
      throw(CSignal(sig));
   }
}
 
void Parser::row_tail(UINT rti_row,UINT rti_col,UINT &rts_row)
{  
   UINT rs_col;
   switch(cur_tok)
   {
   case SEMICOL:  // row_tail -> row row_tail
      _OUT(cout<<"row_tail -> row row_tail"<<endl;);
      match(SEMICOL);
      m_Crow=rti_row+1;
      row(rs_col);
      if(rs_col != rti_col)
      {
         sprintf(sig,"row_tail() attribute error cols: %d != %d",
            rs_col,rti_col);
         throw(CSignal(sig));
      }
      row_tail(rti_row+1,rti_col,rts_row);
      break;
   case RBRACK:   // row_tail -> ep
      _OUT(cout<<"row_tail -> ep"<<endl;);
      rts_row=rti_row;
      break;
   default:
      sprintf(sig,"row_tail() parse error before: %s",str_token_type[cur_tok]);
      throw(CSignal(sig));
   }
}

void Parser::row(UINT &rs_col)
{  
   switch(cur_tok)
   {
   case FLOATLIT:    // row -> literal literal_tail
      _OUT(cout<<"row -> literal literal_tail"<<endl;);
      m_Ccol=1;
      match(FLOATLIT); 
      lit_tail(1,rs_col);
      break;
   default:
      sprintf(sig,"row() parse error before: %s",str_token_type[cur_tok]);
      throw(CSignal(sig));
   }
}

void Parser::lit_tail(UINT lti_col,UINT &lts_col)
{  
   switch(cur_tok)
   {
   case COMMA:    // literal_tail -> , literal lit_tail
      _OUT(cout<<"literal_tail -> , literal lit_tail"<<endl;);
      match(COMMA); 
      m_Ccol=lti_col+1;
      match(FLOATLIT); 
      lit_tail(lti_col+1,lts_col);
      break;
   case SEMICOL: case RBRACK: // literal_tail -> ep
      _OUT(cout<<"literal_tail -> ep"<<endl;);
      lts_col=lti_col;
      break;
   default:
      sprintf(sig,"lit_tail() parse error before: %s",str_token_type[cur_tok]);
      throw(CSignal(sig));
   }
}

void Parser::command()
{  
   switch(cur_tok)
   {
   case QUIT:  //command -> quit
      _OUT(cout<<"command -> quit"<<endl;);
      match(QUIT);
      break;      
   case WHO:   //command ->who
      _OUT(cout<<"command ->who"<<endl;);
      match(WHO);
      break;
   case WHOS:  //command ->whos
      _OUT(cout<<"command ->whos"<<endl;);
      match(WHOS);
      break;
   case CLEAR: //command ->clear
      _OUT(cout<<"command ->clear"<<endl;);
      match(CLEAR);
      break;
   default:
      sprintf(sig,"command() parse error before: %s",str_token_type[cur_tok]);
      throw(CSignal(sig));
   }
}


