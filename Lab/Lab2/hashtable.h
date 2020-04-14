#include <stdio.h>
#include <string.h>
#include "treeNode.h"
#define TABLE_NUM 1024

typedef struct Type_* Type;
typedef struct FieldList_* FieldList;
typedef struct Function_* Function;
typedef struct Symbol_* Symbol;

enum Kind { BASIC, ARRAY, STRUCTURE, FUNCTION };

struct Type_{
    Kind kind;
    union{
        // 基本类型
        enum { INT, FLOAT } basic;
        // 数组类型信息包括元素类型与数组大小构成
        struct { Type elem; int size; } array;
        // 结构体类型信息是一个链表
        struct { char* name; FieldList fieldList; } structure;
        // 函数
        Function function;
    }u;
    bool isEqual(Type f){
        if(kind != f->kind){
            return false;
        }
        switch(kind){
            case BASIC:{
                return u.basic == f->u.basic;
            }
            case ARRAY:{
                return (u.array.size == f->u.array.size && u.array.elem->isEqual(f->u.array.elem));
            }
            case STRUCTURE:{
                return (strcmp(u.structure.name, f->u.structure.name) == 0);
            }
            case FUNCTION:{
                return u.function->isEqual(f->u.function);
            }
            default:{
                return false;
            }
        }
    }
};

struct FieldList_{
    char* name;             // 域的名字
    Type type;              // 域的类型
    FieldList tail;         // 下一个域
    // bool isEqual(FieldList f){
    //     if(type->){
            
    //     }
    // }
};

struct Function_{
    Type returnType;        //　返回值类型
    FieldList paramType;    //　参数类型
    int paramNum;           //　参数数量
    int isDefined;          //  是否被定义过
    bool isEqual(Function f){
        if(!returnType->isEqual(f->returnType)){
            return false;
        }
        FieldList cur1 = paramType;
        FieldList cur2 = f->paramType;
        while(cur1 != NULL && cur2 != NULL){
            if(!cur1->type->isEqual(cur2->type)){
                return false;
            }
            cur1 = cur1->tail;
            cur2 = cur2->tail;
        }
        if(cur1 != NULL || cur2 != NULL){               // 参数数目不相同
            return false;
        }
        return true;
    }
};

struct Symbol_{
    char* name;             // 变量名称
    Type type;              // 类型
    Symbol next;            // 指向下一个节点的指针
    Symbol_(char* Name, Type Type, Symbol Next){
        strcpy(name, Name);
        
    }
};

void initSymbolTable();
int insertSymbolTable(Symbol symbol);
void serror(char* msg, int line, int errorType);

void program(treeNode* root);
void extDefList(treeNode* root);
