%{
    #include<stdio.h>
    #include "syntax.tab.h"
%}
%option yylineno

DECIMAL 0|[1-9][0-9]*
OCTAL 0[0-7]+
HEX 0[xX][0-9a-fA-F]+
INT {DECIMAL}|{OCTAL}|{HEX}
FLOAT ([0-9]*\.?[0-9]+|[0-9]+\.)
ID [_a-zA-Z][_a-zA-Z0-9]*
SEMI ;
COMMA ,
ASSIGNOP =
RELOP >|<|>=|<=|==|!=
PLUS [+]
MINUS -
STAR [*]
DIV [/]
AND &&
OR \|\|
DOT [.]
NOT !
TYPE int|float
LP [(]
RP [)]
LB \[
RB \]
LC [{]
RC [}]
STRUCT struct
RETURN return
IF if
ELSE else
WHILE while

BLANK [ \t]
%%
{INT} {return INT;}
{FLOAT} {return FLOAT;}
{SEMI} {return SEMI;}
{COMMA} {return COMMA;}
{ASSIGNOP} {return ASSIGNOP;}
{RELOP} {return RELOP;}
{PLUS} {return PLUS;}
{MINUS} {return MINUS;}
{STAR} {return STAR;}
{DIV} {return DIV;}
{AND} {return AND;}
{OR} {return OR;}
{DOT} {return DOT;}
{NOT} {return NOT;}
{TYPE} {return TYPE;}
{LP} {return LP;}
{RP} {return RP;}
{LB} {return LB;}
{RB} {return RB;}
{LC} {return LC;}
{RC} {return RC;}
{STRUCT} {return STRUCT;}
{RETURN} {return RETURN;}
{IF} {return IF;}
{ELSE} {return ELSE;}
{WHILE} {return WHILE;}
{ID} {return ID;}

{BLANK}+ {}
\n {}
. {printf("Error type A at line %d: Mysterious charactor %s\n", yylineno, yytext);}
%%
