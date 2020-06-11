#include "mips32.h"
#ifndef print_lab_4

char* regName[32] = {"$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", 
                     "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"};

void initBlock(){
    function_block_head = (FunctionBlock)malloc(sizeof(struct FunctionBlock_t));
    function_block_head->next = NULL;
    function_block_tail = function_block_head;

    basic_block_head = (BasicBlock)malloc(sizeof(struct BasicBlock_t));
    basic_block_head->next = NULL;
    basic_block_head->endLineNo = -1;
    basic_block_tail = basic_block_head;

    for(int i = 0; i < 32; ++i){
        regDescriptor[i].varList = (LocalVariable)malloc(sizeof(struct LocalVariable_t));
        regDescriptor[i].varList->regNext = NULL;
        regDescriptor[i].isConst = 0;
    }

    indexArray[0] = indexArray[1] = indexArray[2] = indexArray[3] = indexArray[4] = -1;

}

int getEmptyArrayIndex(){
    for(int i = 0; i < 5; ++i){
        if(indexArray[i] == -1){
            return i;
        }
    }
}

LocalVariable newLocalVariable(Operand operand, int offset){
    LocalVariable result = (LocalVariable)malloc(sizeof(struct LocalVariable_t));
    result->useList = (LineNo)malloc(sizeof(struct LineNo_t));
    result->useList->next = NULL;
    result->offset = offset;
    result->operand = operand;
    result->regIndex = -1;
    result->inMemory = 1;
    result->regNext = NULL;
    result->next = NULL;
    return result;
}

FunctionBlock newFunctionBlock(BasicBlock begin){
    FunctionBlock result = (FunctionBlock)malloc(sizeof(struct FunctionBlock_t));
    result->begin = begin;
    result->varList = (LocalVariable)malloc(sizeof(struct LocalVariable_t));
    result->totalSize = 4;      // 腾出４字节存储旧的ebp
    result->end = NULL;
    result->next = NULL;
    return result;
}

BasicBlock newBasicBlock(InterCode begin){
    BasicBlock result = (BasicBlock)malloc(sizeof(struct BasicBlock_t));
    result->begin = begin;
    result->end = NULL;
    result->next = NULL;
    result->endLineNo = -1;
    return result;
}

void insertLocalVariable(LocalVariable local, FunctionBlock functionBlock){
    local->next = functionBlock->varList->next;
    functionBlock->varList->next = local;
}

void insertFunctionBlock(FunctionBlock functionBlock){
    functionBlock->next = function_block_tail->next;
    function_block_tail->next = functionBlock;
    function_block_tail = function_block_tail->next;
}

void insertBasicBlock(BasicBlock basicBlock){
    basicBlock->next = basic_block_tail->next;
    basic_block_tail->next = basicBlock;
    basic_block_tail = basic_block_tail->next;
}

int equalOperand(Operand op1, Operand op2){
    if(op1->kind != op2->kind)  return 0;
    switch(op1->kind){
        case ADDRESS:
        case REFERENCE:
        case VARIABLE:{
            return op1->u.variable.var_num == op2->u.variable.var_num;
        }
        case TEMPORARY_VARIABLE:
        case TEMPORARY_ADDRESS:{
            return op1->u.num == op2->u.num;
        }
        default:{
            printf("OperandKind wrong!\n");
        }
    }
    return 0;
}

void addToStack(FunctionBlock functionBlock, Operand operand, int lineNo){
    if(operand == NULL) return;
    enum OperandKind kind = operand->kind;
    if(kind != CONSTANT && kind != LABEL_OPERAND && kind != FUNCTION_OPERAND){
        LocalVariable cur = functionBlock->varList->next;
        while(cur != NULL){
            if(equalOperand(cur->operand, operand)){
                break;
            }
            cur = cur->next;
        }
        if(cur == NULL){
            LocalVariable localVariable = newLocalVariable(operand, functionBlock->totalSize);
            insertLocalVariable(localVariable, functionBlock);
            addUseLine(localVariable, lineNo);
            functionBlock->totalSize += 4;
        }else{
            addUseLine(cur, lineNo);
        }
    }
}

void addUseLine(LocalVariable localVariable, int lineNo){
    LineNo cur = localVariable->useList;
    while(cur->next != NULL){
        cur = cur->next;
    }
    cur->next = (LineNo)malloc(sizeof(struct LineNo_t));
    cur->next->num = lineNo;
    cur->next->next = NULL;
}

void translateToMisp32(char* output){
    FILE* fp = fopen(output, "w");
    initBlock();
    blocking();
    printMips32Head(fp);
    generateMips32(fp);
}

void printMips32Head(FILE* fp){
    fprintf(fp, ".data\n");
    fprintf(fp, "_prompt: .asciiz \"Enter an integer:\"\n");
    fprintf(fp, "_ret: .asciiz \"\\n\"\n");
    fprintf(fp, ".globl main\n");
    fprintf(fp, ".text\n");
    fprintf(fp, "read:\n");
    fprintf(fp, "  li $v0, 4\n");
    fprintf(fp, "  la $a0, _prompt\n");
    fprintf(fp, "  syscall\n");
    fprintf(fp, "  li $v0, 5\n");
    fprintf(fp, "  syscall\n");
    fprintf(fp, "  jr $ra\n");
    fprintf(fp, "\n");
    fprintf(fp, "write:\n");
    fprintf(fp, "  li $v0, 1\n");
    fprintf(fp, "  syscall\n");
    fprintf(fp, "  li $v0, 4\n");
    fprintf(fp, "  la $a0, _ret\n");
    fprintf(fp, "  syscall\n");
    fprintf(fp, "  move $v0, $0\n");
    fprintf(fp, "  jr $ra\n");
    fprintf(fp, "\n");
}

void blocking(){
    int lineNo = 0;
    InterCode cur = inter_code_head->next;
    FunctionBlock curFunctionBlock = NULL;
    BasicBlock curBasicBlock = NULL;
    while(cur != inter_code_head){
        switch(cur->kind){
            case FUNCTION_INTERCODE:{
                // 函数开始
                BasicBlock basicBlock = newBasicBlock(cur);
                insertBasicBlock(basicBlock);
                FunctionBlock functionBlock = newFunctionBlock(basicBlock);
                insertFunctionBlock(functionBlock);
                curFunctionBlock = functionBlock;
                curBasicBlock = basicBlock;
                lineNo = 0;
                break;
            }
            case LABEL_INTERCODE:{
                BasicBlock basicBlock = newBasicBlock(cur);
                insertBasicBlock(basicBlock);
                curBasicBlock = basicBlock;
                break;
            }
            case GOTO:
            case JE:
            case JNE:
            case JA:
            case JAE:
            case JB:
            case JBE:{
                // 收尾
                curBasicBlock->end = cur;
                curBasicBlock->endLineNo = lineNo;
                break;
            }
            case RETURN:{
                // 函数和基本块收尾
                curBasicBlock->end = cur;
                curBasicBlock->endLineNo = lineNo;
                curFunctionBlock->end = curBasicBlock;
                break;
            }
            case ASSIGN:{
                addToStack(curFunctionBlock, cur->op1, lineNo);
                addToStack(curFunctionBlock, cur->result, lineNo);
                break;
            }
            case PLUS:
            case MINUS:
            case STAR:
            case DIV:{
                addToStack(curFunctionBlock, cur->op1, lineNo);
                addToStack(curFunctionBlock, cur->op2, lineNo);
                addToStack(curFunctionBlock, cur->result, lineNo);
                break;
            }
            case DEC:{
                int decSize = cur->op2->u.const_value;
                curFunctionBlock->totalSize += (decSize - 4);
                addToStack(curFunctionBlock, cur->op1, lineNo);
                break;
            }
            case CALL:{
                addToStack(curFunctionBlock, cur->op1, lineNo);
                addToStack(curFunctionBlock, cur->result, lineNo);
                // 函数和基本块收尾
                curBasicBlock->end = cur;
                curBasicBlock->endLineNo = lineNo;
                break;
            }
            case PARAM:{
                addToStack(curFunctionBlock, cur->op1, lineNo);
                break;
            }
            case ARG:
            case READ:
            case WRITE:{
                addToStack(curFunctionBlock, cur->result, lineNo);
                break;
            }
        }
        if(cur->next != inter_code_head && cur->next->kind == LABEL_INTERCODE){
            // 收尾
            curBasicBlock->end = cur;
            curBasicBlock->endLineNo = lineNo;
        }
        if(cur->prev != inter_code_head && cur->kind != LABEL_INTERCODE && cur->kind != FUNCTION_INTERCODE){
            // enum InterCodeKind kind = cur->prev->kind;
            if(cur->prev->kind == GOTO || cur->prev->kind == JE || cur->prev->kind == JNE 
            || cur->prev->kind == JA || cur->prev->kind == JAE || cur->prev->kind == JB 
            || cur->prev->kind == JBE || cur->prev->kind == CALL || cur->prev->kind == RETURN){
                // 跳转指令的下一条指令
                BasicBlock basicBlock = newBasicBlock(cur);
                insertBasicBlock(basicBlock);
                curBasicBlock = basicBlock;
            }
        }
        lineNo++;
        cur = cur->next;
    }
}

