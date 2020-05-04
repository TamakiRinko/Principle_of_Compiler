#ifndef __IR_H__
#define __IR_H__

#include <stdio.h>
#include "treeNode.h"
#include "hashtable.h"

typedef struct Operand_t* Operand;
typedef struct InterCode_t* InterCode;
enum OperandKind { VARIABLE, CONSTANT, ADDRESS, LABEL_OPERAND, FUNCTION_OPERAND, TEMPORARY_VARIABLE };
enum InterCodeKind { LABEL_INTERCODE, FUNCTION_INTERCODE, ASSIGN, PLUS, MINUS, STAR, DIV, 
            ADDR, LEFT_REF, RIGHT_REF, GOTO, JE, JNE, JA, JAE, JB, JBE, 
            RETURN, DEC, ARG, CALL, PARAM, READ, WRITE };

struct Operand_t{
    enum OperandKind kind;
    union{
        // 一般变量
        struct{
            int var_num;
            char* var_name;
        }variable;
        // 临时变量，Label
        int num;
        // 常量
        int const_value;
        // 函数，地址
        char* name;
    }u;
    Operand next;
};

struct InterCode_t{
    enum InterCodeKind kind;
    Operand result;
    Operand op1;
    Operand op2;
    InterCode next;
    InterCode prev;
};

InterCode inter_code_head;
InterCode inter_code_tail;

Operand operand_head;
Operand operand_tail;

int var_num;
int temp_var_num;
int label_num;
int IRERROR;

int getTypeSize(Type type);

Operand newOperand(enum OperandKind kind, int num, char* name);
InterCode newInterCode(enum InterCodeKind kind, Operand op1, Operand op2, Operand result);
void insertInterCode(InterCode intercode);
void insertOperand(Operand operand);
Operand findOperand(char* name);

void initIr();
void IRProgram(treeNode* root);
void IRExtDefList(treeNode* parent);
void IRExtDef(treeNode* parent);
void IRFunDec(treeNode* parent);
void IRVarList(treeNode* parent);
void IRParamDec(treeNode* parent);
void IRFunctionVarDec(treeNode* parent);
void IRDefList(treeNode* parent);
void IRStmtList(treeNode* parent);
void IRDef(treeNode* parent);
void IRDecList(treeNode* parent);
void IRDec(treeNode* parent);
Operand IRVarDec(treeNode* parent);
Operand IRExp(treeNode* parent, Operand place);

void IRStmt(treeNode* parent);
void IRCond(treeNode* parent, Operand label1, Operand label2);

#endif