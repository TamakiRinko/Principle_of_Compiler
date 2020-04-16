#include "hashtable.h"

Symbol symbolTable[TABLE_NUM];

Symbol newSymbol(char* name, Type type, int lineno){
    Symbol symbol = (Symbol)malloc(sizeof(struct Symbol_));
    symbol->name = (char*)malloc(strlen(name) + 1);
    strcpy(symbol->name, name);
    symbol->type = type;
    symbol->lineno = lineno;
    return symbol;
}

// 获得一个字符串
char* getStr(char* str){
    char* str1 = (char*)malloc(strlen(str) + 1);
    strcpy(str1, str);
    return str1;
}

// 获得结构体变量类型
Type getStructureType(char* name){
    unsigned int hashCode = hash_pjw(name);
    Symbol cur = symbolTable[hashCode];
    while (cur != NULL){
        if(strcmp(cur->name, name) == 0){
            Type variableType = (Type)malloc(sizeof(struct Type_));
            variableType->kind = STRUCTURE;
            variableType->u.structure.fieldList = cur->type->u.structure.fieldList;
            variableType->u.structure.name = getStr(cur->type->u.structure.name);
            return variableType;
        }
        cur = cur->next;
    }
    return NULL;
}

// 获得匿名名称
char* getAnonymousName(){
    char* name = (char* )malloc(32);
    memset(name, '\0', 32);
    itoa(structureId, name, 10);
    structureId++;
    return name;
}

unsigned int hash_pjw(char* name){
    unsigned int val = 0, i;
    for (; *name; ++name){
        val = (val << 2) + *name;
        if (i = val & ~0x3fff) val = (val ^ (i >> 12)) & TABLE_NUM;
    }
    return val;
}

int isEqual(Type t1, Type t2){
    if(t1->kind != t2->kind){
        return 0;
    }
    switch(t1->kind){
        case BASIC:{
            return t1->u.basic == t2->u.basic;
        }
        case ARRAY:{
            return (t1->u.array.size == t2->u.array.size && isEqual(t1->u.array.elem, t2->u.array.elem));
        }
        case STRUCTURE:{
            return (strcmp(t1->u.structure.name, t2->u.structure.name) == 0);
        }
        case FUNCTION:{
            // 返回值
            if(!isEqual(t1->u.function->returnType, t2->u.function->returnType)){
                return 0;
            }
            // 参数列表
            FieldList cur1 = t1->u.function->paramType;
            FieldList cur2 = t2->u.function->paramType;
            while(cur1 != NULL && cur2 != NULL){
                if(!isEqual(cur1->type, cur2->type)){
                    return 0;
                }
                cur1 = cur1->tail;
                cur2 = cur2->tail;
            }
            if(cur1 != NULL || cur2 != NULL){               // 参数数目不相同
                return 0;
            }
            return 1;
        }
        default:{
            return 0;
        }
    }
}

void initSymbolTable(){
    for(int i = 0; i < TABLE_NUM; ++i){
        symbolTable[i] = NULL;
    }
}

int insertSymbolTable(Symbol symbol){
    unsigned int hashCode = hash_pjw(symbol->name);
    if(symbolTable[hashCode] == NULL){
        symbolTable[hashCode] = symbol;
    }else{
        Symbol cur = symbolTable[hashCode];
        while (cur != NULL){
            if(strcmp(cur->name, symbol->name) == 0){           // 重名错误
                if(cur->type->kind == FUNCTION && symbol->type->kind == FUNCTION){
                    if(!isEqual(cur->type, symbol->type)){                                                          // 类型不同
                        serror("Inconsistent declaration of function", symbol->lineno, 19);
                        return 1;
                    }else if(cur->type->u.function->isDefined == 0 && symbol->type->u.function->isDefined == 1){    // 先声明后定义
                        cur->type->u.function->isDefined = 1;
                        return 0;
                    }else if(cur->type->u.function->isDefined == 1 && symbol->type->u.function->isDefined == 1){    // 两次定义
                        serror("Function redefined", symbol->lineno, 4);
                        return 1;
                    }
                }else if(symbol->type->kind == STRUCTURETYPE && cur->type->kind != FUNCTION){
                    serror("Structure redefined", symbol->lineno, 16);
                    return 1;
                }else if(symbol->type->kind != FUNCTION && symbol->type->kind != STRUCTURETYPE && cur->type->kind != FUNCTION){
                    // serror("Variable redefined", symbol->lineno, 3);
                    // return 1;
                    return 3;
                }
                return 0;
            }
            cur = cur->next;
        }
        symbol->next = symbolTable[hashCode];
        symbolTable[hashCode] = symbol;
    }
    return 0;
}

void serror(char* msg, int line, int errorType){
    printf("Error type %d at Line %d: %s.\n", errorType, line, msg);
}

void checkDef(){
    for(int i = 0; i < TABLE_NUM; ++i){
        Symbol cur = symbolTable[i];
        while (cur != NULL){
            if(cur->type->kind == FUNCTION && cur->type->u.function->isDefined == 0){
                serror("Undefined function", cur->lineno, 18);
            }
            cur = cur->next;
        }
    }
}