int getReg(FILE* fp, Operand operand, FunctionBlock functionBlock, BasicBlock basicBlock, int lineNo){
    if(operand == NULL){
        // 直接申请一个寄存器
        for(int i = 8; i < 26; ++i){
            if(isFree(i)){
                // 有空寄存器
                regDescriptor[i].isConst = 1;
                return i;
            }
        }
        // 无空寄存器
        int index = overrideReg(fp, lineNo, basicBlock->endLineNo);
        regDescriptor[index].isConst = 1;
        return index;
    }else if(operand->kind == CONSTANT){
        // 常数，放入寄存器
        for(int i = 8; i < 26; ++i){
            if(isFree(i)){
                // 有空寄存器
                regDescriptor[i].isConst = 1;
                fprintf(fp,"  li %s, %d\n", regName[i], operand->u.const_value);
                return i;
            }
        }
        // 无空寄存器
        int index = overrideReg(fp, lineNo, basicBlock->endLineNo);
        regDescriptor[index].isConst = 1;
        fprintf(fp," li %s, %d\n", regName[index], operand->u.const_value);
        return index;
    }else if(operand->kind != LABEL_OPERAND && operand->kind != FUNCTION_OPERAND){
        // t/v，存入寄存器
        LocalVariable operandVariable = findLocalVariable(operand, functionBlock);
        if(operandVariable->regIndex != -1){
            // 已经在寄存器中
            return operandVariable->regIndex;
        }else{
            for(int i = 8; i < 26; ++i){
                if(isFree(i)){
                    // 有空寄存器
                    regDescriptor[i].varList->regNext = operandVariable;
                    operandVariable->regIndex = i;
                    fprintf(fp,"  lw %s, -%d($fp)\n", regName[i], operandVariable->offset);
                    return i;
                }
            }
            // 无空寄存器
            int index = overrideReg(fp, lineNo, basicBlock->endLineNo);
            regDescriptor[index].varList->regNext = operandVariable;
            operandVariable->regIndex = index;
            fprintf(fp,"  lw %s, -%d($fp)\n", regName[index], operandVariable->offset);
            return index;
        }
    }
}

int getRegForAllKind(FILE* fp, Operand operand, FunctionBlock functionBlock, BasicBlock basicBlock, int lineNo){
    if(operand == NULL){
        int index = getReg(fp, operand, functionBlock, basicBlock, lineNo);
        int x = getEmptyArrayIndex();
        indexArray[x] = index;
        return index;
    }else if(operand->kind == ADDRESS || operand->kind == TEMPORARY_ADDRESS){
        int index1 = getReg(fp, operand, functionBlock, basicBlock, lineNo);
        int index2 = getReg(fp, NULL, functionBlock, basicBlock, lineNo);
        // t = *x
        fprintf(fp, "  lw %s, 0(%s)\n", regName[index2], regName[index1]);
        int x1 = getEmptyArrayIndex();
        indexArray[x1] = index1;
        int x2 = getEmptyArrayIndex();
        indexArray[x2] = index2;
        return index2;
    }else if(operand->kind == REFERENCE){
        // 为立即数申请
        int index1 = getReg(fp, NULL, functionBlock, basicBlock, lineNo);
        // 为临时变量申请
        int index2 = getReg(fp, NULL, functionBlock, basicBlock, lineNo);
        // t = &x
        fprintf(fp, "  addi %s, $fp, -%d\n", regName[index2], findLocalVariable(operand, functionBlock)->offset);
        int x1 = getEmptyArrayIndex();
        indexArray[x1] = index1;
        int x2 = getEmptyArrayIndex();
        indexArray[x2] = index2;
        return index2;
    }else{
        int index = getReg(fp, operand, functionBlock, basicBlock, lineNo);
        int x = getEmptyArrayIndex();
        indexArray[x] = index;
        return index;
    }
}

int overrideReg(FILE* fp, int curLineNo, int endLineNo){
    int indexMax = 8;
    int lineNoMax = -1;
    for(int i = 8; i < 26; ++i){
        int regDesMin = 0x7FFFFFFF;
        if(regDescriptor[i].isConst == 1)   continue;
        LocalVariable cur = regDescriptor[i].varList->regNext;
        while(cur != NULL){
            LineNo curLine = cur->useList->next;
            while(curLine != NULL){
                if(curLine->num > curLineNo && curLine->num <= endLineNo){
                    // 每个寄存器找最小的
                    regDesMin = (regDesMin>curLine->num)?curLine->num:regDesMin;
                    break;
                }
                curLine = curLine->next;
            }
            cur = cur->regNext;
        }
        if(lineNoMax < regDesMin){
            // 寄存器间找最大的
            lineNoMax = regDesMin;
            indexMax = i;
        }
    }
    LocalVariable cur1 = regDescriptor[lineNoMax].varList->regNext;
    while(cur1 != NULL){
        // 修改地址描述符
        cur1->regIndex = -1;
        if(cur1->inMemory == 0){
            fprintf(fp, "  sw %s, -%d($fp)\n", regName[lineNoMax], cur1->offset);
            cur1->inMemory = 1;
        }
        cur1 = cur1->regNext;
    }
    // 清空该寄存器
    regDescriptor[lineNoMax].isConst = 0;
    regDescriptor[lineNoMax].varList->regNext = NULL;
    return lineNoMax;
}

