/*
	Quiz12.y

 	Bison specification file.

	Grammar is:
		P -> var V { C }
		V -> ident N ; V | lambda
		N -> [ intconst ] N | lambda
		C -> S ; C | lambda
		S -> A | F | W
		A -> ident = E | L = E
		F -> if ( B ) then S else S
		W -> while ( B ) S
		E -> E + intconst | ident | L | intconst
		L -> ident [ E ] | L [ E ]
		B -> E R E | true | false
		R -> > | < | != | >= | <= | ==

      To create the syntax analyzer:

        flex Quiz12.l
        bison Quiz12.y
        g++ Quiz12.tab.c -o parser
        parser < inputFileName
 */

%{
#include <stdio.h>

int numLines = 1;

void printRule(const char *lhs, const char *rhs);
void yyerror(const char *s);
void printTokenInfo(const char* tokenType, const char* lexeme);

extern "C" 
{
    int yyparse(void);
    int yylex(void);
    int yywrap() { return 1; }
}

%}

/* Token declarations */
%token  T_LPAREN T_RPAREN T_LBRACK T_RBRACK T_SEMICOL T_PLUS 
%token	T_ASSIGN T_GT T_LT T_NE T_GE T_LE T_EQ T_VAR T_LCURLY 
%token	T_RCURLY T_IF T_THEN T_ELSE T_DO T_WHILE T_TRUE T_FALSE 
%token	T_LAMBDA T_INTCONST T_IDENT T_UNKNOWN

/* Starting point */
%start		N_START

/* Translation rules */
%%
N_START		: P
				{
				printRule("START", "P");
				printf("\n---- Completed parsing ----\n\n");
				return 0;
				}
			;
			

P			: T_VAR V T_LCURLY C T_RCURLY
				{
				printRule("P", "var V {C}");
				}
			;
			
V			: /* lambda */
				{
				printRule("V", "lambda");
				}
			| T_IDENT N T_SEMICOL V
				{
				printRule("V", "ident N ; V");
				}
			;
			
N			: /* lambda */
				{
				printRule("N", "lambda");
				}
			| T_LBRACK T_INTCONST T_RBRACK N
				{
				printRule("N", "[intconst] N");
				}
			;

C			:	S T_SEMICOL C
					{
					printRule("C", "S ; C");
					}
				| /* lambda */
					{
					printRule("C", "lambda");
					}
			;
			
S			: A
				{
				printRule("S", "A");
				}
			| F
				{
				printRule("S", "F");
				}
			| W
				{
				printRule("S", "W");
				}
			;

A			: T_IDENT T_ASSIGN E
				{
				printRule("A", "ident = E");
				}
			| L T_ASSIGN E
				{
				printRule("A", "L = E");
				}
			;

F			: T_IF T_LPAREN B T_RPAREN T_THEN S T_ELSE S
				{
				printRule("F", "if (B) then S else S");
				}
			;

W			: T_WHILE T_LPAREN B T_RPAREN S
				{
				printRule("W", "while (B) S");
				}
			;
			
E			: E T_PLUS T_INTCONST
				{
				printRule("E", "E + intconst");
				}
			| T_IDENT
				{
				printRule("E", "ident");
				}
			| L
				{
				printRule("E", "L");
				}
			| T_INTCONST
				{
				printRule("E", "intconst");
				}
			;
			
L			: T_IDENT T_LBRACK E T_RBRACK
				{
				printRule("L", "ident[E]");
				}
			| L T_LBRACK E T_RBRACK
				{
				printRule("L", "L[E]");
				}
			;
			
B			: E R E
				{
				printRule("B", "E R E");
				}
			| T_TRUE
				{
				printRule("B", "true");
				}
			| T_FALSE
				{
				printRule("B", "false");
				}
			;
			
R			: T_GT
				{
				printRule("R", ">");
				}
			| T_LT
				{
				printRule("R", "<");
				}
			| T_NE
				{
				printRule("R", "!=");
				}
			| T_GE
				{
				printRule("R", ">=");
				}
			| T_LE
				{
				printRule("R", "<=");
				}
			| T_EQ
				{
				printRule("R", "==");
				}
			;
%%

#include "lex.yy.c"
extern FILE *yyin;

void printRule(const char *lhs, const char *rhs) 
{
  printf("%s -> %s\n", lhs, rhs);
  return;
}

void yyerror(const char *s) 
{
  printf("Line %d: %s at %s\n", yylineno, s, yytext);
}

void printTokenInfo(const char* tokenType, const char* lexeme) 
{
  printf("TOKEN: %-15s  LEXEME: %s\n", tokenType, lexeme);
  return;
}

int main() 
{
  do 
  {
	yyparse();
  } while (!feof(yyin));

  printf("%d lines processed\n", numLines);
  return(0);
}