void program(treeNode* root){
    if(root->firstChild != NULL){
        extDefList(root->firstChild);
        checkDef();
    }
}

void extDefList(treeNode* parent){
    if(parent == NULL || parent->firstChild == NULL)    return;
    // ExtDefList: ExtDef ExtDefList
    extDef(parent->firstChild);
    extDefList(parent->firstChild->nextBrother);
}

void extDef(treeNode* parent){
    if(parent == NULL)    return;
    Type type = specifier(parent->firstChild);
    if(strcmp(parent->firstChild->nextBrother->name, "SEMI") == 0){
        // ExtDef: Specifier SEMI
    }else if(strcmp(parent->firstChild->nextBrother->name, "ExtDecList") == 0){
        // ExtDef: Specifier ExtDecList SEMI
        extDecList(parent->firstChild->nextBrother, type);
    }else if(strcmp(parent->firstChild->nextBrother->nextBrother->name, "SEMI") == 0){
        // ExtDef: Specifier FunDec SEMI
        funDec(parent->firstChild->nextBrother, type, 0);
    }else{
        // ExtDef: Specifier FunDec CompSt
        funDec(parent->firstChild->nextBrother, type, 1);
        compSt(parent->firstChild->nextBrother->nextBrother, type);
    }
}

Type specifier(treeNode* parent){
    if(parent == NULL)  return;
    if(strcmp(parent->firstChild->name, "TYPE") == 0){
        // Specifier: TYPE
        Type type = (Type)malloc(sizeof(struct Type_));
        type->kind = BASIC;
        if(strcmp(parent->firstChild->text, "INT") == 0){
            type->u.basic = INT;
        }else{
            type->u.basic = FLOAT;
        }
        return type;
    }else{
        // Specifier: StructSpecifier
        return structSpecifier(parent->firstChild);
    }
}

void extDecList(treeNode* parent, Type type){
    if(parent == NULL)  return;
    if(parent->firstChild->nextBrother == NULL){
        // ExtDecList: VarDec
        varDec(parent->firstChild, type);
    }else{
        // ExtDecList: VarDec COMMA ExtDecList
        varDec(parent->firstChild, type);
        extDecList(parent->firstChild->nextBrother->nextBrother, type);
    }
}

void funDec(treeNode* parent, Type returnType, int isDef){
    if(parent == NULL)  return;
    Type funcType = (Type)malloc(sizeof(struct Type_));
    funcType->kind = FUNCTION;
    funcType->u.function = (Function)malloc(sizeof(struct Function_));
    funcType->u.function->isDefined = isDef;
    funcType->u.function->returnType = returnType;
    funcType->u.function->paramNum = 0;
    funcType->u.function->paramType = NULL;

    Symbol func = newSymbol(parent->firstChild->text, funcType, parent->firstChild->lineno);
    if(parent->firstChild->nextBrother->nextBrother->nextBrother == NULL){
        // FunDec: ID LP RP
    }else{
        // FunDec: ID LP VarList RP
        funcType->u.function->paramType = varList(parent->firstChild->nextBrother->nextBrother);
        FieldList cur = funcType->u.function->paramType;
        while (cur != NULL){
            funcType->u.function->paramNum++;
            cur = cur->tail;
        }
    }
    insertSymbolTable(func);
}

void compSt(treeNode* parent, Type type){
    if(parent == NULL)  return;
    // CompSt: LC DefList StmtList RC
    if(strcmp(parent->firstChild->nextBrother->name, "DefList") == 0){
        defList(parent->firstChild->nextBrother);
        if(strcmp(parent->firstChild->nextBrother->nextBrother->name, "StmtList") == 0){
            stmtList(parent->firstChild->nextBrother->nextBrother, type); 
        }
    }else if(strcmp(parent->firstChild->nextBrother->name, "StmtList") == 0){
        stmtList(parent->firstChild->nextBrother, type);
    }
}

Type structSpecifier(treeNode* parent){

    Type structureType = (Type)malloc(sizeof(struct Type_));                        // 结构体类型表项
    structureType->kind = STRUCTURETYPE;
    structureType->u.structure.fieldList = NULL;

    Type variableType = (Type)malloc(sizeof(struct Type_));                         // 结构体变量表项
    variableType->kind = STRUCTURE;

    // Type variableType;

    if(strcmp(parent->firstChild->nextBrother->name, "OptTag") == 0){
        // StructSpecifier: STRUCT OptTag LC DefList RC
        structureType->u.structure.name = getStr(parent->firstChild->nextBrother->firstChild->text);
        structureDefList(parent->firstChild->nextBrother->nextBrother->nextBrother, structureType);
        variableType->u = structureType->u;
    }else if(strcmp(parent->firstChild->nextBrother->name, "LC") == 0){
        // StructSpecifier: STRUCT LC DefList RC
        structureType->u.structure.name = getAnonymousName();
        structureDefList(parent->firstChild->nextBrother->nextBrother, structureType);
        variableType->u = structureType->u;
    }else{
        // StructureSpecifier: STRUCTURE Tag
        variableType = getStructureType(parent->firstChild->nextBrother->firstChild->text);
        if(variableType == NULL){
            serror("Undefined Structure", parent->firstChild->lineno, 17);
        }
        return variableType;
        // variableType->u.structure.fieldList = NULL;
        // return variableType;
    }
    Symbol structure = newSymbol(structureType->u.structure.name, structureType, parent->firstChild->lineno);
    insertSymbolTable(structure);
    return variableType;
}

