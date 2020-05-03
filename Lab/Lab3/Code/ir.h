#ifndef __IR_H__
#define __IR_H__

typedef Operand_t* Operand;
typedef InterCode_t* InterCode;

struct Operand_t{
    enum { VARIABLE, CONSTANT, ADDRESS, LABEL, FUNCTION, TEMPORARY_VARIABLE } kind;
    union{
        // 一般变量
        struct{
            int var_num;
            char* var_name;
        }var;
        // 临时变量，Label
        int num;
        // 常量
        int value;
        // 函数
        char* name;
    }u;
    Operand next;
};

struct InterCode_t{
    enum { ASSIGN, ADD, SUB, MUL, DIV, ADDR, LEFT_REF, RIGHT_REF, GOTO, IF_GOTO, RETURN, DEC, ARG, CALL, PARAM, READ, WRITE } kind;
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

#endif