#include <stdio.h>
#include <string.h>
#include "treeNode.h"
#define TABLE_NUM 1024

typedef struct Type_* Type;
typedef struct FieldList_* FieldList;
typedef struct Function_* Function;
typedef struct Symbol_* Symbol;

enum Kind { BASIC, ARRAY, STRUCTURE, FUNCTION, STRUCTURETYPE };

int isEqual(Type t1, Type t2);                                      // 比较Type是否相等

int structureId = 1;

struct Type_{
    enum Kind kind;
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
};

struct FieldList_{
    char* name;             // 域的名字
    Type type;              // 域的类型
    FieldList tail;         // 下一个域
};

struct Function_{
    Type returnType;        //　返回值类型
    FieldList paramType;    //　参数类型
    int paramNum;           //　参数数量
    int isDefined;          //  是否被定义过
};

struct Symbol_{
    char* name;             // 变量名称
    Type type;              // 类型
    int lineno;             // 行数
    Symbol next;            // 指向下一个节点的指针
};

Symbol newSymbol(char* name, Type type, int lineno);
char* getStr(char* str);
Type getStructureType(char* name);

void initSymbolTable();
int insertSymbolTable(Symbol symbol);
void serror(char* msg, int line, int errorType);

void checkDef();

void program(treeNode* root);
void extDefList(treeNode* parent);
void extDef(treeNode* parent);
Type specifier(treeNode* parent);
void extDecList(treeNode* parent, Type type);
void funDec(treeNode* parent, Type returnType, int isDef);
void compSt(treeNode* parent, Type type);
Type structSpecifier(treeNode* parent);
void varDec(treeNode* parent, Type type);
void varList(treeNode* parent, Type functionType);
void defList(treeNode* parent);
void stmtList(treeNode* parent, Type type);
FieldList structureDefList(treeNode* parent, Type type);                     // 结构体内部定义
void def(treeNode* parent);
void decList(treeNode* parent, Type type);
void structureDef(treeNode* parent, Type type);
void structureDecList(treeNode* parent, Type specifierType, Type structureType);
void structureDec(treeNode* parent, Type specifierType, Type structureType);
void structureVarDec(treeNode* parent, Type specifierType, Type structureType);
void paramDec(treeNode* parent, Type functionType);
void dec(treeNode* parent, Type specifierType);
Type exp(treeNode* parent);
void stmt(treeNode* parent, Type type);
