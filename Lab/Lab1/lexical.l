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
{INT} {printf("INT, value = %d\n", (int)(strtol(yytext,NULL,10))); return INT;}
{FLOAT} {printf("FLOAT, value = %f\n", atof(yytext)); return FLOAT;}
{SEMI} {printf("SEMI\n"); return SEMI;}
{COMMA} {printf("COMMA\n"); return COMMA;}
{ASSIGNOP} {printf("ASSIGNOP\n"); return ASSIGNOP;}
{RELOP} {printf("RELOP, type = %s\n", yytext); return RELOP;}
{PLUS} {printf("PLUS\n"); return PLUS;}
{MINUS} {printf("MINUS\n"); return MINUS;}
{STAR} {printf("STAR\n"); return STAR;}
{DIV} {printf("DIV\n"); return DIV;}
{AND} {printf("AND\n"); return AND;}
{OR} {printf("OR\n"); return OR;}
{DOT} {printf("DOT\n"); return DOT;}
{NOT} {printf("NOT\n"); return NOT;}
{TYPE} {printf("TYPE, name = %s\n", yytext); return TYPE;}
{LP} {printf("LP\n"); return LP;}
{RP} {printf("RP\n"); return RP;}
{LB} {printf("LB\n"); return LB;}
{RB} {printf("RB\n"); return RB;}
{LC} {printf("LC\n"); return LC;}
{RC} {printf("RC\n"); return RC;}
{STRUCT} {printf("STRUCT\n"); return STRUCT;}
{RETURN} {printf("RETURN\n"); return RETURN;}
{IF} {printf("IF\n"); return IF;}
{ELSE} {printf("ELSE\n"); return ELSE;}
{WHILE} {printf("WHILE\n"); return WHILE;}
{ID} {printf("ID, name = %s\n", yytext); return ID;}

{BLANK}+ {}
. {printf("Error type A at line %d: Mysterious charactor %s\n", yylineno, yytext);}
%%
