#include "hashtable.h"

Symbol newSymbol(char* name, Type type, int lineno){
#ifdef print_lab_2
    printf("newSymbol\n");
#endif
    Symbol symbol = (Symbol)malloc(sizeof(struct Symbol_));
    symbol->name = (char*)malloc(strlen(name) + 1);
    strcpy(symbol->name, name);
    symbol->type = type;
    symbol->lineno = lineno;
    symbol->next = NULL;
    return symbol;
}

// 获得一个字符串
char* getStr(char* str){
#ifdef print_lab_2
    printf("getStr\n");
#endif
    char* str1 = (char*)malloc(strlen(str) + 1);
    strcpy(str1, str);
    return str1;
}

// 获得结构体变量类型
Type getStructureType(char* name){
#ifdef print_lab_2
    printf("getStructureType\n");
#endif
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

Type getIDType(char* name){
#ifdef print_lab_2
    printf("getIDType\n");
#endif
    // printf("name = %s\n", name);
    unsigned int hashCode = hash_pjw(name);
    Symbol cur = symbolTable[hashCode];
    while (cur != NULL){
        // printf("cur->name = %s\n", cur->name);
        if(strcmp(cur->name, name) == 0 && cur->type->kind != STRUCTURETYPE && cur->type->kind != FUNCTION){
            return cur->type;
        }
        cur = cur->next;
    }
    return NULL;
}

Type getFuncType(char* name){
#ifdef print_lab_2
    printf("getFuncType\n");
#endif
    unsigned int hashCode = hash_pjw(name);
    Symbol cur = symbolTable[hashCode];
    while (cur != NULL){
        if(strcmp(cur->name, name) == 0 && cur->type->kind != STRUCTURETYPE){
            return cur->type;
        }
        cur = cur->next;
    }
    return NULL;
}

int isRightValue(treeNode* parent){
#ifdef print_lab_2
    printf("isRightValue\n");
#endif
    if(strcmp(parent->firstChild->name, "ID") == 0 && parent->firstChild->nextBrother == NULL){
        // Exp: ID
        return 0;
    }else if(strcmp(parent->firstChild->name, "LP") == 0){
        // Exp: LP Exp RP
        return isRightValue(parent->firstChild->nextBrother);
    }else if(strcmp(parent->firstChild->name, "Exp") == 0 && strcmp(parent->firstChild->nextBrother->name, "DOT") == 0){
        // Exp: Exp DOT ID
        return 0;
    }else if(strcmp(parent->firstChild->name, "Exp") == 0 && strcmp(parent->firstChild->nextBrother->name, "LB") == 0){
        // Exp: Exp LB Exp RB
        return 0;
    }
    return 1;
}

// 获得匿名名称
char* getAnonymousName(){
#ifdef print_lab_2
    printf("getAnonymousName\n");
#endif
    char* name = (char* )malloc(32);
    memset(name, '\0', 32);
    // itoa(structureId, name, 10);
    sprintf(name, "%d", structureId);
    structureId++;
    return name;
}

unsigned int hash_pjw(char* name){
#ifdef print_lab_2
    printf("hash_pjw\n");
#endif
    unsigned int val = 0, i;
    for (; *name; ++name){
        val = (val << 2) + *name;
        if (i = val & ~TABLE_NUM) val = (val ^ (i >> 12)) & TABLE_NUM;
    }
    return val;
}

int isEqual(Type t1, Type t2){
#ifdef print_lab_2
    printf("isEqual\n");
#endif
    if(t1 == NULL || t2 == NULL){
        return 0;
    }
    if(t1->kind != t2->kind){
        return 0;
    }
    switch(t1->kind){
        case BASIC:{
            // printf("t1->u.basic = %d, t2->u.basic = %d\n", t1->u.basic, t2->u.basic);
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
#ifdef print_lab_2
    printf("initSymbolTable\n");
#endif
    for(int i = 0; i < TABLE_NUM; ++i){
        symbolTable[i] = NULL;
    }

    Type readReturnType = (Type)malloc(sizeof(struct Type_));
    readReturnType->kind = BASIC;
    readReturnType->u.basic = INT;
    Function readFunction = (Function)malloc(sizeof(struct Function_));
    Type readType = (Type)malloc(sizeof(struct Type_));
    readType->kind = FUNCTION;
    readType->u.function = readFunction;
    readType->u.function->isDefined = 1;
    readType->u.function->paramNum = 0;
    readType->u.function->paramType = NULL;
    readType->u.function->returnType = readReturnType;
    Symbol readSymbol = newSymbol("read", readType, 0);
    insertSymbolTable(readSymbol);

    Type writeReturnType = (Type)malloc(sizeof(struct Type_));
    writeReturnType->kind = BASIC;
    writeReturnType->u.basic = INT;
    Type writeParamType = (Type)malloc(sizeof(struct Type_));
    writeParamType->kind = BASIC;
    writeParamType->u.basic = INT;
    Function writeFunction = (Function)malloc(sizeof(struct Function_));
    FieldList writeFieldList = (FieldList)malloc(sizeof(struct FieldList_));
    writeFieldList->tail = NULL;
    writeFieldList->type = writeParamType;
    Type writeType = (Type)malloc(sizeof(struct Type_));
    writeType->kind = FUNCTION;
    writeType->u.function = writeFunction;
    writeType->u.function->isDefined = 1;
    writeType->u.function->paramNum = 1;
    writeType->u.function->paramType = writeFieldList;
    writeType->u.function->returnType = writeReturnType;
    Symbol writeSymbol = newSymbol("write", writeType, 0);
    insertSymbolTable(writeSymbol);

}

int insertSymbolTable(Symbol symbol){
#ifdef print_lab_2
    printf("insertSymbolTable\n");
#endif
#ifdef print_lab_2
    printf("line = %d, name = %s\n", symbol->lineno, symbol->name);
#endif
    unsigned int hashCode = hash_pjw(symbol->name);
#ifdef print_lab_2
    printf("hashcode = %d\n", hashCode);
#endif
    if(symbolTable[hashCode] == NULL){
        symbolTable[hashCode] = symbol;
    }else{
        Symbol cur = symbolTable[hashCode];
        while (cur != NULL){
            if(strcmp(cur->name, symbol->name) == 0){           // 重名错误
                if(cur->type->kind == FUNCTION && symbol->type->kind == FUNCTION){
                    if(cur->type->u.function->isDefined == 1 && symbol->type->u.function->isDefined == 1){          // 两次定义
                        serror("Function redefined", symbol->lineno, 4);
                        return 1;
                    }else if(isEqual(cur->type, symbol->type) == 0){                                                // 类型不同
                        serror("Inconsistent declaration of function", symbol->lineno, 19);
                        return 1;
                    }else if(cur->type->u.function->isDefined == 0 && symbol->type->u.function->isDefined == 1){    // 先声明后定义
                        cur->type->u.function->isDefined = 1;
                        return 0;
                    }
                }else if(symbol->type->kind == STRUCTURETYPE && cur->type->kind != FUNCTION){
                    serror("Structure redefined", symbol->lineno, 16);
                    return 1;
                }else if(symbol->type->kind != FUNCTION && symbol->type->kind != STRUCTURETYPE && cur->type->kind != FUNCTION){
                    serror("Variable redefined", symbol->lineno, 3);
                    return 1;
                    // return 3;
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
#ifdef print_lab_2
    printf("checkDef\n");
#endif
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
    // printf("%d\n", structureId);
#ifdef print_lab_2
    printf("program\n");
#endif
    structureId = 1;
    initSymbolTable();
    if(root->firstChild != NULL){
        extDefList(root->firstChild);
        checkDef();
    }
}

void extDefList(treeNode* parent){
#ifdef print_lab_2
    printf("extDefList\n");
#endif
    if(parent == NULL || parent->firstChild == NULL)    return;
    // ExtDefList: ExtDef ExtDefList
    extDef(parent->firstChild);
    extDefList(parent->firstChild->nextBrother);
}

void extDef(treeNode* parent){
#ifdef print_lab_2
    printf("extDef\n");
#endif
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
#ifdef print_lab_2
    printf("specifier\n");
#endif
    if(parent == NULL)  return NULL;
    if(strcmp(parent->firstChild->name, "TYPE") == 0){
        // Specifier: TYPE
        Type type = (Type)malloc(sizeof(struct Type_));
        type->kind = BASIC;
        if(strcmp(parent->firstChild->text, "int") == 0){
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
#ifdef print_lab_2
    printf("extDecList\n");
#endif
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
#ifdef print_lab_2
    printf("funDec\n");
#endif
    if(parent == NULL)  return;
    Type funcType = (Type)malloc(sizeof(struct Type_));
    funcType->kind = FUNCTION;
    // funcType->u.function = (Function)malloc(sizeof(struct Function_));
    // funcType->u.function->isDefined = isDef;
    // funcType->u.function->returnType = returnType;
    // funcType->u.function->paramNum = 0;
    // funcType->u.function->paramType = NULL;

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
        varList(parent->firstChild->nextBrother->nextBrother, funcType);
        FieldList cur = funcType->u.function->paramType;
        while (cur != NULL){
            funcType->u.function->paramNum++;
            cur = cur->tail;
        }
    }
    insertSymbolTable(func);
}

void compSt(treeNode* parent, Type type){
#ifdef print_lab_2
    printf("compSt\n");
#endif
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
#ifdef print_lab_2
    printf("structSpecifier\n");
#endif
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
#ifdef print_lab_2
    printf("varDec\n");
#endif
    treeNode* cur = parent->firstChild;
    char* name = NULL;
    while(cur){
        if(strcmp(cur->name, "ID") == 0){
            name = getStr(cur->text);
            break;
        }
        /*VarDec is array*/
        Type arrayType = (Type)malloc(sizeof(struct Type_));
        arrayType->kind = ARRAY;
        arrayType->u.array.size = atoi(cur->nextBrother->nextBrother->text);
        arrayType->u.array.elem = type;
        type = arrayType;
        cur = cur->firstChild;
    }
    Symbol symbol = newSymbol(name, type, parent->firstChild->lineno);
    insertSymbolTable(symbol);
}

void varList(treeNode* parent, Type functionType){
#ifdef print_lab_2
    printf("varList\n");
#endif
    if(parent->firstChild->nextBrother == NULL){
        // VarList: ParamDec
        paramDec(parent->firstChild, functionType);
    }else{
        // VarList: ParamDec COMMA VarList
        paramDec(parent->firstChild, functionType);
        varList(parent->firstChild->nextBrother->nextBrother, functionType);
    }
}

void defList(treeNode* parent){
#ifdef print_lab_2
    printf("defList\n");
#endif
    if(parent == NULL)  return;
    // DefList: Def DefList
    def(parent->firstChild);
    defList(parent->firstChild->nextBrother);
}

void stmtList(treeNode* parent, Type type){
#ifdef print_lab_2
    printf("stmtList\n");
#endif
    if(parent == NULL)  return;
    // StmtList: Stmt StmtList
    stmt(parent->firstChild, type);
    stmtList(parent->firstChild->nextBrother, type);
}

void structureDefList(treeNode* parent, Type type){
#ifdef print_lab_2
    printf("structureDefList\n");
#endif
    //TODO: 
    if(parent == NULL)  return;
    // DefList: Def DefList
    structureDef(parent->firstChild, type);
    if(parent->firstChild != NULL){
        structureDefList(parent->firstChild->nextBrother, type);
    }
}

void def(treeNode* parent){
#ifdef print_lab_2
    printf("def\n");
#endif
    // Def: Specifier DecList SEMI
    Type type = specifier(parent->firstChild);
    if(type == NULL)    return;
    decList(parent->firstChild->nextBrother, type);
}

void decList(treeNode* parent, Type type){
#ifdef print_lab_2
    printf("decList\n");
#endif
    if(parent->firstChild->nextBrother == NULL){
        // DecList: Dec
        dec(parent->firstChild, type);
    }else{
        // DecList: Dec COMMA DecList
        dec(parent->firstChild, type);
        decList(parent->firstChild->nextBrother->nextBrother, type);
    }
}

void structureDef(treeNode* parent, Type type){
#ifdef print_lab_2
    printf("structureDef\n");
#endif
    // Def: Specifier DecList SEMI
    if(parent == NULL)  return;
    Type specifierType = specifier(parent->firstChild);
    if(specifierType == NULL)    return;
    structureDecList(parent->firstChild->nextBrother, specifierType, type);
}

void structureDecList(treeNode* parent, Type specifierType, Type structureType){
#ifdef print_lab_2
    printf("structureDecList\n");
#endif
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
#ifdef print_lab_2
    printf("structureDec\n");
#endif
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
#ifdef print_lab_2
    printf("structureVarDec\n");
#endif
    FieldList fieldList = (FieldList)malloc(sizeof(struct FieldList_));
    fieldList->type = specifierType;
    treeNode* cur = parent->firstChild;
    while(cur != NULL){
        if(strcmp(cur->name, "ID") == 0){
            fieldList->name = getStr(cur->text);
#ifdef print_lab_2
            printf("cur->text = %s, ", cur->text);
#endif
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
#ifdef print_lab_2
    printf("fieldList->type->kind = %d\n", fieldList->type->kind);
#endif
    Symbol symbol = newSymbol(fieldList->name, fieldList->type, parent->firstChild->lineno);
    if(structureType->kind == STRUCTURETYPE){
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
        if(!flag){
            fieldList->tail = structureType->u.structure.fieldList;
            structureType->u.structure.fieldList = fieldList;
            insertSymbolTable(symbol);
        }
    }else if(structureType->kind == FUNCTION){
        // Insert into fieldList
        
        fieldList->tail = structureType->u.function->paramType;
        structureType->u.function->paramType = fieldList;
        if(structureType->u.function->isDefined == 1){
            insertSymbolTable(symbol);
        }
    }
    
}

void paramDec(treeNode* parent, Type functionType){
#ifdef print_lab_2
    printf("paramDec\n");
#endif
    Type specifierType = specifier(parent->firstChild);
    if(specifierType == NULL)   return;
    structureVarDec(parent->firstChild->nextBrother, specifierType, functionType);
}

void dec(treeNode* parent, Type specifierType){
#ifdef print_lab_2
    printf("dec\n");
#endif
    if(parent->firstChild->nextBrother == NULL){
        // Dec: VarDec
        varDec(parent->firstChild, specifierType);
    }else{
        // Dec: VarDec ASSIGNOP Exp
        varDec(parent->firstChild, specifierType);
        Type expType = Exp(parent->firstChild->nextBrother->nextBrother);
        if(expType == NULL) return;                 // int x = a + b
        if(isEqual(expType, specifierType) == 0){
            serror("Mismatch type between ASSIGNOP", parent->firstChild->lineno, 5);
        }
    }
}

Type Exp(treeNode* parent){
#ifdef print_lab_2
    printf("Exp\n");
#endif
    Type expType = (Type)malloc(sizeof(struct Type_));
    if(strcmp(parent->firstChild->name, "ID") == 0 && parent->firstChild->nextBrother == NULL){
        // Exp: ID
        // printf("text = %s\n", parent->firstChild->text);
        Type type = getIDType(parent->firstChild->text);
        if(type == NULL){
            serror("Variable used without definition", parent->lineno, 1);
        }
        return type;
    }else if(strcmp(parent->firstChild->name, "INT") == 0){
        // Exp: INT
        expType->kind = BASIC;
        expType->u.basic = INT;
        return expType;
    }else if(strcmp(parent->firstChild->name, "FLOAT") == 0){
        // Exp: FLOAT
        expType->kind = BASIC;
        expType->u.basic = FLOAT;
        return expType;
    }else if(strcmp(parent->firstChild->name, "Exp") == 0){
        if(strcmp(parent->firstChild->nextBrother->nextBrother->name, "Exp") == 0){
            Type type1 = Exp(parent->firstChild);
            Type type2 = Exp(parent->firstChild->nextBrother->nextBrother);
            if(type1 == NULL || type2 == NULL)  return NULL;
            if(strcmp(parent->firstChild->nextBrother->name, "LB") != 0){
                if(strcmp(parent->firstChild->nextBrother->name, "ASSIGNOP") == 0){
                    if(isRightValue(parent->firstChild)){
                        serror("Right value at right of assignment", parent->lineno, 6);
                        return NULL;
                    }
                    if(isEqual(type1, type2) == 0){
                        serror("Mismatch type between ASSIGNOP", parent->firstChild->lineno, 5);
                        return NULL;
                    }  
                    return type2;
                }
                // Exp: Exp operator Exp
                if(isEqual(type1, type2) == 0){
                    serror("Mismatch type between operator", parent->firstChild->lineno, 7);
                    return NULL;
                }else{
                    if(strcmp(parent->firstChild->nextBrother->name, "AND") == 0 || 
                        strcmp(parent->firstChild->nextBrother->name, "OR") == 0 || 
                        strcmp(parent->firstChild->nextBrother->name, "RELOP") == 0){
                        if(type2->kind != BASIC || (type2->kind == BASIC && type2->u.basic != INT)){
                            serror("Wrong type, need INT", parent->firstChild->lineno, 7);
                            return NULL;
                        }else if(type1->kind != BASIC || (type1->kind == BASIC && type1->u.basic != INT)){
                            serror("Wrong type, need INT", parent->firstChild->lineno, 7);
                            return NULL;
                        }
                        // 逻辑运算，类型为整形
                        return type1;
                    }else{
                        // 加减乘除，类型不变
                        if(type1->kind != BASIC || type2->kind != BASIC){
                            serror("Wrong type, need INT OR FLOAT", parent->firstChild->lineno, 7);
                            return NULL;
                        }
                        return type1;
                    }
                }
            }else{
                // Exp: Exp LB Exp RB
                if(type1->kind != ARRAY){
                    serror("NOT ARRAY Variable", parent->firstChild->lineno, 10);
                    return NULL;
                }else if(type2->kind != BASIC || (type2->kind == BASIC && type2->u.basic != INT)){
                    serror("NOT INT IN [...]", parent->firstChild->lineno, 12);
                    return NULL;
                }
                return type1->u.array.elem;
            }
        }else{
            // Exp: Exp DOT ID
            // printf("hola\n");
            Type type1 = Exp(parent->firstChild);
            if(type1 == NULL)   return NULL;
            if(type1->kind != STRUCTURE){
                serror("NOT STRUCTURE Variable", parent->firstChild->lineno, 13);
                return NULL;
            }else{
                FieldList fieldList = type1->u.structure.fieldList;
                while(fieldList != NULL){
                    if(strcmp(fieldList->name, parent->firstChild->nextBrother->nextBrother->text) == 0){
                        return fieldList->type;
                    }
                    fieldList = fieldList->tail;
                }
                serror("Undefined variable in STRUCTURE", parent->firstChild->nextBrother->nextBrother->lineno, 14);
                return NULL;
            }
        }
    }else if(strcmp(parent->firstChild->name, "MINUS") == 0){
        // Exp: MINUS Exp
        Type type = Exp(parent->firstChild->nextBrother);
        if(type == NULL)    return NULL;
        if(type->kind != BASIC){
            serror("Wrong type, need INT OR FLOAT", parent->firstChild->nextBrother->lineno, 7);
            return NULL;
        }
        return type;
    }else if(strcmp(parent->firstChild->name, "NOT") == 0){
        // Exp: NOT Exp
        Type type = Exp(parent->firstChild->nextBrother);
        if(type == NULL)    return NULL;
        if(type->kind != BASIC || (type->kind == BASIC && type->u.basic != INT)){
            serror("Wrong type, need INT", parent->firstChild->nextBrother->lineno, 7);
            return NULL;
        }
        return type;
    }else if(strcmp(parent->firstChild->name, "LP") == 0){
        // Exp: LP Exp RP
        return Exp(parent->firstChild->nextBrother);
    }else{
        // Exp: ID LP (Args) RP
        // printf("name = %s\n", parent->firstChild->text);
        Type type = getFuncType(parent->firstChild->text);
        if(type == NULL){
            serror("Undefined function used", parent->firstChild->lineno, 2);
            return NULL;
        }
        if(type->kind != FUNCTION){
            serror("Not FUNCTION variable", parent->firstChild->lineno, 11);
            return NULL;
        }
        if(strcmp(parent->firstChild->nextBrother->nextBrother->name, "Args") == 0){
            // 参数出错
            if(Args(parent->firstChild->nextBrother->nextBrother, type) == 0){
                return NULL;
            }
        }
        return type->u.function->returnType;
    }
}

void stmt(treeNode* parent, Type type){
#ifdef print_lab_2
    printf("stmt\n");
#endif
    if(strcmp(parent->firstChild->name, "Exp") == 0){
        // Stmt: Exp SEMI
        Exp(parent->firstChild);
    }else if(strcmp(parent->firstChild->name, "CompSt") == 0){
        // Stmt: CompSt
        compSt(parent->firstChild, type);
    }else if(strcmp(parent->firstChild->name, "RETURN") == 0){
        // Stmt: RETURN Exp SEMI
        Type expType = Exp(parent->firstChild->nextBrother);
        if(expType == NULL) return;
        if(isEqual(expType, type) == 0){
            serror("Mismatch Return type", parent->firstChild->lineno, 8);
        }
    }else{
        // Stmt: IF/WHILE
        Exp(parent->firstChild->nextBrother->nextBrother);
        stmt(parent->firstChild->nextBrother->nextBrother->nextBrother->nextBrother, type);
        // Stmt: IF LP Exp RP Stmt ELSE Stmt
        if(parent->firstChild->nextBrother->nextBrother->nextBrother->nextBrother->nextBrother != NULL){
            stmt(parent->firstChild->nextBrother->nextBrother->nextBrother->nextBrother->nextBrother->nextBrother, type);
        }
    }
}

int Args(treeNode* parent, Type type){
#ifdef print_lab_2
    printf("Args\n");
#endif
    FieldList fieldList1 = type->u.function->paramType;
    FieldList fieldList2 = NULL;

    treeNode* cur = parent->firstChild;
    while(cur != NULL){
        FieldList temp = (FieldList)malloc(sizeof(struct FieldList_));
        temp->type = Exp(cur);
        temp->tail = fieldList2;
        fieldList2 = temp;
        if(cur->nextBrother != NULL){
            // Args: Exp COMMA Args
            cur = cur->nextBrother->nextBrother->firstChild;
        }else{
            // Args: Exp
            break;
        }
    }
    FieldList cur1 = fieldList1;
    FieldList cur2 = fieldList2;
    while((cur1 != NULL) && (cur2 != NULL)){
        if(isEqual(cur1->type, cur2->type) == 0){
            serror("Mismatch type in Args", parent->lineno, 9);
            return 0;
        }
        cur1 = cur1->tail;
        cur2 = cur2->tail;
    }
    if(cur1 != NULL || cur2 != NULL){
        serror("Mismatch type in Args", parent->lineno, 9);
        return 0;
    }
    return 1;
}