LocalVariable findLocalVariable(Operand operand, FunctionBlock functionBlock){
    LocalVariable cur = functionBlock->varList->next;
    while(cur != NULL){
        if(equalOperand(cur->operand, operand)){
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

int isFree(int index){
    if(regDescriptor[index].isConst == 0 && regDescriptor[index].varList->regNext == NULL)  return 1;
    return 0;
}

void saveAllRegs(FILE* fp){
    for(int i = 8; i < 26; ++i){
        LocalVariable cur = regDescriptor[i].varList->regNext;
        while(cur != NULL){
            cur->regIndex = -1;
            if(cur->inMemory == 0){
                fprintf(fp, "  sw %s, -%d($fp)\n", regName[i], cur->offset);
                cur->inMemory = 1;
            }
            cur = cur->regNext;
        }
        regDescriptor[i].varList->regNext = NULL;
        regDescriptor[i].isConst = 0;
    }
}

// b = a[1]
// t1 = &v1 + 4
// v2 = *t1

void generateMips32(FILE* fp){
    FunctionBlock curFunction = function_block_head->next;
    while(curFunction != NULL){
        int lineNo = 0;
        BasicBlock curBasic = curFunction->begin;
        while(curBasic != curFunction->end->next){
            InterCode curInterCode = curBasic->begin;
            while(curInterCode != curBasic->end->next){
                switch(curInterCode->kind){
                    case LABEL_INTERCODE:{
                        fprintf(fp, "label%d:\n", curInterCode->op1->u.num);
                        break;
                    }
                    case FUNCTION_INTERCODE:{
                        fprintf(fp, "%s:\n", curInterCode->op1->u.name);
                        fprintf(fp, "  addi $sp, $sp, -4\n");
                        fprintf(fp, "  sw $fp, 0($sp)\n");
                        fprintf(fp, "  move $fp, $sp\n");
                        fprintf(fp, "  addi $sp, $sp, -%d\n", curFunction->totalSize);
                        break;
                    }
                    case ASSIGN:{
                        int index0 = -1;
                        int index1 = -1;
                        int index2 = -1;
                        
                        if(curInterCode->op1->kind == ADDRESS && curInterCode->result->kind == ADDRESS){
                            // *x = *y
                            index0 = getReg(fp, curInterCode->result, curFunction, curBasic, lineNo);
                            index1 = getReg(fp, curInterCode->op1, curFunction, curBasic, lineNo);
                            index2 = getReg(fp, NULL, curFunction, curBasic, lineNo);
                            fprintf(fp, "  lw %s, 0(%s)\n", regName[index2], regName[index1]);
                            fprintf(fp, "  sw %s, 0(%s)\n", regName[index2], regName[index0]);
                        }else if(curInterCode->op1->kind == REFERENCE){
                            // x = &y
                            index0 = getReg(fp, curInterCode->result, curFunction, curBasic, lineNo);
                            index1 = getReg(fp, NULL, curFunction, curBasic, lineNo);
                            fprintf(fp, "  addi %s, $fp, -%d\n", regName[index0], findLocalVariable(curInterCode->op1, curFunction)->offset);
                            findLocalVariable(curInterCode->result, curFunction)->inMemory = 0;
                        }else if(curInterCode->result->kind == ADDRESS){
                            // *x = y
                            index0 = getReg(fp, curInterCode->result, curFunction, curBasic, lineNo);
                            index1 = getReg(fp, curInterCode->op1, curFunction, curBasic, lineNo);
                            fprintf(fp, "  sw %s, 0(%s)\n", regName[index1], regName[index0]);
                        }else if(curInterCode->op1->kind == ADDRESS){
                            // x = *y
                            index0 = getReg(fp, curInterCode->result, curFunction, curBasic, lineNo);
                            index1 = getReg(fp, curInterCode->op1, curFunction, curBasic, lineNo);
                            fprintf(fp, "  lw %s, 0(%s)\n", regName[index0], regName[index1]);
                            findLocalVariable(curInterCode->result, curFunction)->inMemory = 0;
                        }else{
                            // x = y
                            printf("haha\n");
                            printf("kind = %d, resultKind = %d, op1Kind = %d, ", curInterCode->kind, curInterCode->result->kind, curInterCode->op1->kind);
                            printf("op1->name = %s, op2->name = %s\n", curInterCode->result->u.variable.var_name, curInterCode->op1->u.variable.var_name);
                            if(curInterCode->op1->kind == CONSTANT){
                                index0 = getReg(fp, curInterCode->result, curFunction, curBasic, lineNo);
                                fprintf(fp, "  li %s, %d\n", regName[index0], curInterCode->op1->u.const_value);
                            }else{
                                index1 = getReg(fp, curInterCode->op1, curFunction, curBasic, lineNo);
                                LocalVariable result = findLocalVariable(curInterCode->result, curFunction);
                                if(result->regIndex == -1){
                                    // x不在寄存器中
                                    result->regIndex = index1;
                                    result->regNext = regDescriptor[index1].varList->regNext;
                                    regDescriptor[index1].varList->regNext = result;
                                }else if(result->regIndex != index1){
                                    // x在其他寄存器中
                                    freeVariable(result->regIndex, result);
                                    result->regIndex = index1;
                                    result->regNext = regDescriptor[index1].varList->regNext;
                                    regDescriptor[index1].varList->regNext = result;
                                }else{
                                    // x就在该寄存器中
                                }
                            }
                            findLocalVariable(curInterCode->result, curFunction)->inMemory = 0;
                        }
                        indexArray[0] = index0;
                        indexArray[1] = index1;
                        indexArray[2] = index2;
                        break;
                    }
                    case PLUS:{
                        int index0 = getRegForAllKind(fp, curInterCode->result, curFunction, curBasic, lineNo);
                        int index1 = getRegForAllKind(fp, curInterCode->op1, curFunction, curBasic, lineNo);
                        int index2 = getRegForAllKind(fp, curInterCode->op2, curFunction, curBasic, lineNo);
                        if(curInterCode->op1->kind == CONSTANT){
                            fprintf(fp, "  addi %s, %s, %d\n", regName[index0], regName[index2], 
                                                           curInterCode->op1->u.const_value);
                        }else if(curInterCode->op2->kind == CONSTANT){
                            fprintf(fp, "  addi %s, %s, %d\n", regName[index0], regName[index1],
                                                           curInterCode->op2->u.const_value);
                        }else{
                            fprintf(fp, "  add %s, %s, %s\n", regName[index0], regName[index1], 
                                                           regName[index2]);
                        }
                        findLocalVariable(curInterCode->result, curFunction)->inMemory = 0;
                        break;
                    }
                    case MINUS:{
                        int index0 = getRegForAllKind(fp, curInterCode->result, curFunction, curBasic, lineNo);
                        int index1 = getRegForAllKind(fp, curInterCode->op1, curFunction, curBasic, lineNo);
                        int index2 = getRegForAllKind(fp, curInterCode->op2, curFunction, curBasic, lineNo);
                        if(curInterCode->op2->kind == CONSTANT){
                            fprintf(fp, "  addi %s, %s, %d\n", regName[index0], regName[index1],
                                                           -curInterCode->op2->u.const_value);
                        }else{
                            fprintf(fp, "  sub %s, %s, %s\n", regName[index0], regName[index1], 
                                                           regName[index2]);
                        }
                        findLocalVariable(curInterCode->result, curFunction)->inMemory = 0;
                        break;
                    }
                    case STAR:{
                        int index0 = getRegForAllKind(fp, curInterCode->result, curFunction, curBasic, lineNo);
                        int index1 = getRegForAllKind(fp, curInterCode->op1, curFunction, curBasic, lineNo);
                        int index2 = getRegForAllKind(fp, curInterCode->op2, curFunction, curBasic, lineNo);
                        fprintf(fp, "  mul %s, %s, %s\n", regName[index0], regName[index1], 
                                                           regName[index2]);
                        findLocalVariable(curInterCode->result, curFunction)->inMemory = 0;
                        break;
                    }
                    case DIV:{
                        int index0 = getRegForAllKind(fp, curInterCode->result, curFunction, curBasic, lineNo);
                        int index1 = getRegForAllKind(fp, curInterCode->op1, curFunction, curBasic, lineNo);
                        int index2 = getRegForAllKind(fp, curInterCode->op2, curFunction, curBasic, lineNo);
                        fprintf(fp, "  div %s, %s\n", regName[index1], regName[index2]);
                        fprintf(fp, "  mflo %s\n", regName[index0]);
                        findLocalVariable(curInterCode->result, curFunction)->inMemory = 0;
                        break;
                    }
                    case GOTO:{
                        fprintf(fp, "  j label%d\n", curInterCode->result->u.num);
                        break;
                    }
                    case JE:{
                        int index1 = getReg(fp, curInterCode->op1, curFunction, curBasic, lineNo);
                        int index2 = getReg(fp, curInterCode->op2, curFunction, curBasic, lineNo);
                        fprintf(fp, "  beq %s, %s, label%d\n", regName[index1], regName[index2],
                                                           curInterCode->result->u.num);
                        indexArray[1] = index1;
                        indexArray[2] = index2;
                        break;
                    }
                    case JNE:{
                        int index1 = getReg(fp, curInterCode->op1, curFunction, curBasic, lineNo);
                        int index2 = getReg(fp, curInterCode->op2, curFunction, curBasic, lineNo);
                        fprintf(fp, "  bne %s, %s, label%d\n", regName[index1], regName[index2],
                                                           curInterCode->result->u.num);
                        indexArray[1] = index1;
                        indexArray[2] = index2;
                        break;
                    }
                    case JA:{
                        int index1 = getReg(fp, curInterCode->op1, curFunction, curBasic, lineNo);
                        int index2 = getReg(fp, curInterCode->op2, curFunction, curBasic, lineNo);
                        fprintf(fp, "  bgt %s, %s, label%d\n", regName[index1], regName[index2],
                                                           curInterCode->result->u.num);
                        indexArray[1] = index1;
                        indexArray[2] = index2;
                        break;
                    }
                    case JAE:{
                        int index1 = getReg(fp, curInterCode->op1, curFunction, curBasic, lineNo);
                        int index2 = getReg(fp, curInterCode->op2, curFunction, curBasic, lineNo);
                        fprintf(fp, "  bge %s, %s, label%d\n", regName[index1], regName[index2],
                                                           curInterCode->result->u.num);
                        indexArray[1] = index1;
                        indexArray[2] = index2;
                        break;
                    }
                    case JB:{
                        int index1 = getReg(fp, curInterCode->op1, curFunction, curBasic, lineNo);
                        int index2 = getReg(fp, curInterCode->op2, curFunction, curBasic, lineNo);
                        fprintf(fp, "  blt %s, %s, label%d\n", regName[index1], regName[index2],
                                                           curInterCode->result->u.num);
                        indexArray[1] = index1;
                        indexArray[2] = index2;
                        break;
                    }
                    case JBE:{
                        int index1 = getReg(fp, curInterCode->op1, curFunction, curBasic, lineNo);
                        int index2 = getReg(fp, curInterCode->op2, curFunction, curBasic, lineNo);
                        fprintf(fp, "  ble %s, %s, label%d\n", regName[index1], regName[index2],
                                                           curInterCode->result->u.num);
                        indexArray[1] = index1;
                        indexArray[2] = index2;
                        break;
                    }
                    case RETURN:{
                        int index = getRegForAllKind(fp, curInterCode->op1, curFunction, curBasic, lineNo);
                        fprintf(fp, "  move $v0, %s\n", regName[index]);
                        fprintf(fp, "  move $sp, $fp\n");
                        fprintf(fp, "  lw $fp, 0($sp)\n");
                        fprintf(fp, "  addi $sp, $sp, 4\n");
                        fprintf(fp, "  jr $ra\n");
                        break;
                    }
                    case DEC:{
                        break;
                    }
                    case ARG:{
                        break;
                    }
                    case CALL:{
                        InterCode cur = curInterCode->prev;
                        int x = 12;
                        while(cur->kind == ARG){
                            int index1 = getRegForAllKind(fp, cur->op1, curFunction, curBasic, lineNo);
                            fprintf(fp, "  sw %s, -%d($sp)\n", regName[index1], x);
                            x = x + 4;
                            freeRegs(fp, lineNo, curBasic);
                            cur = cur->prev;
                        }
                        fprintf(fp, "  addi $sp, $sp, -4\n");
                        fprintf(fp, "  sw $ra, 0($sp)\n");
                        fprintf(fp, "  jal %s\n", curInterCode->op1->u.name);
                        fprintf(fp, "  lw $ra, 0($sp)\n");
                        fprintf(fp, "  addi $sp, $sp, 4\n");
                        int resultIndex = getRegForAllKind(fp, cur->result, curFunction, curBasic, lineNo);
                        fprintf(fp, "  move %s, $v0\n", regName[resultIndex]);
                        break;
                    }
                    case PARAM:{
                        break;
                    }
                    case READ:{
                        fprintf(fp, "  addi $sp, $sp, -4\n");
                        fprintf(fp, "  sw $ra, 0($sp)\n");
                        fprintf(fp, "  jal read\n");
                        fprintf(fp, "  lw $ra, 0($sp)\n");
                        fprintf(fp, "  addi $sp, $sp, 4\n");
                        int resultIndex = getRegForAllKind(fp, curInterCode->result, curFunction, curBasic, lineNo);
                        fprintf(fp, "  move %s, $v0\n", regName[resultIndex]);
                        break;
                    }
                    case WRITE:{
                        int paramIndex = getRegForAllKind(fp, curInterCode->result, curFunction, curBasic, lineNo);
                        fprintf(fp, "  move $a0, %s\n", regName[paramIndex]);
                        fprintf(fp, "  addi $sp, $sp, -4\n");
                        fprintf(fp, "  sw $ra, 0($sp)\n");
                        fprintf(fp, "  jal write\n");
                        fprintf(fp, "  lw $ra, 0($sp)\n");
                        fprintf(fp, "  addi $sp, $sp, 4\n");
                        break;
                    }
                    default: break;
                }
                freeRegs(fp, lineNo, curBasic);
                curInterCode = curInterCode->next;
                lineNo++;
            }
            // 每个BasicBlock末尾写会内存
            saveAllRegs(fp);
            curBasic = curBasic->next;
        }
        curFunction = curFunction->next;
    }
}

void freeRegs(FILE* fp, int lineNo, BasicBlock curBasic){
    // Free reg
    for(int i = 0; i < 5; ++i){
        if(indexArray[i] != -1){
            if(regDescriptor[indexArray[i]].isConst == 1){
                // 常数可直接删去
                regDescriptor[indexArray[i]].isConst = 0;
                regDescriptor[indexArray[i]].varList->regNext = NULL;
            }else{
                LocalVariable cur = regDescriptor[indexArray[i]].varList->regNext;
                int willBeUsed = 0;
                while(cur != NULL){
                    LineNo curLineNo = cur->useList->next;
                    while(curLineNo !=  NULL){
                        if(curLineNo->num > lineNo && curLineNo->num <= curBasic->endLineNo){
                            // 每个寄存器找最小的
                            willBeUsed = 1;
                            break;
                        }
                        curLineNo = curLineNo->next;
                    }
                    if(willBeUsed == 1) break;
                    cur = cur->regNext;
                }
                if(willBeUsed == 0){
                    // 后续不会被使用，溢出到栈
                    cur = regDescriptor[indexArray[i]].varList->regNext;
                    while(cur != NULL){
                        cur->regIndex = -1;
                        if(cur->inMemory == 0){
                            fprintf(fp, "  sw %s, -%d($fp)\n", regName[indexArray[i]], cur->offset);
                            cur->inMemory = 1;
                        }
                        cur = cur->regNext;
                    }
                    regDescriptor[indexArray[i]].varList->regNext = NULL;
                    regDescriptor[indexArray[i]].isConst = 0;
                }
            }
        }
        indexArray[i] = -1;
    }
}

void freeVariable(int index, LocalVariable localVariable){
    // 将liveVariable从regDescriptor[index]中删除
    LocalVariable cur = regDescriptor[index].varList->regNext;
    LocalVariable pre = regDescriptor[index].varList;
    while(cur != NULL){
        if(equalOperand(cur->operand, localVariable->operand) == 1){
            pre->regNext = cur->regNext;
            cur->regNext = NULL;
            break;
        }
        pre = cur;
        cur = cur->regNext;
    }
    localVariable->regIndex = -1;
}

#else


char* regName[32] = {"$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3", "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", 
                     "$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp", "$ra"};

void initBlock(){
    function_block_head = (FunctionBlock)malloc(sizeof(struct FunctionBlock_t));
    function_block_head->next = NULL;
    function_block_tail = function_block_head;

    basic_block_head = (BasicBlock)malloc(sizeof(struct BasicBlock_t));
    basic_block_head->next = NULL;
    basic_block_head->endLineNo = -1;
    basic_block_tail = basic_block_head;

    for(int i = 0; i < 32; ++i){
        regDescriptor[i].varList = (LocalVariable)malloc(sizeof(struct LocalVariable_t));
        regDescriptor[i].varList->regNext = NULL;
        regDescriptor[i].isConst = 0;
    }

    indexArray[0] = indexArray[1] = indexArray[2] = indexArray[3] = indexArray[4] = -1;

}

int getEmptyArrayIndex(){
    for(int i = 0; i < 5; ++i){
        if(indexArray[i] == -1){
            return i;
        }
    }
}

LocalVariable newLocalVariable(Operand operand, int offset){
    LocalVariable result = (LocalVariable)malloc(sizeof(struct LocalVariable_t));
    result->useList = (LineNo)malloc(sizeof(struct LineNo_t));
    result->useList->next = NULL;
    result->offset = offset;
    result->operand = operand;
    result->regIndex = -1;
    result->inMemory = 1;
    result->regNext = NULL;
    result->next = NULL;
    return result;
}

FunctionBlock newFunctionBlock(BasicBlock begin){
    FunctionBlock result = (FunctionBlock)malloc(sizeof(struct FunctionBlock_t));
    result->begin = begin;
    result->varList = (LocalVariable)malloc(sizeof(struct LocalVariable_t));
    result->varList->next = NULL;
    result->totalSize = 4;      // 腾出４字节存储旧的ebp
    result->end = NULL;
    result->next = NULL;
    return result;
}

BasicBlock newBasicBlock(InterCode begin){
    BasicBlock result = (BasicBlock)malloc(sizeof(struct BasicBlock_t));
    result->begin = begin;
    result->end = NULL;
    result->next = NULL;
    result->endLineNo = -1;
    return result;
}

void insertLocalVariable(LocalVariable local, FunctionBlock functionBlock){
    local->next = functionBlock->varList->next;
    functionBlock->varList->next = local;
}

void insertFunctionBlock(FunctionBlock functionBlock){
    functionBlock->next = function_block_tail->next;
    function_block_tail->next = functionBlock;
    function_block_tail = function_block_tail->next;
}

void insertBasicBlock(BasicBlock basicBlock){
    basicBlock->next = basic_block_tail->next;
    basic_block_tail->next = basicBlock;
    basic_block_tail = basic_block_tail->next;
}

int equalOperand(Operand op1, Operand op2){
    // if(op1->kind != op2->kind)  return 0;
    // switch(op1->kind){
    //     case ADDRESS:
    //     case REFERENCE:
    //     case VARIABLE:{
    //         return op1->u.variable.var_num == op2->u.variable.var_num;
    //     }
    //     case TEMPORARY_VARIABLE:
    //     case TEMPORARY_ADDRESS:{
    //         return op1->u.num == op2->u.num;
    //     }
    //     default:{
    //         printf("OperandKind wrong!\n");
    //     }
    // }
    if(op1->kind == ADDRESS || op1->kind == REFERENCE || op1->kind == VARIABLE){
        if(op2->kind == TEMPORARY_VARIABLE || op2->kind == TEMPORARY_ADDRESS){
            return 0;
        }else{
            return op1->u.variable.var_num == op2->u.variable.var_num;
        }
    }else if(op1->kind == TEMPORARY_VARIABLE || op1->kind == TEMPORARY_ADDRESS){
        if(op2->kind == ADDRESS || op2->kind == REFERENCE || op2->kind == VARIABLE){
            return 0;
        }else{
            return op1->u.num == op2->u.num;
        }
    }
    return 0;
}

void addToStack(FunctionBlock functionBlock, Operand operand, int lineNo){
    if(operand == NULL) return;
    enum OperandKind kind = operand->kind;
    if(kind != CONSTANT && kind != LABEL_OPERAND && kind != FUNCTION_OPERAND){
        LocalVariable cur = functionBlock->varList->next;
        while(cur != NULL){
            if(equalOperand(cur->operand, operand)){
                break;
            }
            cur = cur->next;
        }
        if(cur == NULL){
            LocalVariable localVariable = newLocalVariable(operand, functionBlock->totalSize);
            insertLocalVariable(localVariable, functionBlock);
            addUseLine(localVariable, lineNo);
            functionBlock->totalSize += 4;
        }else{
            addUseLine(cur, lineNo);
        }
    }
}

void addUseLine(LocalVariable localVariable, int lineNo){
    LineNo cur = localVariable->useList;
    while(cur->next != NULL){
        cur = cur->next;
    }
    cur->next = (LineNo)malloc(sizeof(struct LineNo_t));
    cur->next->num = lineNo;
    cur->next->next = NULL;
}

void translateToMisp32(char* output){
    FILE* fp = fopen(output, "w");
    initBlock();
    blocking();
    // BasicBlock cur1 = basic_block_head->next;
    // while(cur1 != NULL){
    //     printOneInterCode(fp, cur1->begin);
    //     cur1 = cur1->next;
    // }
    // printf("\n");
    // printf("\n");
    // FunctionBlock cur2 = function_block_head->next;
    // while(cur2 != NULL){
    //     printOneInterCode(fp, cur2->begin->begin);
    //     BasicBlock cur3 = cur2->begin;
    //     while(cur3 != cur2->end){
    //         printOneInterCode(fp, cur3->begin);
    //         cur3 = cur3->next;
    //     }
    //     printOneInterCode(fp, cur3->begin);
    //     fprintf(fp, "\n");
    //     cur2 = cur2->next;
    // }
    // printf("\n");
    // printf("\n");
    printMips32Head(fp);
    generateMips32(fp);
}

void printMips32Head(FILE* fp){
    fprintf(fp, ".data\n");
    fprintf(fp, "_prompt: .asciiz \"Enter an integer:\"\n");
    fprintf(fp, "_ret: .asciiz \"\\n\"\n");
    fprintf(fp, ".globl main\n");
    fprintf(fp, ".text\n");
    fprintf(fp, "read:\n");
    fprintf(fp, "  li $v0, 4\n");
    fprintf(fp, "  la $a0, _prompt\n");
    fprintf(fp, "  syscall\n");
    fprintf(fp, "  li $v0, 5\n");
    fprintf(fp, "  syscall\n");
    fprintf(fp, "  jr $ra\n");
    fprintf(fp, "\n");
    fprintf(fp, "write:\n");
    fprintf(fp, "  li $v0, 1\n");
    fprintf(fp, "  syscall\n");
    fprintf(fp, "  li $v0, 4\n");
    fprintf(fp, "  la $a0, _ret\n");
    fprintf(fp, "  syscall\n");
    fprintf(fp, "  move $v0, $0\n");
    fprintf(fp, "  jr $ra\n");
    fprintf(fp, "\n");
}

void blocking(){
    
    int lineNo = 0;
    
    InterCode cur = inter_code_head->next;
    FunctionBlock curFunctionBlock = NULL;
    BasicBlock curBasicBlock = NULL;
    while(cur != inter_code_head){
        if(cur->prev != inter_code_head && cur->kind != LABEL_INTERCODE && cur->kind != FUNCTION_INTERCODE){
            // enum InterCodeKind kind = cur->prev->kind;
            if(cur->prev->kind == GOTO || cur->prev->kind == JE || cur->prev->kind == JNE 
            || cur->prev->kind == JA || cur->prev->kind == JAE || cur->prev->kind == JB 
            || cur->prev->kind == JBE || cur->prev->kind == CALL || cur->prev->kind == RETURN){
                // 跳转指令的下一条指令
                BasicBlock basicBlock = newBasicBlock(cur);
                insertBasicBlock(basicBlock);
                curBasicBlock = basicBlock;
            }
        }
        switch(cur->kind){
            case FUNCTION_INTERCODE:{
                // 函数开始
                BasicBlock basicBlock = newBasicBlock(cur);
                insertBasicBlock(basicBlock);
                FunctionBlock functionBlock = newFunctionBlock(basicBlock);
                insertFunctionBlock(functionBlock);
                if(curFunctionBlock != NULL && curBasicBlock != NULL){
                    // 函数收尾
                    curFunctionBlock->end = curBasicBlock;
                }
                curFunctionBlock = functionBlock;
                curBasicBlock = basicBlock;
                lineNo = 0;
                break;
            }
            case LABEL_INTERCODE:{
                BasicBlock basicBlock = newBasicBlock(cur);
                insertBasicBlock(basicBlock);
                curBasicBlock = basicBlock;
                break;
            }
            case GOTO:{
                // 收尾
                curBasicBlock->end = cur;
                curBasicBlock->endLineNo = lineNo;
                break;
            }
            case JE:
            case JNE:
            case JA:
            case JAE:
            case JB:
            case JBE:{
                // 收尾
                curBasicBlock->end = cur;
                curBasicBlock->endLineNo = lineNo;
                // addToStack(curFunctionBlock, cur->op1, lineNo);
                // addToStack(curFunctionBlock, cur->op2, lineNo);
                break;
            }
            case RETURN:{
                // 函数和基本块收尾
                curBasicBlock->end = cur;
                curBasicBlock->endLineNo = lineNo;
                addToStack(curFunctionBlock, cur->op1, lineNo);
                // curFunctionBlock->end = curBasicBlock;
                break;
            }
            case ASSIGN:{
                addToStack(curFunctionBlock, cur->op1, lineNo);
                addToStack(curFunctionBlock, cur->result, lineNo);
                break;
            }
            case PLUS:
            case MINUS:
            case STAR:
            case DIV:{
                addToStack(curFunctionBlock, cur->op1, lineNo);
                addToStack(curFunctionBlock, cur->op2, lineNo);
                addToStack(curFunctionBlock, cur->result, lineNo);
                break;
            }
            case DEC:{
                int decSize = cur->op2->u.const_value;
                curFunctionBlock->totalSize += (decSize - 4);
                addToStack(curFunctionBlock, cur->op1, lineNo);
                break;
            }
            case CALL:{
                addToStack(curFunctionBlock, cur->op1, lineNo);
                addToStack(curFunctionBlock, cur->result, lineNo);
                // 函数和基本块收尾
                curBasicBlock->end = cur;
                curBasicBlock->endLineNo = lineNo;
                break;
            }
            case PARAM:{
                addToStack(curFunctionBlock, cur->op1, lineNo);
                break;
            }
            case ARG:
            case READ:
            case WRITE:{
                addToStack(curFunctionBlock, cur->result, lineNo);
                break;
            }
        }
        if(cur->next != inter_code_head && (cur->next->kind == LABEL_INTERCODE || cur->next->kind == FUNCTION_INTERCODE)){
            // 基本块收尾
            curBasicBlock->end = cur;
            curBasicBlock->endLineNo = lineNo;
        }
        
        lineNo++;
        cur = cur->next;
    }
    if(curFunctionBlock != NULL && curBasicBlock != NULL){
        // 函数收尾
        curFunctionBlock->end = curBasicBlock;
    }
    
    // LocalVariable temp1 = curFunctionBlock->varList->next;
    // while(temp1)
    // {
    //     LineNo temp2 = temp1->useList->next;
    //     while(temp2)
    //     {
    //         printf("%d  ", temp2->num);
    //         temp2 = temp2->next;
    //     }
    //     printf("\n");
    //     temp1 = temp1->next;
    // }
}

int getReg(FILE* fp, Operand operand, FunctionBlock functionBlock, BasicBlock basicBlock, int lineNo){
    if(operand == NULL){
        // 直接申请一个寄存器
        for(int i = 8; i < 26; ++i){
            if(isFree(i)){
                // 有空寄存器
                regDescriptor[i].isConst = 1;
                return i;
            }
        }
        // 无空寄存器
        int index = overrideReg(fp, lineNo, basicBlock->endLineNo);
        regDescriptor[index].isConst = 1;
        return index;
    }else if(operand->kind == CONSTANT){
        // 常数，放入寄存器
        for(int i = 8; i < 26; ++i){
            if(isFree(i)){
                // 有空寄存器
                regDescriptor[i].isConst = 1;
                printf("  li %s, %d\n", regName[i], operand->u.const_value);
                return i;
            }
        }
        // 无空寄存器
        int index = overrideReg(fp, lineNo, basicBlock->endLineNo);
        regDescriptor[index].isConst = 1;
        printf(" li %s, %d\n", regName[index], operand->u.const_value);
        return index;
    }else if(operand->kind != LABEL_OPERAND && operand->kind != FUNCTION_OPERAND){
        // printf("1\n");
        // t/v，存入寄存器
        // printf("kind = %d, ", operand->kind);
        // printOneOperand(fp, operand);
        // printf("\n");
        LocalVariable operandVariable = findLocalVariable(operand, functionBlock);
        // printf("2\n");
        if(operandVariable->regIndex != -1){
            // 已经在寄存器中
            // printf("3\n");
            return operandVariable->regIndex;
        }else{
            // printf("4\n");
            for(int i = 8; i < 26; ++i){
                if(isFree(i)){
                    // 有空寄存器
                    regDescriptor[i].varList->regNext = operandVariable;
                    operandVariable->regIndex = i;
                    printf("  lw %s, -%d($fp)\n", regName[i], operandVariable->offset);
                    return i;
                }
            }
            // 无空寄存器
            int index = overrideReg(fp, lineNo, basicBlock->endLineNo);
            regDescriptor[index].varList->regNext = operandVariable;
            operandVariable->regIndex = index;
            printf("  lw %s, -%d($fp)\n", regName[index], operandVariable->offset);
            return index;
        }
    }
}

int getRegForAllKind(FILE* fp, Operand operand, FunctionBlock functionBlock, BasicBlock basicBlock, int lineNo){
    if(operand == NULL){
        int index = getReg(fp, operand, functionBlock, basicBlock, lineNo);
        int x = getEmptyArrayIndex();
        indexArray[x] = index;
        return index;
    }else if(operand->kind == ADDRESS || operand->kind == TEMPORARY_ADDRESS){
        // printf("haha\n");
        int index1 = getReg(fp, operand, functionBlock, basicBlock, lineNo);
        // printf("hoho\n");
        int index2 = getReg(fp, NULL, functionBlock, basicBlock, lineNo);
        // printf("index1 = %d, index2 = %d\n", index1, index2);
        // t = *x
        printf("  lw %s, 0(%s)\n", regName[index2], regName[index1]);
        int x1 = getEmptyArrayIndex();
        indexArray[x1] = index1;
        int x2 = getEmptyArrayIndex();
        indexArray[x2] = index2;
        return index2;
    }else if(operand->kind == REFERENCE){
        // 为立即数申请
        int index1 = getReg(fp, NULL, functionBlock, basicBlock, lineNo);
        // 为临时变量申请
        int index2 = getReg(fp, NULL, functionBlock, basicBlock, lineNo);
        // t = &x
        printf("  addi %s, $fp, -%d\n", regName[index2], findLocalVariable(operand, functionBlock)->offset);
        int x1 = getEmptyArrayIndex();
        indexArray[x1] = index1;
        int x2 = getEmptyArrayIndex();
        indexArray[x2] = index2;
        return index2;
    }else{
        int index = getReg(fp, operand, functionBlock, basicBlock, lineNo);
        int x = getEmptyArrayIndex();
        indexArray[x] = index;
        return index;
    }
}

int overrideReg(FILE* fp, int curLineNo, int endLineNo){
    int indexMax = 8;
    int lineNoMax = -1;
    for(int i = 8; i < 26; ++i){
        int regDesMin = 0x7FFFFFFF;
        if(regDescriptor[i].isConst == 1)   continue;
        LocalVariable cur = regDescriptor[i].varList->regNext;
        while(cur != NULL){
            LineNo curLine = cur->useList->next;
            while(curLine != NULL){
                if(curLine->num > curLineNo && curLine->num <= endLineNo){
                    // 每个寄存器找最小的
                    regDesMin = (regDesMin>curLine->num)?curLine->num:regDesMin;
                    break;
                }
                curLine = curLine->next;
            }
            cur = cur->regNext;
        }
        if(lineNoMax < regDesMin){
            // 寄存器间找最大的
            lineNoMax = regDesMin;
            indexMax = i;
        }
    }
    LocalVariable cur1 = regDescriptor[lineNoMax].varList->regNext;
    while(cur1 != NULL){
        // 修改地址描述符
        cur1->regIndex = -1;
        if(cur1->inMemory == 0){
            // printf("  sw %s, -%d($fp)  in override\n", regName[lineNoMax], cur1->offset);
            printf("  sw %s, -%d($fp)\n", regName[lineNoMax], cur1->offset);
            cur1->inMemory = 1;
        }
        cur1 = cur1->regNext;
    }
    // 清空该寄存器
    regDescriptor[lineNoMax].isConst = 0;
    regDescriptor[lineNoMax].varList->regNext = NULL;
    return lineNoMax;
}

LocalVariable findLocalVariable(Operand operand, FunctionBlock functionBlock){
    LocalVariable cur = functionBlock->varList->next;
    while(cur != NULL){
        // printOneOperand(NULL, cur->operand);
        // printf("  kind = %d, ", cur->operand->kind);
        // printOneOperand(NULL, operand);
        // printf("\n");
        if(equalOperand(cur->operand, operand)){
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

int isFree(int index){
    if(regDescriptor[index].isConst == 0 && regDescriptor[index].varList->regNext == NULL)  return 1;
    return 0;
}

void saveAllRegs(FILE* fp){
    for(int i = 8; i < 26; ++i){
        LocalVariable cur = regDescriptor[i].varList->regNext;
        while(cur != NULL){
            cur->regIndex = -1;
            if(cur->inMemory == 0){
                // printf("  sw %s, -%d($fp)  in saveAllRegs\n", regName[i], cur->offset);
                printf("  sw %s, -%d($fp)\n", regName[i], cur->offset);
                cur->inMemory = 1;
            }
            cur = cur->regNext;
        }
        regDescriptor[i].varList->regNext = NULL;
        regDescriptor[i].isConst = 0;
    }
}

// b = a[1]
// t1 = &v1 + 4
// v2 = *t1

void generateMips32(FILE* fp){
    FunctionBlock curFunction = function_block_head->next;
    while(curFunction != NULL){
        int lineNo = 0;
        BasicBlock curBasic = curFunction->begin;
        while(curBasic != curFunction->end->next){
            InterCode curInterCode = curBasic->begin;
            while(curInterCode != curBasic->end->next){
                // printf("------\n");
                // printOneInterCode(fp, curInterCode);
                // printf("------\n");
                switch(curInterCode->kind){
                    case LABEL_INTERCODE:{
                        printf("label%d:\n", curInterCode->op1->u.num);
                        break;
                    }
                    case FUNCTION_INTERCODE:{
                        printf("%s:\n", curInterCode->op1->u.name);
                        printf("  addi $sp, $sp, -4\n");
                        // printf("  sw $fp, 0($sp)  in FUNCTION_INTERCODE\n");
                        printf("  sw $fp, 0($sp)\n");
                        printf("  move $fp, $sp\n");
                        printf("  addi $sp, $sp, -%d\n", curFunction->totalSize - 4);
                        break;
                    }
                    case ASSIGN:{
                        int index0 = -1;
                        int index1 = -1;
                        int index2 = -1;
                        
                        if((curInterCode->op1->kind == ADDRESS || curInterCode->op1->kind == TEMPORARY_ADDRESS)
                             && (curInterCode->result->kind == ADDRESS || curInterCode->result->kind == TEMPORARY_ADDRESS)){
                            // *x = *y
                            index0 = getReg(fp, curInterCode->result, curFunction, curBasic, lineNo);
                            index1 = getReg(fp, curInterCode->op1, curFunction, curBasic, lineNo);
                            index2 = getReg(fp, NULL, curFunction, curBasic, lineNo);
                            printf("  lw %s, 0(%s)\n", regName[index2], regName[index1]);
                            printf("  sw %s, 0(%s)\n", regName[index2], regName[index0]);
                            // printf("  sw %s, 0(%s)  in ASSIGN1\n", regName[index2], regName[index0]);
                        }else if(curInterCode->op1->kind == REFERENCE){
                            // x = &y
                            index0 = getReg(fp, curInterCode->result, curFunction, curBasic, lineNo);
                            index1 = getReg(fp, NULL, curFunction, curBasic, lineNo);
                            printf("  addi %s, $fp, -%d\n", regName[index0], findLocalVariable(curInterCode->op1, curFunction)->offset);
                            findLocalVariable(curInterCode->result, curFunction)->inMemory = 0;
                        }else if(curInterCode->result->kind == ADDRESS || curInterCode->result->kind == TEMPORARY_ADDRESS){
                            // *x = y
                            index0 = getReg(fp, curInterCode->result, curFunction, curBasic, lineNo);
                            index1 = getReg(fp, curInterCode->op1, curFunction, curBasic, lineNo);
                            // printf("  sw %s, 0(%s)  in ASSIGN2\n", regName[index1], regName[index0]);
                            printf("  sw %s, 0(%s)\n", regName[index1], regName[index0]);
                        }else if(curInterCode->op1->kind == ADDRESS || curInterCode->op1->kind == TEMPORARY_ADDRESS){
                            // x = *y
                            index0 = getReg(fp, curInterCode->result, curFunction, curBasic, lineNo);
                            index1 = getReg(fp, curInterCode->op1, curFunction, curBasic, lineNo);
                            printf("  lw %s, 0(%s)\n", regName[index0], regName[index1]);
                            findLocalVariable(curInterCode->result, curFunction)->inMemory = 0;
                        }else{
                            // x = y
                            // printf("kind = %d, resultKind = %d, op1Kind = %d, ", curInterCode->kind, curInterCode->result->kind, curInterCode->op1->kind);
                            // printf("op1->name = %s, op2->name = %s\n", curInterCode->result->u.variable.var_name, curInterCode->op1->u.variable.var_name);
                            if(curInterCode->op1->kind == CONSTANT){
                                index0 = getReg(fp, curInterCode->result, curFunction, curBasic, lineNo);
                                printf("  li %s, %d\n", regName[index0], curInterCode->op1->u.const_value);
                            }else{
                                index1 = getReg(fp, curInterCode->op1, curFunction, curBasic, lineNo);
                                LocalVariable result = findLocalVariable(curInterCode->result, curFunction);
                                if(result->regIndex == -1){
                                    // x不在寄存器中
                                    result->regIndex = index1;
                                    result->regNext = regDescriptor[index1].varList->regNext;
                                    regDescriptor[index1].varList->regNext = result;
                                }else if(result->regIndex != index1){
                                    indexArray[3] = result->regIndex;
                                    // x在其他寄存器中
                                    freeVariable(result->regIndex, result);
                                    result->regIndex = index1;
                                    result->regNext = regDescriptor[index1].varList->regNext;
                                    regDescriptor[index1].varList->regNext = result;
                                }else{
                                    // x就在该寄存器中
                                }
                            }
                            findLocalVariable(curInterCode->result, curFunction)->inMemory = 0;
                        }
                        indexArray[0] = index0;
                        indexArray[1] = index1;
                        indexArray[2] = index2;
                        break;
                    }
                    case PLUS:{
                        int index0 = getRegForAllKind(fp, curInterCode->result, curFunction, curBasic, lineNo);
                        int index1 = getRegForAllKind(fp, curInterCode->op1, curFunction, curBasic, lineNo);
                        int index2 = getRegForAllKind(fp, curInterCode->op2, curFunction, curBasic, lineNo);
                        if(curInterCode->op1->kind == CONSTANT){
                            printf("  addi %s, %s, %d\n", regName[index0], regName[index2], 
                                                           curInterCode->op1->u.const_value);
                        }else if(curInterCode->op2->kind == CONSTANT){
                            printf("  addi %s, %s, %d\n", regName[index0], regName[index1],
                                                           curInterCode->op2->u.const_value);
                        }else{
                            printf("  add %s, %s, %s\n", regName[index0], regName[index1], 
                                                           regName[index2]);
                        }
                        findLocalVariable(curInterCode->result, curFunction)->inMemory = 0;
                        break;
                    }
                    case MINUS:{
                        int index0 = getRegForAllKind(fp, curInterCode->result, curFunction, curBasic, lineNo);
                        int index1 = getRegForAllKind(fp, curInterCode->op1, curFunction, curBasic, lineNo);
                        int index2 = getRegForAllKind(fp, curInterCode->op2, curFunction, curBasic, lineNo);
                        if(curInterCode->op2->kind == CONSTANT){
                            printf("  addi %s, %s, %d\n", regName[index0], regName[index1],
                                                           -curInterCode->op2->u.const_value);
                        }else{
                            printf("  sub %s, %s, %s\n", regName[index0], regName[index1], 
                                                           regName[index2]);
                        }
                        findLocalVariable(curInterCode->result, curFunction)->inMemory = 0;
                        break;
                    }
                    case STAR:{
                        int index0 = getRegForAllKind(fp, curInterCode->result, curFunction, curBasic, lineNo);
                        int index1 = getRegForAllKind(fp, curInterCode->op1, curFunction, curBasic, lineNo);
                        int index2 = getRegForAllKind(fp, curInterCode->op2, curFunction, curBasic, lineNo);
                        printf("  mul %s, %s, %s\n", regName[index0], regName[index1], 
                                                           regName[index2]);
                        findLocalVariable(curInterCode->result, curFunction)->inMemory = 0;
                        break;
                    }
                    case DIV:{
                        int index0 = getRegForAllKind(fp, curInterCode->result, curFunction, curBasic, lineNo);
                        int index1 = getRegForAllKind(fp, curInterCode->op1, curFunction, curBasic, lineNo);
                        int index2 = getRegForAllKind(fp, curInterCode->op2, curFunction, curBasic, lineNo);
                        printf("  div %s, %s\n", regName[index1], regName[index2]);
                        printf("  mflo %s\n", regName[index0]);
                        findLocalVariable(curInterCode->result, curFunction)->inMemory = 0;
                        break;
                    }
                    case GOTO:{
                        printf("  j label%d\n", curInterCode->result->u.num);
                        break;
                    }
                    case JE:{
                        int index1 = getRegForAllKind(fp, curInterCode->op1, curFunction, curBasic, lineNo);
                        int index2 = getRegForAllKind(fp, curInterCode->op2, curFunction, curBasic, lineNo);
                        printf("  beq %s, %s, label%d\n", regName[index1], regName[index2],
                                                           curInterCode->result->u.num);
                        break;
                    }
                    case JNE:{
                        int index1 = getRegForAllKind(fp, curInterCode->op1, curFunction, curBasic, lineNo);
                        int index2 = getRegForAllKind(fp, curInterCode->op2, curFunction, curBasic, lineNo);
                        printf("  bne %s, %s, label%d\n", regName[index1], regName[index2],
                                                           curInterCode->result->u.num);
                        break;
                    }
                    case JA:{
                        int index1 = getRegForAllKind(fp, curInterCode->op1, curFunction, curBasic, lineNo);
                        int index2 = getRegForAllKind(fp, curInterCode->op2, curFunction, curBasic, lineNo);
                        printf("  bgt %s, %s, label%d\n", regName[index1], regName[index2],
                                                           curInterCode->result->u.num);
                        break;
                    }
                    case JAE:{
                        int index1 = getRegForAllKind(fp, curInterCode->op1, curFunction, curBasic, lineNo);
                        int index2 = getRegForAllKind(fp, curInterCode->op2, curFunction, curBasic, lineNo);
                        printf("  bge %s, %s, label%d\n", regName[index1], regName[index2],
                                                           curInterCode->result->u.num);
                        break;
                    }
                    case JB:{
                        int index1 = getRegForAllKind(fp, curInterCode->op1, curFunction, curBasic, lineNo);
                        int index2 = getRegForAllKind(fp, curInterCode->op2, curFunction, curBasic, lineNo);
                        printf("  blt %s, %s, label%d\n", regName[index1], regName[index2],
                                                           curInterCode->result->u.num);
                        break;
                    }
                    case JBE:{
                        int index1 = getRegForAllKind(fp, curInterCode->op1, curFunction, curBasic, lineNo);
                        int index2 = getRegForAllKind(fp, curInterCode->op2, curFunction, curBasic, lineNo);
                        printf("  ble %s, %s, label%d\n", regName[index1], regName[index2],
                                                           curInterCode->result->u.num);
                        break;
                    }
                    case RETURN:{
                        int index = getRegForAllKind(fp, curInterCode->op1, curFunction, curBasic, lineNo);
                        printf("  move $v0, %s\n", regName[index]);
                        printf("  move $sp, $fp\n");
                        printf("  lw $fp, 0($sp)\n");
                        printf("  addi $sp, $sp, 4\n");
                        printf("  jr $ra\n");
                        // printf("in return\n");
                        break;
                    }
                    case DEC:{
                        break;
                    }
                    case ARG:{
                        // indexArray[0] = findLocalVariable(curInterCode->result, curFunction)->regIndex;
                        break;
                    }
                    case CALL:{
                        InterCode cur = curInterCode->prev;
                        int x = 12;
                        while(cur->kind == ARG){
                            // printf("======\n");
                            // printOneInterCode(fp, cur);
                            // printf("%d\n", findLocalVariable(cur->result, curFunction)->inMemory);
                            // printf("======\n");
                            int index1 = getRegForAllKind(fp, cur->result, curFunction, curBasic, lineNo);
                            // printf("  sw %s, -%d($sp)  in CALL1\n", regName[index1], x);
                            printf("  sw %s, -%d($sp)\n", regName[index1], x);
                            x = x + 4;
                            freeRegs(fp, lineNo, curBasic);
                            cur = cur->prev;
                        }
                        printf("  addi $sp, $sp, -4\n");
                        // printf("  sw $ra, 0($sp)  in CALL2\n");
                        printf("  sw $ra, 0($sp)\n");
                        printf("  jal %s\n", curInterCode->op1->u.name);
                        printf("  lw $ra, 0($sp)\n");
                        printf("  addi $sp, $sp, 4\n");
                        int resultIndex = getRegForAllKind(fp, curInterCode->result, curFunction, curBasic, lineNo);
                        printf("  move %s, $v0\n", regName[resultIndex]);
                        findLocalVariable(curInterCode->result, curFunction)->inMemory = 0;
                        break;
                    }
                    case PARAM:{
                        break;
                    }
                    case READ:{
                        printf("  addi $sp, $sp, -4\n");
                        // printf("  sw $ra, 0($sp)  in READ1\n");
                        printf("  sw $ra, 0($sp)\n");
                        printf("  jal read\n");
                        printf("  lw $ra, 0($sp)\n");
                        printf("  addi $sp, $sp, 4\n");
                        int resultIndex = getRegForAllKind(fp, curInterCode->result, curFunction, curBasic, lineNo);
                        printf("  move %s, $v0\n", regName[resultIndex]);
                        findLocalVariable(curInterCode->result, curFunction)->inMemory = 0;
                        break;
                    }
                    case WRITE:{
                        int paramIndex = getRegForAllKind(fp, curInterCode->result, curFunction, curBasic, lineNo);
                        printf("  move $a0, %s\n", regName[paramIndex]);
                        printf("  addi $sp, $sp, -4\n");
                        // printf("  sw $ra, 0($sp)  in READ2\n");
                        printf("  sw $ra, 0($sp)\n");
                        printf("  jal write\n");
                        printf("  lw $ra, 0($sp)\n");
                        printf("  addi $sp, $sp, 4\n");
                        break;
                    }
                    default: break;
                }
                freeRegs(fp, lineNo, curBasic);
                curInterCode = curInterCode->next;
                lineNo++;
            }
            // 每个BasicBlock末尾写会内存
            saveAllRegs(fp);
            curBasic = curBasic->next;
        }
        curFunction = curFunction->next;
    }
}

void freeRegs(FILE* fp, int lineNo, BasicBlock curBasic){
    // Free reg
    for(int i = 0; i < 5; ++i){
        if(indexArray[i] != -1){
            if(regDescriptor[indexArray[i]].isConst == 1){
                // 常数可直接删去
                regDescriptor[indexArray[i]].isConst = 0;
                regDescriptor[indexArray[i]].varList->regNext = NULL;
            }else{
                LocalVariable cur = regDescriptor[indexArray[i]].varList->regNext;
                int willBeUsed = 0;
                while(cur != NULL){
                    LineNo curLineNo = cur->useList->next;
                    while(curLineNo !=  NULL){
                        if(curLineNo->num > lineNo && curLineNo->num <= curBasic->endLineNo){
                            // 每个寄存器找最小的
                            willBeUsed = 1;
                            break;
                        }
                        curLineNo = curLineNo->next;
                    }
                    if(willBeUsed == 1) break;
                    cur = cur->regNext;
                }
                if(willBeUsed == 0){
                    // 后续不会被使用，溢出到栈
                    cur = regDescriptor[indexArray[i]].varList->regNext;
                    while(cur != NULL){
                        cur->regIndex = -1;
                        if(cur->inMemory == 0){
                            // printf("  sw %s, -%d($fp)  in freeRegs\n", regName[indexArray[i]], cur->offset);
                            printf("  sw %s, -%d($fp)\n", regName[indexArray[i]], cur->offset);
                            cur->inMemory = 1;
                        }
                        cur = cur->regNext;
                    }
                    regDescriptor[indexArray[i]].varList->regNext = NULL;
                    regDescriptor[indexArray[i]].isConst = 0;
                }
            }
        }
        indexArray[i] = -1;
    }
}

void freeVariable(int index, LocalVariable localVariable){
    // 将liveVariable从regDescriptor[index]中删除
    LocalVariable cur = regDescriptor[index].varList->regNext;
    LocalVariable pre = regDescriptor[index].varList;
    while(cur != NULL){
        if(equalOperand(cur->operand, localVariable->operand) == 1){
            pre->regNext = cur->regNext;
            cur->regNext = NULL;
            break;
        }
        pre = cur;
        cur = cur->regNext;
    }
    localVariable->regIndex = -1;
}

void printOneInterCode(FILE* fp, InterCode cur){
    switch(cur->kind){
        case LABEL_INTERCODE:{
            printf("LABEL ");
            printOneOperand(fp, cur->op1);
            printf(" :");
            break;
        }
        case FUNCTION_INTERCODE:{
            printf("FUNCTION ");
            printOneOperand(fp, cur->op1);
            printf(" :");
            break;
        }
        case ASSIGN:{
            printOneOperand(fp, cur->result);
            printf(" := ");
            printOneOperand(fp, cur->op1);
            break;
        }
        case PLUS:{
            printOneOperand(fp, cur->result);
            printf(" := ");
            printOneOperand(fp, cur->op1);
            printf(" + ");
            printOneOperand(fp, cur->op2);
            break;
        }
        case MINUS:{
            printOneOperand(fp, cur->result);
            printf(" := ");
            printOneOperand(fp, cur->op1);
            printf(" - ");
            printOneOperand(fp, cur->op2);
            break;
        }
        case STAR:{
            printOneOperand(fp, cur->result);
            printf(" := ");
            printOneOperand(fp, cur->op1);
            printf(" * ");
            printOneOperand(fp, cur->op2);
            break;
        }
        case DIV:{
            printOneOperand(fp, cur->result);
            printf(" := ");
            printOneOperand(fp, cur->op1);
            printf(" / ");
            printOneOperand(fp, cur->op2);
            break;
        }
        case ADDR:{
            break;
        }
        case LEFT_REF:{
            break;
        }
        case RIGHT_REF:{
            break;
        }
        case GOTO:{
            printf("GOTO ");
            printOneOperand(fp, cur->result);
            break;
        }
        case JE:{
            printf("IF ");
            printOneOperand(fp, cur->op1);
            printf(" == ");
            printOneOperand(fp, cur->op2);
            printf(" GOTO ");
            printOneOperand(fp, cur->result);
            break;
        }
        case JNE:{
            printf("IF ");
            printOneOperand(fp, cur->op1);
            printf(" != ");
            printOneOperand(fp, cur->op2);
            printf(" GOTO ");
            printOneOperand(fp, cur->result);
            break;
        }
        case JA:{
            printf("IF ");
            printOneOperand(fp, cur->op1);
            printf(" > ");
            printOneOperand(fp, cur->op2);
            printf(" GOTO ");
            printOneOperand(fp, cur->result);
            break;
        }
        case JAE:{
            printf("IF ");
            printOneOperand(fp, cur->op1);
            printf(" >= ");
            printOneOperand(fp, cur->op2);
            printf(" GOTO ");
            printOneOperand(fp, cur->result);
            break;
        }
        case JB:{
            printf("IF ");
            printOneOperand(fp, cur->op1);
            printf(" < ");
            printOneOperand(fp, cur->op2);
            printf(" GOTO ");
            printOneOperand(fp, cur->result);
            break;
        }
        case JBE:{
            printf("IF ");
            printOneOperand(fp, cur->op1);
            printf(" <= ");
            printOneOperand(fp, cur->op2);
            printf(" GOTO ");
            printOneOperand(fp, cur->result);
            break;
        }
        case RETURN:{
            printf("RETURN ");
            printOneOperand(fp, cur->op1);
            break;
        }
        case DEC:{
            printf("DEC ");
            printOneOperand(fp, cur->op1);
            printf(" %d", cur->op2->u.const_value);
            break;
        }
        case ARG:{
            printf("ARG ");
            printOneOperand(fp, cur->result);
            break;
        }
        case CALL:{
            printOneOperand(fp, cur->result);
            printf(" := CALL ");
            printOneOperand(fp, cur->op1);
            break;
        }
        case PARAM:{
            printf("PARAM ");
            printOneOperand(fp, cur->op1);
            break;
        }
        case READ:{
            printf("READ ");
            printOneOperand(fp, cur->result);
            break;
        }
        case WRITE:{
            printf("WRITE ");
            printOneOperand(fp, cur->result);
            break;
        }
        default: break;
    }
    printf("\n");
}

void printOneOperand(FILE* fp, Operand operand){
    if(operand == NULL) return;
    switch(operand->kind){
        case VARIABLE:{
            printf("v%d", operand->u.variable.var_num);
            break;
        }
        case CONSTANT:{
            printf("#%d", operand->u.const_value);
            break;
        }
        case ADDRESS:{
            printf("*v%d", operand->u.variable.var_num);
            break;
        }
        case REFERENCE:{
            printf("&v%d", operand->u.variable.var_num);
            break;
        }
        case LABEL_OPERAND:{
            printf("label%d", operand->u.num);
            break;
        }
        case FUNCTION_OPERAND:{
            printf("%s", operand->u.name);
            break;
        }
        case TEMPORARY_VARIABLE:{
            printf("t%d", operand->u.num);
            break;
        }
        case TEMPORARY_ADDRESS:{
            printf("*t%d", operand->u.num);
            break;
        }
        case STRUCTURE_ARRAY:
        case STRUCTURE_STRUCTURE:{
            printf("t%d", operand->u.variable.var_num);
            break;
        }
        default: break;
    }
}

#endif
