/*
 *  main.l
 *  homework-2
 *
 *  Created by Illya Starikov on 03/18/18.
 *  Copyright 2018. Illya Starikov. All rights reserved.
 *
 *  NOTE: Only works with C++14.
 */

%{
#include <iostream>
#include <map>
#include <iomanip>

int numberOfLines = 0;
int numberOfTokens = 0;

enum Token {
    integer, decimal, scientific, hexadecimal, binary, phone, keyword, identifier, string, operators, unknown
};

void process(const Token token, const std::string& lexeme) {
    static std::map<const Token, const std::string> tokenDescription = {
        {integer,     "INTCONST" },
        {decimal,     "DECCONST" },
        {scientific,  "SCICONST" },
        {hexadecimal, "HEXCONST" },
        {binary,      "BINCONST" },
        {phone,       "PHCONST"  },
        {keyword,     "KEYWORD"  },
        {identifier,  "IDENT"    },
        {string,      "STRCONST" },
        {operators,   "OPERATOR" },
        {unknown,     "?"        }
    };

    std::cout << "#" << numberOfTokens << ": TOKEN: " << std::setw(11) << std::left << tokenDescription[token] << "LEXEME: " << lexeme << "\n";
    numberOfTokens++;
}

%}
                          /* ---- DEFINITIONS ---- */
%option noyywrap

COMMENT    #.*
WHITESPACE [ \t]

NONZERO_DIGIT   [1-9]
NONZERO_INTEGER (\+|-)?{DIGIT}+

HEX_CHARS [ABCDEF]

DIGIT       [0-9]
INTEGER     (\+|-)?{DIGIT}+
DECIMAL     {INTEGER}\.{DIGIT}+
SCIENTIFIC  {DECIMAL}.E{NONZERO_INTEGER}
HEXADECIMAL ({DIGIT}|{HEX_CHARS})+H
BINARY      [01]+B

PHONE_SECTION  {DIGIT}{DIGIT}{DIGIT}
PHONE_FORMAT_1 {PHONE_SECTION}\.{PHONE_SECTION}\.{PHONE_SECTION}{DIGIT}
PHONE_FORMAT_2 \({PHONE_SECTION}\){PHONE_SECTION}-{PHONE_SECTION}{DIGIT}
PHONE_FORMAT_3 {PHONE_SECTION}-{PHONE_SECTION}-{PHONE_SECTION}{DIGIT}

IF       if
THEN     then
ELSE     else
WHILE    while
END      end
FUNCTION func
PRINT    print

CHARACTER       [a-zA-Z]
STRING          {CHARACTER}+
IDENTIFIER      {CHARACTER}({CHARACTER}|{DIGIT})*
STRING_CONSTANT \"({CHARACTER}|{DIGIT}|{WHITESPACE})*\"

PLUS         \+
MINUS        -
STAR         \*
SLASH        \/
LESS_THAN    <
GREATER_THAN >
EQUALS       =




%%                        /* ---- REGULAR EXPRESSIONS ---- */

[ \t] { };
{COMMENT} { };

\n  { numberOfLines++; }

{IF}       { process(keyword, yytext); }
{THEN}     { process(keyword, yytext); }
{ELSE}     { process(keyword, yytext); }
{WHILE}    { process(keyword, yytext); }
{END}      { process(keyword, yytext); }
{FUNCTION} { process(keyword, yytext); }
{PRINT}    { process(keyword, yytext); }

{PHONE_FORMAT_1}|{PHONE_FORMAT_2}|{PHONE_FORMAT_3} { process(phone, yytext); }

{BINARY}      { process(binary, yytext); }
{HEXADECIMAL} { process(hexadecimal, yytext); }
{SCIENTIFIC}  { process(scientific, yytext); }
{INTEGER}     { process(integer, yytext); }
{DECIMAL}     { process(decimal, yytext); }

{STRING_CONSTANT} { process(string, yytext); }
{IDENTIFIER}      { process(identifier, yytext); }

{PLUS}         { process(operators, yytext); }
{MINUS}        { process(operators, yytext); }
{STAR}         { process(operators, yytext); }
{SLASH}        { process(operators, yytext); }
{LESS_THAN}    { process(operators, yytext); }
{GREATER_THAN} { process(operators, yytext); }
{EQUALS}       { process(operators, yytext); }

. { process(unknown, yytext); }

%%                        /* ---- EPILOGUE ---- */

int main()
{
    yylex();
    std::cout << numberOfLines << " lines processed." << "\n";
}
