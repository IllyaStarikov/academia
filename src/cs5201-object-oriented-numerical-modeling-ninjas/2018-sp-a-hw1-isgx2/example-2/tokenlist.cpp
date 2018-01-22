//   File Name: tokenlist.cpp
//   Function:  Define the token list class
//   Author:    Franck Xia
//   Creation:  Oct. 10, 2001

#include "tokenlist.h"
#include "signal.h"
using std::endl;

CToken_List::CToken_List()
{
   cur = tokList.begin();
}

void CToken_List::clear()
{
   tokList.clear();
   cur = tokList.begin();  // risky if not to do so
}

void CToken_List::set_at_start()
{
   cur = tokList.begin();
}

// moveahead is equivalent of advance() with a different name

void CToken_List::moveahead()         
{
   if( tokList.empty() )
   {
      throw CSignal("List empty, cannot advance");
   }
   else if( cur == tokList.end() )
   {
      throw CSignal("End of list reached, cannot advance");
   }
   
   cur++;     // that's the meaning of iterator
}


void CToken_List::insert( enTokens t, std::string s  )
{
   CToken tmp( t, s );
   tokList.push_back( tmp );
}

void CToken_List::insert( CToken t )
{
   tokList.push_back( t );
}

CToken CToken_List::get_current_token() const
{
   return *cur;
}

enTokens CToken_List::get_current_token_type() const
{
   return cur->get_token_type();
}

std::string CToken_List::get_current_lex() const
{
   return cur->get_lex();
}


enTokens CToken_List::next_token_type_peek()
{
   std::list<CToken>::iterator tmp;
   
   if( cur == tokList.end() )
   {
      throw CSignal("No Next token, the ned reached");
   }
   
   // use a temporary one, not affecting cur.
   tmp = cur;     
   tmp++;
   return tmp->get_token_type();
}


bool CToken_List::is_end_of_list() const
{
   bool rts = false;
   if( tokList.end() == cur)
   {
      rts = true;
   }
   return rts;
}


ostream& operator<<( ostream& display, CToken_List list )
{
   int token_count = 1;
   CToken tmp;
  
   if( list.tokList.empty() )
   {
    // This case should not be omitted.
    
      display << "Nothing to display!" << endl;
   }
   else
   {
      list.set_at_start();

      while ( !list.is_end_of_list() )
      {
       // get the current token on the list & display it
    
         tmp = list.get_current_token();
         display << tmp;
      
       // move to the next node to make sure if tmp is the last one 
    
         list.moveahead();
      
         if( list.is_end_of_list() )
         {
         // The last one: do not display arrow.
             display << endl;
         }
         else
         { 
            display << "->";
	    token_count++;
	    
	    // cut the current display line when there are more than 4 tokens
            if( token_count > 4 )   
            {
               display << endl;
	       token_count = 1;
            }
         }
      }
   }
   
   return display;
}

