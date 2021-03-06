#ifndef __IR_H__
#define __IR_H__


#include <stdio.h>
#include "treeNode.h"
#include "hashtable.h"



// #define print_lab_3

typedef struct Operand_t* Operand;
typedef struct InterCode_t* InterCode;
typedef struct PointToOperand_ * PointToOperand;

enum OperandKind { VARIABLE, CONSTANT, ADDRESS, REFERENCE, LABEL_OPERAND, FUNCTION_OPERAND, TEMPORARY_VARIABLE, TEMPORARY_ADDRESS, STRUCTURE_ARRAY, STRUCTURE_STRUCTURE };
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

struct PointToOperand_{
    Operand point;
    PointToOperand next;
};

InterCode inter_code_head;
InterCode inter_code_tail;

Operand operand_head;
Operand operand_tail;

int var_num;
int temp_var_num;
int label_num;
int IRERROR;

void printOperand(FILE* fp, Operand operand);
void printInterCode();

int haveMultiDimensionalArray();
int isArray(Operand operand);
int isStructure(Operand operand);

int getTypeSize(Type type);

Operand newOperand(enum OperandKind kind, int num, char* name);
InterCode newInterCode(enum InterCodeKind kind, Operand op1, Operand op2, Operand result);
void insertInterCode(InterCode intercode);
void insertAfter(InterCode target, InterCode place);
void deleteInterCode(InterCode intercode);
void insertOperand(Operand operand);
Operand findOperand(char* name);
Operand findStructure(char* name);

void initIr();
void IRProgram(treeNode* root);
void IRExtDefList(treeNode* parent);
void IRExtDef(treeNode* parent);
void IRFunDec(treeNode* parent);
void IRVarList(treeNode* parent);
void IRParamDec(treeNode* parent);
void IRFunctionVarDec(treeNode* parent);
void IRCompSt(treeNode* parent);
void IRDefList(treeNode* parent);
void IRStmtList(treeNode* parent);
void IRDef(treeNode* parent);
void IRDecList(treeNode* parent);
void IRDec(treeNode* parent);
Operand IRVarDec(treeNode* parent);
Operand IRExp(treeNode* parent, Operand place);
PointToOperand IRArgs(treeNode* parent);

void IRStmt(treeNode* parent);
void IRCond(treeNode* parent, Operand label1, Operand label2);
int getStructureIndex(Type type, char* name);



int changed;


void irOptimise();
void computeConstant();
void replaceTempConstant(InterCode start, int temp_num, int const_value);
void replaceTempAssignConstant();
void reverseIf();


#endif