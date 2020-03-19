%{
    #include "lex.yy.c"
    #include <stdio.h>
    #include "treeNode.h"

    treeNode* root = NULL;
%}

%union{
    struct TreeNode* treeNode;
}

%token <treeNode> INT FLOAT STRUCT
%token <treeNode> ID
%token <treeNode> SEMI COMMA
%token <treeNode> ASSIGNOP RELOP
%token <treeNode> PLUS MINUS STAR DIV AND OR NOT
%token <treeNode> DOT
%token <treeNode> TYPE
%token <treeNode> LP RP LB RB LC RC
%token <treeNode> RETURN
%token <treeNode> IF ELSE WHILE

%type <treeNode> Program ExtDefList ExtDef Specifier ExtDecList FunDec CompSt VarDec
%type <treeNode> StructSpecifier OptTag DefList Tag
%type <treeNode> VarList ParamDec
%type <treeNode> StmtList Stmt Exp 
%type <treeNode> Def DecList Dec
%type <treeNode> Args

%right ASSIGNOP
%left OR
%left AND
%left RELOP
%left PLUS MINUS
%left STAR DIV
%right NOT
%left LP RP LB RB DOT

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%
/*-------------------------- High-level Definitions-------------------------*/
Program: ExtDefList {$$ = initSyntax("Program"); buildTree($$, 1, $1); root = $$;}
;
ExtDefList: ExtDef ExtDefList {$$ = initSyntax("ExtDefList"); buildTree($$, 2, $1, $2);}
| /*empty*/ {$$ = NULL;}
;
ExtDef: Specifier ExtDecList SEMI {$$ = initSyntax("ExtDef"); buildTree($$, 3, $1, $2, $3);}
| Specifier SEMI {$$ = initSyntax("ExtDef"); buildTree($$, 2, $1, $2);}
| Specifier FunDec CompSt {$$ = initSyntax("ExtDef"); buildTree($$, 3, $1, $2, $3);}
;
ExtDecList: VarDec {$$ = initSyntax("ExtDecList"); buildTree($$, 1, $1);}
| VarDec COMMA ExtDecList {$$ = initSyntax("ExtDecList"); buildTree($$, 3, $1, $2, $3);}
;
/*--------------------------------------------------------------------------*/

/*-------------------------- Specifiers ------------------------------------*/
Specifier: TYPE {$$ = initSyntax("Specifier"); buildTree($$, 1, $1);}
| StructSpecifier {$$ = initSyntax("Specifier"); buildTree($$, 1, $1);}
;
StructSpecifier: STRUCT OptTag LC DefList RC {$$ = initSyntax("StructSpecifier"); buildTree($$, 5, $1, $2, $3, $4, $5);}
| STRUCT Tag {$$ = initSyntax("StructSpecifier"); buildTree($$, 2, $1, $2);}
;
OptTag: ID {$$ = initSyntax("OptTag"); buildTree($$, 1, $1);}
| /*empty*/ {$$ = NULL;}
;
Tag: ID {$$ = initSyntax("Tag"); buildTree($$, 1, $1);}
;
/*--------------------------------------------------------------------------*/

/*-------------------------- Declarators -----------------------------------*/
VarDec: ID {$$ = initSyntax("VarDec"); buildTree($$, 1, $1);}
| VarDec LB INT RB {$$ = initSyntax("VarDec"); buildTree($$, 4, $1, $2, $3, $4);}
;
FunDec: ID LP VarList RP {$$ = initSyntax("FunDec"); buildTree($$, 4, $1, $2, $3, $4);}
| ID LP RP {$$ = initSyntax("FunDec"); buildTree($$, 3, $1, $2, $3);}
;
VarList: ParamDec COMMA VarList {$$ = initSyntax("VarList"); buildTree($$, 3, $1, $2, $3);}
| ParamDec {$$ = initSyntax("VarList"); buildTree($$, 1, $1);}
;
ParamDec: Specifier VarDec {$$ = initSyntax("ParamDec"); buildTree($$, 2, $1, $2);}
;
/*--------------------------------------------------------------------------*/

