/*
*/

%{
%}
/* Definitions of regular expressions */
WSPACE [ \t\r]+
NEWLINE [\n]
DIGIT [0-9]
LETTER [a-zA-Z]
NEG_INTCONST	"-"[0-9]+
POS_INTCONST	("+")?[0-9]+
INTCONST        {NEG_INTCONST}|{POS_INTCONST}
IDENT			[a-z]|[A-Z]


%option yylineno

%%
"("			{
				printTokenInfo("LPAREN", yytext);
				return T_LPAREN;
			}
")"			{
				printTokenInfo("RPAREN", yytext);
				return T_RPAREN;
			}
"["			{
				printTokenInfo("LBRACK", yytext);
				return T_LBRACK;
			}
"]"			{
				printTokenInfo("RBRACK", yytext);
				return T_RBRACK;
			}
";"			{
				printTokenInfo("SEMICOL", yytext);
				return T_SEMICOL;
			}
"+"			{
				printTokenInfo("PLUS", yytext);
				return T_PLUS;
			}
"="			{
				printTokenInfo("ASSIGN", yytext);
				return T_ASSIGN;
			}
">"			{
				printTokenInfo("GT", yytext);
				return T_GT;
			}
"<"			{
				printTokenInfo("LT", yytext);
				return T_LT;
			}
"!="			{
				printTokenInfo("NE", yytext);
				return T_NE;
			}
">="			{
				printTokenInfo("GE", yytext);
				return T_GE;
			}
"<="			{
				printTokenInfo("LE", yytext);
				return T_LE;
			}
"=="			{
				printTokenInfo("EQ", yytext);
				return T_EQ;
			}
"var"			{
				printTokenInfo("VAR", yytext);
				return T_VAR;
			}
"{"			{
				printTokenInfo("LCURLY", yytext);
                      return T_LCURLY;
			}
"}"			{
				printTokenInfo("RCURLY", yytext);
                      return T_RCURLY;
			}
"if"			{
				printTokenInfo("IF", yytext);
				return T_IF;
			}
"then"		{
				printTokenInfo("THEN", yytext);
				return T_THEN;
			}
"else"		{
				printTokenInfo("ELSE", yytext);
				return T_ELSE;
			}
"do"		{
				printTokenInfo("DO", yytext);
				return T_DO;
			}
"while"		{
				printTokenInfo("WHILE", yytext);
				return T_WHILE;
			}
"true"		{
				printTokenInfo("TRUE", yytext);
				return T_TRUE;
			}
"false"		{
				printTokenInfo("FALSE", yytext);
				return T_FALSE;
		    }

{INTCONST} 	{
				printTokenInfo("INTCONST", yytext);
				return T_INTCONST;
			}
{IDENT} 	{
				printTokenInfo("IDENT", yytext);
				return T_IDENT;
			}
{NEWLINE} 	{
 				numLines++;
 			}
{WSPACE} 	{ }
. 			{
				printTokenInfo("UNKNOWN", yytext);
				return T_UNKNOWN;
			}

%%
