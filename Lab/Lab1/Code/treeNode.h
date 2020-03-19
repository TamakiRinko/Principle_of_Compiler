#ifndef H_TREENODE_H
#define H_TREENODE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

enum CELLTYPE{
    Lexical, Syntax
};  

typedef struct TreeNode{
    enum CELLTYPE cellType;
    char* name;         //名称
    char* text;         //词素
    int lineno;
    // union{
    //     int int_val;
    //     float float_val;
    //     char* str_val;
    // };
    struct TreeNode* firstChild;
    struct TreeNode* nextBrother;
    // treeNode(char* Name, int Lineno, enum CELLTYPE CellType, struct treeNode* FirstChild, struct ){
    //     lineno = Lineno;
    //     cellType = CellType;
    //     name = (char*)malloc(strlen(Name) + 1);
    //     strcpy(name, Name);
    //     if(cellType == Lexical){            //词法单元，需要求值
    //         if(strcmp("INT", name)){
                
    //         }else if(strcmp("FLOAT", name)){

    //         }else if(strcmp("ID", name)){

    //         }
    //     }
        
    // }
}treeNode;

treeNode* initLexical(char* name, char* text, int lineno);
treeNode* initSyntax(char* name);
void buildTree(treeNode* parent, int childNum, ...);
void printNode(treeNode* root, int lineno);

#endif