/*-------------------------- Statements ------------------------------------*/
CompSt: LC DefList StmtList RC {$$ = initSyntax("CompSt"); buildTree($$, 4, $1, $2, $3, $4);}
;
StmtList: Stmt StmtList {$$ = initSyntax("StmtList"); buildTree($$, 2, $1, $2);}
| /*empty*/ {$$ = NULL;}
;
Stmt: Exp SEMI {$$ = initSyntax("Stmt"); buildTree($$, 2, $1, $2);}
| CompSt {$$ = initSyntax("Stmt"); buildTree($$, 1, $1);}
| RETURN Exp SEMI {$$ = initSyntax("Stmt"); buildTree($$, 3, $1, $2, $3);}
| IF LP Exp RP Stmt %prec LOWER_THAN_ELSE {$$ = initSyntax("Stmt"); buildTree($$, 5, $1, $2, $3, $4, $5);}
| IF LP Exp RP Stmt ELSE Stmt {$$ = initSyntax("Stmt"); buildTree($$, 7, $1, $2, $3, $4, $5, $6, $7);}
| WHILE LP Exp RP Stmt {$$ = initSyntax("Stmt"); buildTree($$, 5, $1, $2, $3, $4, $5);}
;
/*---------------------------------------------------------------------------*/

/*-------------------------- Local Definitions ------------------------------*/
DefList: Def DefList {$$ = initSyntax("DefList"); buildTree($$, 2, $1, $2);}
| /*empty*/ {$$ = NULL;}
;
Def: Specifier DecList SEMI {$$ = initSyntax("Def"); buildTree($$, 3, $1, $2, $3);}
;
DecList: Dec {$$ = initSyntax("DecList"); buildTree($$, 1, $1);}
| Dec COMMA DecList {$$ = initSyntax("DecList"); buildTree($$, 3, $1, $2, $3);}
;
Dec: VarDec {$$ = initSyntax("Dec"); buildTree($$, 1, $1);}
| VarDec ASSIGNOP Exp {$$ = initSyntax("Dec"); buildTree($$, 3, $1, $2, $3);}
;
/*----------------------------------------------------------------------------*/

/*-------------------------- Expressions -------------------------------------*/
Exp: Exp ASSIGNOP Exp {$$ = initSyntax("Exp"); buildTree($$, 3, $1, $2, $3);}
| Exp AND Exp {$$ = initSyntax("Exp"); buildTree($$, 3, $1, $2, $3);}
| Exp OR Exp {$$ = initSyntax("Exp"); buildTree($$, 3, $1, $2, $3);}
| Exp RELOP Exp {$$ = initSyntax("Exp"); buildTree($$, 3, $1, $2, $3);}
| Exp PLUS Exp {$$ = initSyntax("Exp"); buildTree($$, 3, $1, $2, $3);}
| Exp MINUS Exp {$$ = initSyntax("Exp"); buildTree($$, 3, $1, $2, $3);}
| Exp STAR Exp {$$ = initSyntax("Exp"); buildTree($$, 3, $1, $2, $3);}
| Exp DIV Exp {$$ = initSyntax("Exp"); buildTree($$, 3, $1, $2, $3);}
| LP Exp RP {$$ = initSyntax("Exp"); buildTree($$, 3, $1, $2, $3);}
| MINUS Exp {$$ = initSyntax("Exp"); buildTree($$, 2, $1, $2);}
| NOT Exp {$$ = initSyntax("Exp"); buildTree($$, 2, $1, $2);}
| ID LP Args RP {$$ = initSyntax("Exp"); buildTree($$, 4, $1, $2, $3, $4);}
| ID LP RP {$$ = initSyntax("Exp"); buildTree($$, 3, $1, $2, $3);}
| Exp LB Exp RB {$$ = initSyntax("Exp"); buildTree($$, 4, $1, $2, $3, $4);}
| Exp DOT ID {$$ = initSyntax("Exp"); buildTree($$, 3, $1, $2, $3);}
| ID {$$ = initSyntax("Exp"); buildTree($$, 1, $1);}
| INT {$$ = initSyntax("Exp"); buildTree($$, 1, $1);}
| FLOAT {$$ = initSyntax("Exp"); buildTree($$, 1, $1);}
;
Args: Exp COMMA Args {$$ = initSyntax("Args"); buildTree($$, 3, $1, $2, $3);}
| Exp {$$ = initSyntax("Args"); buildTree($$, 1, $1);}
;
/*-----------------------------------------------------------------------------*/

%%

int yyerror(char* msg){
    haveError = 1;
    fprintf(stderr, "Error type B at line %d:  %s\n", yylineno,  msg);
}
