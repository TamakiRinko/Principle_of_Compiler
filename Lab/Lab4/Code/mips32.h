#ifndef _MIPS_32_H_
#define _MIPS_32_H_

#include "ir.h"

#define print_lab_4

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

int indexArray[5];
struct RegDescriptor_t regDescriptor[32];
FunctionBlock function_block_head;
FunctionBlock function_block_tail;
BasicBlock basic_block_head;
BasicBlock basic_block_tail;

void blocking();

int getEmptyArrayIndex();

int isFree(int index);
void translateToMisp32(char* output);
void initBlock();
void printMips32Head(FILE* fp);
void generateMips32(FILE* fp);
LocalVariable newLocalVariable(Operand operand, int offset);
FunctionBlock newFunctionBlock(BasicBlock begin);
BasicBlock newBasicBlock(InterCode begin);
void insertLocalVariable(LocalVariable local, FunctionBlock functionBlock);
void insertFunctionBlock(FunctionBlock functionBlock);
void insertBasicBlock(BasicBlock basicBlock);

void addToStack(FunctionBlock functionBlock, Operand operand, int lineNo);
void addUseLine(LocalVariable localVariable, int lineNo);
int equalOperand(Operand op1, Operand op2);

int getReg(FILE* fp, Operand operand, FunctionBlock functionBlock, BasicBlock basicBlock, int lineNo);
int getRegForAllKind(FILE* fp, Operand operand, FunctionBlock functionBlock, BasicBlock basicBlock, int lineNo);
int overrideReg(FILE* fp, int curLineNo, int endLineNo);
void saveAllRegs(FILE* fp);
LocalVariable findLocalVariable(Operand operand, FunctionBlock functionBlock);
void freeRegs(FILE* fp, int lineNo, BasicBlock curBasic);

void freeVariable(int index, LocalVariable localVariable);
void printOneInterCode(FILE* fp, InterCode cur);
void printOneOperand(FILE* fp, Operand operand);

#endif