void varDec(treeNode* parent, Type type){

}

FieldList varList(treeNode* parent){

}

void defList(treeNode* parent){
    if(parent == NULL)  return;
    // DefList: Def DefList
    def(parent->firstChild);
    defList(parent->firstChild->nextBrother);
}

void stmtList(treeNode* parent, Type type){

}

FieldList structureDefList(treeNode* parent, Type type){
    //TODO: 
    if(parent == NULL)  return;
    // DefList: Def DefList
    structureDef(parent->firstChild, type);
    structureDefList(parent->firstChild->nextBrother, type);
}

void def(treeNode* parent){
    // Def: Specifier DecList SEMI
    Type type = specifier(parent->firstChild);
    if(type == NULL)    return;
    decList(parent->firstChild->nextBrother, type);
}

void decList(treeNode* parent, Type type){

}

void structureDef(treeNode* parent, Type type){
    // Def: Specifier DecList SEMI
    Type specifierType = specifier(parent->firstChild);
    if(specifierType == NULL)    return;
    structureDecList(parent->firstChild->nextBrother, specifierType, type);
}

void structureDecList(treeNode* parent, Type specifierType, Type structureType){
    if(parent->firstChild->nextBrother == NULL){
        // DecList: Dec
        structureDec(parent->firstChild, specifierType, structureType);
    }else{
        // DecList: Dec COMMA DecList
        structureDec(parent->firstChild, specifierType, structureType);
        structureDecList(parent->firstChild->nextBrother->nextBrother, specifierType, structureType);
    }
}

void structureDec(treeNode* parent, Type specifierType, Type structureType){
    if(parent->firstChild->nextBrother == NULL){
        // Dec: VarDec
        structureVarDec(parent->firstChild, specifierType, structureType);
    }else{
        // Dec: VarDec ASSIGNOP Exp
        serror("Initialization during definition", parent->lineno, 15);
        structureVarDec(parent->firstChild, specifierType, structureType);
    }
}

void structureVarDec(treeNode* parent, Type specifierType, Type structureType){
    // if(parent->firstChild->nextBrother == NULL){
    //     // VarDec: ID
    //     Symbol symbol = newSymbol(parent->firstChild->text, specifierType, parent->firstChild->lineno);
    //     FieldList fieldList = (FieldList)malloc(sizeof(struct FieldList_));
    //     fieldList->name = getStr(parent->firstChild->text);
    //     fieldList->type = specifierType;
    //     int flag = 0;
    //     FieldList cur = structureType->u.structure.fieldList;
    //     while (cur != NULL){
    //         if(strcmp(cur->name, fieldList->name) == 0){
    //             serror("Variable redefined in structure", symbol->lineno, 15);
    //             flag = 1;
    //         }
    //         cur = cur->tail;
    //     }
    //     // Insert into fieldList
    //     fieldList->tail = structureType->u.structure.fieldList;
    //     structureType->u.structure.fieldList = fieldList;
    //     // Insert into symbolTable
    //     if(!flag){
    //         insertSymbolTable(symbol);
    //     }
    // }else{
    //     // VarDec: VarDec LB INT RB
    //     Type arrayType = (Type)malloc(sizeof(struct Type_));
    //     arrayType->kind = ARRAY;
    //     arrayType->u.array.size = atoi()
    // }

    FieldList fieldList = (FieldList)malloc(sizeof(struct FieldList_));
    fieldList->type = specifierType;
    treeNode* cur = parent->firstChild;
    while(cur){
        if(!strcmp(cur->name, "ID")){
            fieldList->name = cur->text;
            break;
        }
        /*VarDec is array*/
        Type arrayType = (Type)malloc(sizeof(struct Type_));
        arrayType->kind = ARRAY;
        arrayType->u.array.size = atoi(cur->nextBrother->nextBrother->text);
        arrayType->u.array.elem = fieldList->type;
        fieldList->type = arrayType;
        cur = cur->firstChild;
    }
    Symbol symbol = newSymbol(fieldList->name, fieldList->type, parent->firstChild->lineno);
    int flag = 0;
    FieldList current = structureType->u.structure.fieldList;
    while (current != NULL){
        if(strcmp(current->name, fieldList->name) == 0){
            serror("Variable redefined in structure", symbol->lineno, 15);
            flag = 1;
        }
        current = current->tail;
    }
    // Insert into fieldList
    fieldList->tail = structureType->u.structure.fieldList;
    structureType->u.structure.fieldList = fieldList;
    if(!flag){
        insertSymbolTable(symbol);
    }
}
