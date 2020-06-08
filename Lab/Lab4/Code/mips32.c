#include "mips32.h"

void initBlock(){
    function_block_head = (FunctionBlock)malloc(sizeof(struct FunctionBlock_t));
    function_block_head->next = NULL;
    function_block_tail = function_block_head;

    basic_block_head = (BasicBlock)malloc(sizeof(struct BasicBlock_t));
    basic_block_head->next = NULL;
    basic_block_tail = basic_block_head;

    for(int i = 0; i < 32; ++i){
        regDescriptor[i].varList = (LocalVariable)malloc(sizeof(struct LocalVariable_t));
        regDescriptor[i].varList->regNext = NULL;
        regDescriptor[i].isConst = 0;
    }

}

LocalVariable newLocalVariable(Operand operand, int offset){
    LocalVariable result = (LocalVariable)malloc(sizeof(struct LocalVariable_t));
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
    result->totalSize = 0;
    result->end = NULL;
    result->next = NULL;
    return result;
}

BasicBlock newBasicBlock(InterCode begin){
    BasicBlock result = (BasicBlock)malloc(sizeof(struct BasicBlock_t));
    result->begin = begin;
    result->end = NULL;
    result->next = NULL;
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

void addToStack(FunctionBlock functionBlock, Operand operand){
    if(operand == NULL) return;
    enum OperandKind kind = operand->kind;
    if(kind != CONSTANT && kind != LABEL_OPERAND && kind != FUNCTION_OPERAND){
        LocalVariable cur = functionBlock->varList->next;
        while(cur != NULL){
            if(equalOperand(cur, operand)){
                break;
            }
            cur = cur->next;
        }
        if(cur == NULL){
            LocalVariable localVariable = newLocalVariable(operand, functionBlock->totalSize);
            insertLocalVariable(localVariable, functionBlock);
            functionBlock->totalSize += 4;
        }
    }
}

void translateToMisp32(char* output){
    FILE* fp = fopen(output, "w");
    initBlock();
    blocking();
}

void printMips32Head(FILE* fp){
    fprintf(fp, ".data\n");
    fprintf(fp, "_prompt: .asciiz \"Enter an integer:\"\n");
    fprintf(fp, "_ret: .asciiz \"\n\"\n");
    fprintf(fp, ".globl main\n");
    fprintf(fp, ".text\n");
    fprintf(fp, "read:\n");
    fprintf(fp, "\tli $v0, 4\n");
    fprintf(fp, "\tla $a0, _prompt\n");
    fprintf(fp, "\tsyscall\n");
    fprintf(fp, "\tli $v0, 5\n");
    fprintf(fp, "\tsyscall\n");
    fprintf(fp, "\tjr $ra\n");
    fprintf(fp, "\n");
    fprintf(fp, "write:\n");
    fprintf(fp, "\tli $v0, 1\n");
    fprintf(fp, "\tsyscall\n");
    fprintf(fp, "\tli $v0, 4\n");
    fprintf(fp, "\tla $a0, _ret\n");
    fprintf(fp, "\tsyscall\n");
    fprintf(fp, "\tmove $v0, $0\n");
    fprintf(fp, "\tjr $ra\n");
}

void blocking(){
    int offset = 0;
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
                break;
            }
            case RETURN:{
                // 函数和基本块收尾
                curBasicBlock->end = cur;
                curFunctionBlock->end = curBasicBlock;
                break;
            }
            case ASSIGN:{
                addToStack(curFunctionBlock, cur->op1);
                addToStack(curFunctionBlock, cur->result);
                break;
            }
            case PLUS:
            case MINUS:
            case STAR:
            case DIV:{
                addToStack(curFunctionBlock, cur->op1);
                addToStack(curFunctionBlock, cur->op2);
                addToStack(curFunctionBlock, cur->result);
                break;
            }
            case DEC:{
                int decSize = cur->op2->u.const_value;
                curFunctionBlock->totalSize += (decSize - 4);
                addToStack(curFunctionBlock, cur->op1);
                break;
            }
            case CALL:{
                addToStack(curFunctionBlock, cur->op1);
                addToStack(curFunctionBlock, cur->result);
                break;
            }
            case ARG:
            case READ:
            case WRITE:{
                addToStack(curFunctionBlock, cur->result);
                break;
            }
        }
        if(cur->next != inter_code_head && cur->next->kind == LABEL_INTERCODE){
            // 收尾
            curBasicBlock->end = cur;
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
    }
}

char* getReg(Operand operand, FunctionBlock functionBlock, FILE* fp){
    if(operand->kind == CONSTANT){
        // 常数，放入寄存器
        for(int i = 8; i < 26; ++i){
            if(isFree(i)){
                // 有空寄存器
                regDescriptor[i].isConst = 1;
                fprintf(fp," li $%s, %d\n", regName[i], operand->u.const_value);
                return regName[i];
            }
        }

    }else if(operand->kind == LABEL_OPERAND || operand->kind == FUNCTION_OPERAND){
        // t/v，存入寄存器
        LocalVariable operandVariable = findLocalVariable(operand, functionBlock);
        if(operandVariable->regIndex != -1){
            // 已经在寄存器中
            return regName[operandVariable->regIndex];
        }else{
            for(int i = 8; i < 26; ++i){
                if(isFree(i)){
                    // 有空寄存器
                    regDescriptor[i].varList->regNext = operandVariable;
                    operandVariable->regIndex = i;
                    fprintf(fp," lw $%s, -%d($fp)\n", regName[i], operandVariable->offset);
                    return regName[i];
                }
            }
        }
        
    }
    
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
