//  File Name:  scanner.cpp
//  Function:   Implement CScanner member functions
//  Author:     Franck Xia
//  Creation:   Nov. 3, 2001
//  Modified:   Nov. 10, 2002

#include "scanner.h"
#include "signal.h"
using std::cout;
using std::endl;

CScanner::CScanner()
{
   m_IToken.clear();
   m_strCommand.resize(MAX_STT_LENGTH);
   lexeme.resize(MAX_LEX_SIZE);
}
     
void CScanner::generate_token_list( std::string sttment )
{
   next_pos_in_cmd = 0;
   no_char_in_cmd = sttment.length() ;
   
   m_strCommand = sttment;
   next_char_type = BLANK;     // no char read yet.

   // initailized token list
   m_IToken.clear();
   
   while( next_pos_in_cmd <= no_char_in_cmd )
   {
   //  start a new lexeme
      next_pos_in_lex = 0;
      lex_type = U;
      lexeme.resize(MAX_LEX_SIZE);     // necessary
      
   // get a lexeme and its type
      lex();
      lexeme.resize(next_pos_in_lex+1);   // shrink for display
      m_IToken.insert( lex_type, lexeme );
   //   cout<<"TEST"<<no_char_in_cmd<<" "<<next_pos_in_cmd<<endl;

   }
   
   if( next_pos_in_cmd == no_char_in_cmd )
   {
      // the command terniates without '$', add it.
      if( next_char_type != ENDCODE ) 
      {
         m_IToken.insert( SCANEOF, "$" );
      }
   }
   /*
   else  // a '$' found in the middle of command
   {
      m_IToken.insert( SCANEOF, "$" );
   }*/
   
}

CToken_List CScanner::get_token_list() const
{
   return m_IToken;
}
   
void CScanner::get_char_set_type()
{
   if( next_pos_in_cmd > no_char_in_cmd )
   {
      throw CSignal("Warning: End of command reach");
   }
   else
   {
    // get the next character from the command and position to the following
      next_char = m_strCommand[next_pos_in_cmd++];
      
      if( next_char >= '0' && next_char <= '9' )
         next_char_type = DIGIT;
      else if( (next_char >= 'A' && next_char <= 'Z') ||
               (next_char >= 'a' && next_char <= 'z')  )
         next_char_type = LETTER;
      else if( next_char == '.' )
         next_char_type = DOT;
      else if( next_char == '_' )
         next_char_type = UNDERSCORE;
      else if( next_char == '$' )
         next_char_type = ENDCODE;
      else if( next_char == ' ' )
         next_char_type = BLANK;
      else
         next_char_type = GENERAL;
      
   //   cout << "char found in get_char_set_type: " 
   //        << next_char << endl;
   }
}

void CScanner::add_char()
{
   lexeme[next_pos_in_lex] = next_char;
   next_pos_in_lex++;
   // \0 is the terminator. Last one if no further
   lexeme[next_pos_in_lex] = '\0';        
}

// these external data have been set/intiliazed in driver.cpp

extern const int CTL_CHAR_OFFSET = 32;
extern lexeme_type_t lexeme_type[];

void CScanner::lex()
{
   next_pos_in_lex = 0;
   int no_dots = 0;     // used for detecting wrong literals
   lexeme[0] = '\0';
   
   // skip blank space in input
   while( next_char_type == BLANK )
   {
      get_char_set_type();
   }

//   cout << "Before switch " << endl;
   switch( next_char_type )
   {
   case LETTER:      // an identifier starts
      add_char();
	   if( next_pos_in_cmd <= no_char_in_cmd )
	   {
	      get_char_set_type();
               while( (next_pos_in_cmd <= no_char_in_cmd ) &&
	            (next_char_type == LETTER ||
                     next_char_type == DIGIT  ||
		               next_char_type == UNDERSCORE) )
               {
                  add_char();
                  get_char_set_type();
               }
	   }
      lex_type = ID;
      break;
   case DIGIT:      // a float literal starts
      add_char();
	   if( next_pos_in_cmd <= no_char_in_cmd )
	   {
               get_char_set_type();
               while( (next_pos_in_cmd <= no_char_in_cmd ) &&
	            (next_char_type == DIGIT || 
	               next_char_type == DOT) )
               {
	         if( next_char_type == DOT )
	         {
	            if( no_dots == 0 )
	            {
	               no_dots++;
	            }
	            else    // Error: 2 or more dots in float literal!!
	            {
	               throw CSignal("Illegal literal: too much dots");
	            }
	         }
                  add_char();
                  get_char_set_type();
	      }
	   }
      lex_type = FLOATLIT;
      break;
   case ENDCODE:
      add_char();
	   lex_type = SCANEOF;
	   if( next_pos_in_cmd <= no_char_in_cmd )
	      get_char_set_type();
	   break;
   default:     
         // the pther lexemes
            add_char();
	   lex_type = lexeme_type[(int)next_char-CTL_CHAR_OFFSET].lex_type;
	   if( next_pos_in_cmd < no_char_in_cmd )
	   {
	      get_char_set_type();
	   }
      if( next_pos_in_cmd == no_char_in_cmd && next_char_type != ENDCODE)
         next_pos_in_cmd++;
   }
}
