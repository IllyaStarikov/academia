//********************************************************
//                                                       *
//  Instructor: Franck Xia                               *
//  Class:      CS236 Fall 2002                          *
//  Assignment: Program 6                                *
//  Programmer: It's you                                 *
//  File name:  driver.cpp                               *
//  Function:   driver program testing the parser        *
//                                                       *
//********************************************************                 

#define SUCCESSFUL 0

#include <iostream>
#include <list>
#include <string>
#include <fstream>
#include <cstring>

#include "signal.h"
#include "parser.h"
#include "scanner.h"

using std::cout;
using std::endl;

char str_token_type[30][10];    // the array is global

// The following part declare an array of record to keep a single character 
//   lexeme and the type of lexeme useful for the parser

const int CTL_CHAR_OFFSET = 32;

lexeme_type_t  lexeme_type[] =
{
 // the first field of each record is a chacater, the second one its enTokens code
 // all the characters appear in the ascii code value ascedent order.
 // as the first 32 ascii chacaters are controlled characters, they are not
 // included. to access an appropriate record of a character, we can use the ascii
 // value of the character - 32 as the index to this array. 
   { ' ', U },{'!',U},{'"',U},{'#',U},
   { '$', SCANEOF },{'%',U},{'&',U},{ '\'',U},
   { '(', LPAREN },
   { ')', RPAREN },
   { '*', MULTOP },
   { '+', ADDOP },
   { ',', COMMA },
   { '-', SUBOP },{'.',U},
   { '/', DIVOP },
   { '0', U }, {'1',U}, {'2',U}, {'3',U}, {'4',U},
   { '5', U }, {'6',U}, {'7',U}, {'8',U}, {'9',U}, 
   { ':', U },
   { ';', SEMICOL },
   { '<', LESS },
   { '=', ASSIGNOP  },
   { '>', GREAT },{'?',U},{'@',U },
   { 'A', U },{'B',U},{'C',U},{'D',U},{'E',U},{'F',U},{'G',U},
   { 'H',U},{'I',U},{'J',U},{'K',U},{'L',U},{'M',U},{'N',U},
   { 'O',U},{'P',U},{'Q',U},{'R',U},{'S',U},{'T',U},{'U',U},
   { 'V',U},{'W',U},{'X',U},{'Y',U},{'Z',U},
   { '[', LBRACK },{'\\',U},
   { ']', RBRACK },{'^',U},{'_',U},{'`',U},
   { 'a', U },{'b',U},{'c',U},{'d',U},{'e',U},{'f',U},{'g',U},
   { 'h', U },{'i',U},{'j',U},{'k',U},{'l',U},{'m',U},{'n',U},
   { 'o', U },{'p',U},{'q',U},{'r',U},{'s',U},{'t',U},{'u',U},
   { 'v', U },{'w',U},{'x',U},{'y',U},{'z',U},
   { '{', U },{'|',U},{'}',U},{'~',U}
};

int main() {

  // The following lines avoid a huge switch statement
     
    char tt[10];
    int c;
    std::ifstream token_file( "tokens_file.dat" );
    
    c = 0;   // the starting value of enTokens type is set to 0 
    while ( c < 30 && token_file >> tt  )
    {
       std::strcpy( str_token_type[c++], tt );
    } 

    std::list<std::string>  program_list;
    std::list<std::string>::const_iterator itrTest;
    CScanner                scanner;
    Parser		    parsing;
    
    //program_list.push_back(std::string("a=b+3.14156 - 7.8182;$"));
    //program_list.push_back(std::string("a=c*b-d; $"));
    //program_list.push_back(std::string("a=c+b$ "));
    //program_list.push_back(std::string("a=c*(b-d);$"));
    //program_list.push_back(std::string("a=c+b*d;$"));
    //program_list.push_back(std::string("a=(c+b)*d;$"));
    //program_list.push_back(std::string("a=(c+b)*d;$ "));
    //program_list.push_back(std::string("a=(c+b)*d ; b=a-e*t; $"));
    //program_list.push_back(std::string("a=1+b $"));

    program_list.push_back(std::string("b=[1.0,2.1;3.5,4.6];$"));
    program_list.push_back(std::string("b=[1.0,2.1;3.5,4.6]+1.0;$"));
    program_list.push_back(std::string("b=[1.0,2.1;3.5,4.6]-1.0;$"));
    program_list.push_back(std::string("b=1.0+[1.0,2.1;3.5,4.6];$"));
    program_list.push_back(std::string("b=1.0-[1.0,2.1;3.5,4.6];$"));
    program_list.push_back(std::string("b=2.0*[1.0,2.1;3.5,4.6];$"));
    program_list.push_back(std::string("b=[1.0,2.1;3.5,4.6]*2.0;$"));
    program_list.push_back(std::string("b=1.0+2.1;$"));
    program_list.push_back(std::string("b=1.0-2.1;$"));
    program_list.push_back(std::string("b=3.0*2.1;$"));

    program_list.push_back(std::string("b=[1.0,2.1;3.5,4.6];$"));
    program_list.push_back(std::string("b=[1.0,2.1;3.5];$"));
    program_list.push_back(std::string("b=[1.0,2.1;3.5,4.6]+[1.0,2.1;3.5,4.6];$"));
    program_list.push_back(std::string("b=[1.0,2.1]+[1.0,2.1;3.5,4.6];$"));
    program_list.push_back(std::string("b=[1.0,2.1;3.5,4.6]+[2.1;4.6];$"));
    program_list.push_back(std::string("b=[1.0,2.1;3.5,4.6]-[1.0,2.1;3.5,4.6];$"));
    program_list.push_back(std::string("b=[1.0,2.1;3.5,4.6]-[1.0,2.1];$"));
    program_list.push_back(std::string("b=[1.0;3.5]-[1.0,2.1;3.5,4.6];$"));
    program_list.push_back(std::string("b=[1.0,2.1;3.5,4.6]+[1.0,2.1;3.5,4.6];$"));
    program_list.push_back(std::string("b=[1.0;3.5]*[1.0,2.1;3.5,4.6];$")); 
    program_list.push_back(std::string("b=[1.0;3.5]*[1.0,2.1];$"));
    
    itrTest = program_list.begin();
    while(itrTest != program_list.end())
    {
       try
       { 
          cout << *itrTest << endl;
          scanner.generate_token_list(*itrTest);

       // now scanner should contain a list of lexemes ready for parsing
       
         CToken_List ajb_temp=scanner.get_token_list();
	      parsing.parse(ajb_temp);
	      cout << "\nA New Program\n\n";
       }
       catch (CSignal e)
       {
	       cout << e.get_message() <<endl <<endl <<endl;  // Get the message
       }
       itrTest++;
     }
    
    return (SUCCESSFUL);
}
