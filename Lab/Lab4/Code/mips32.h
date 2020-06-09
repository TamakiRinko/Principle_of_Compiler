#ifndef _MIPS_32_H_
#define _MIPS_32_H_

#include "ir.h"

typedef struct FunctionBlock_t * FunctionBlock;
typedef struct BasicBlock_t * BasicBlock;
typedef struct LocalVariable_t * LocalVariable;
typedef struct RegDescriptor_t * RegDescriptor;
typedef struct LineNo_t * LineNo;

struct LineNo_t{
    int num;
    LineNo next;
};

struct LocalVariable_t{
    Operand operand;
    int offset;                 // 在栈内的偏移量
    int inMemory;               // 是否在内存中
    int regIndex;               // 存在的寄存器下标
    LineNo useList;
    LocalVariable next;
    LocalVariable regNext;
};

struct BasicBlock_t{
    InterCode begin;
    InterCode end;
    int endLineNo;
    BasicBlock next;
};

struct FunctionBlock_t{
    BasicBlock begin;
    BasicBlock end;
    LocalVariable varList;
    int totalSize;
    FunctionBlock next;
};

struct RegDescriptor_t{
    LocalVariable varList;
    int isConst;
};

struct RegDescriptor_t regDescriptor[32];
FunctionBlock function_block_head;
FunctionBlock function_block_tail;
BasicBlock basic_block_head;
BasicBlock basic_block_tail;

char* regName[32] = {"$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", 
                     "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"};

void blocking();


int isFree(int index);
void translateToMisp32(char* output);
void initBlock();
LocalVariable newLocalVariable(Operand operand, int offset);
FunctionBlock newFunctionBlock(BasicBlock begin);
BasicBlock newBasicBlock(InterCode begin);
void insertLocalVariable(LocalVariable local, FunctionBlock functionBlock);
void insertFunctionBlock(FunctionBlock functionBlock);
void insertBasicBlock(BasicBlock basicBlock);

void addToStack(FunctionBlock functionBlock, Operand operand, int lineNo);
void addUseLine(LocalVariable localVariable, int lineNo);
int equalOperand(Operand op1, Operand op2);

char* getReg(FILE* fp, Operand operand, FunctionBlock functionBlock, BasicBlock basicBlock, int lineNo);
int overrideReg(FILE* fp, int curLineNo, int endLineNo);
LocalVariable findLocalVariable(Operand operand, FunctionBlock functionBlock);

#endif