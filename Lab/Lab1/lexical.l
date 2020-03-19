%{
    #include<stdio.h>
    #include "syntax.tab.h"
    #include "treeNode.h"

    int haveError = 0;
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
{INT} {yylval.treeNode = initLexical("INT", yytext, yylineno);return INT;}
{FLOAT} {yylval.treeNode = initLexical("FLOAT", yytext, yylineno);return FLOAT;}
{SEMI} {yylval.treeNode = initLexical("SEMI", yytext, yylineno);return SEMI;}
{COMMA} {yylval.treeNode = initLexical("COMMA", yytext, yylineno);return COMMA;}
{ASSIGNOP} {yylval.treeNode = initLexical("ASSIGNOP", yytext, yylineno);return ASSIGNOP;}
{RELOP} {yylval.treeNode = initLexical("RELOP", yytext, yylineno);return RELOP;}
{PLUS} {yylval.treeNode = initLexical("PLUS", yytext, yylineno);return PLUS;}
{MINUS} {yylval.treeNode = initLexical("MINUS", yytext, yylineno);return MINUS;}
{STAR} {yylval.treeNode = initLexical("STAR", yytext, yylineno);return STAR;}
{DIV} {yylval.treeNode = initLexical("DIV", yytext, yylineno);return DIV;}
{AND} {yylval.treeNode = initLexical("AND", yytext, yylineno);return AND;}
{OR} {yylval.treeNode = initLexical("OR", yytext, yylineno);return OR;}
{DOT} {yylval.treeNode = initLexical("DOT", yytext, yylineno);return DOT;}
{NOT} {yylval.treeNode = initLexical("NOT", yytext, yylineno);return NOT;}
{TYPE} {yylval.treeNode = initLexical("TYPE", yytext, yylineno);return TYPE;}
{LP} {yylval.treeNode = initLexical("LP", yytext, yylineno);return LP;}
{RP} {yylval.treeNode = initLexical("RP", yytext, yylineno);return RP;}
{LB} {yylval.treeNode = initLexical("LB", yytext, yylineno);return LB;}
{RB} {yylval.treeNode = initLexical("RB", yytext, yylineno);return RB;}
{LC} {yylval.treeNode = initLexical("LC", yytext, yylineno);return LC;}
{RC} {yylval.treeNode = initLexical("RC", yytext, yylineno);return RC;}
{STRUCT} {yylval.treeNode = initLexical("STRUCT", yytext, yylineno);return STRUCT;}
{RETURN} {yylval.treeNode = initLexical("RETURN", yytext, yylineno);return RETURN;}
{IF} {yylval.treeNode = initLexical("IF", yytext, yylineno);return IF;}
{ELSE} {yylval.treeNode = initLexical("ELSE", yytext, yylineno);return ELSE;}
{WHILE} {yylval.treeNode = initLexical("WHILE", yytext, yylineno);return WHILE;}
{ID} {yylval.treeNode = initLexical("ID", yytext, yylineno);return ID;}

{BLANK}+ {}
\n {}
. {printf("Error type A at line %d: Mysterious charactor %s\n", yylineno, yytext);}
%%
