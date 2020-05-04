#include "ir.h"

int getTypeSize(Type type){
    // 基本类型，４字节
    if(type->kind == BASIC) return 4;
    // 结构体
    if(type->kind == STRUCTURE){
        int typeSize = 0;
        FieldList cur = type->u.structure.fieldList;
        while(cur != NULL){
            typeSize = typeSize + getTypeSize(cur->type);
            cur = cur->tail;
        }
        return typeSize;
    }else if(type->kind == ARRAY){
        int elemSize = getTypeSize(type->u.array.elem);
        return type->u.array.size * elemSize;
    }
    return 0;
}


void initIr(){
    var_num = 1;
    temp_var_num = 1;
    label_num = 1;
    IRERROR = 0;

    inter_code_head = (InterCode)malloc(sizeof(struct InterCode_t));
    inter_code_head->next = inter_code_head->prev = inter_code_head;
    inter_code_tail = inter_code_head;

    operand_head = (Operand)malloc(sizeof(struct Operand_t));
    operand_head->next = NULL;
    operand_tail = operand_head;


}

Operand newOperand(enum OperandKind kind, int num, char* name){
    Operand result = (Operand)malloc(sizeof(struct Operand_t));
    result->kind = kind;
    result->next = NULL;
    switch (kind){
        case VARIABLE:{
            // 一般变量
            result->u.variable.var_num = num;
            result->u.variable.var_name = getStr(name);
            break;
        }
        case CONSTANT:{
            // 常量
            result->u.const_value = num;
        }
        case ADDRESS:
        case FUNCTION_OPERAND:{
            // 变量地址
            result->u.name = getStr(name);
            break;
        }
        case LABEL_OPERAND:
        case TEMPORARY_VARIABLE:{
            // 临时变量，标号
            result->u.num = num;
            break;
        }
        default:{
            break;
        }
    }
    return result;
}

InterCode newInterCode(enum InterCodeKind kind, Operand op1, Operand op2, Operand result){
    InterCode temp = (InterCode)malloc(sizeof(struct InterCode_t));
    temp->kind = kind;
    temp->next = temp->prev = NULL;
    temp->op1 = op1;
    temp->op2 = op2;
    temp->result = result;
    return temp;
}

void insertInterCode(InterCode intercode){
    intercode->next = inter_code_tail->next;
    intercode->prev = inter_code_tail;
    inter_code_tail->next = intercode;
    inter_code_head->prev = intercode;
    inter_code_tail = inter_code_tail->next;
}

void insertOperand(Operand operand){
    operand->next = operand_tail->next;
    operand_tail->next = operand;
    operand_tail = operand_tail->next;
}

Operand findOperand(char* name){
    Operand cur = operand_head->next;
    while (cur != NULL){
        if(cur->kind == VARIABLE && strcmp(cur->u.variable.var_name, name) == 0){
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

void IRProgram(treeNode* root){
#ifdef print_lab_3
    printf("IRProgram\n");
#endif
    if(root == NULL)    return;
    initIr();
    IRExtDefList(root->firstChild);
}

void IRExtDefList(treeNode* parent){
#ifdef print_lab_3
    printf("IRExtDefList\n");
#endif
    if(parent == NULL || parent->firstChild == NULL)    return;
    // ExtDefList: ExtDef ExtDefList
    IRExtDef(parent->firstChild);
    IRExtDefList(parent->firstChild->nextBrother);
}

void IRExtDef(treeNode* parent){
#ifdef print_lab_3
    printf("IRExtDef\n");
#endif
    if(parent == NULL)    return;
    if(strcmp(parent->firstChild->nextBrother->name, "FunDec") == 0){
        // ExtDef: Specifier FunDec CompSt
        IRFunDec(parent->firstChild->nextBrother);
        IRCompSt(parent->firstChild->nextBrother->nextBrother);
    }
}

void IRFunDec(treeNode* parent){
#ifdef print_lab_3
    printf("IRFunDec\n");
#endif
    if(parent == NULL)  return;
    Operand funcOperand = newOperand(FUNCTION_OPERAND, 0, parent->firstChild->name);
    InterCode funcInterCode = newInterCode(FUNCTION_INTERCODE, funcOperand, NULL, NULL);
    if(parent->firstChild->nextBrother->nextBrother->nextBrother != NULL){
        // FunDec: ID LP VarList RP
        IRVarList(parent->firstChild->nextBrother->nextBrother);
    }
}

void IRVarList(treeNode* parent){
#ifdef print_lab_3
    printf("IRVarList\n");
#endif
    if(parent->firstChild->nextBrother == NULL){
        // VarList: ParamDec
        IRParamDec(parent->firstChild);
    }else{
        // VarList: ParamDec COMMA VarList
        IRParamDec(parent->firstChild);
        IRVarList(parent->firstChild->nextBrother->nextBrother);
    }
}

void IRParamDec(treeNode* parent){
#ifdef print_lab_3
    printf("IRParamDec\n");
#endif
    if(parent != NULL && parent->firstChild != NULL){
        IRFunctionVarDec(parent->firstChild->nextBrother);
    }
}

void IRFunctionVarDec(treeNode* parent){
#ifdef print_lab_3
    printf("IRFunctionVarDec\n");
#endif
    treeNode* cur = parent->firstChild;
    char* name = NULL;
    while(cur){
        if(strcmp(cur->name, "ID") == 0){
            name = getStr(cur->text);
            break;
        }
        /*VarDec is array*/
        cur = cur->firstChild;
    }
    Type type = getIDType(cur->text);
    if(type == NULL)    return;
    if(type->kind == ARRAY){
        // 函数参数为数组
        IRERROR = 1;
        return;
    }
    Operand varOperand = newOperand(VARIABLE, var_num++, cur->text);
    insertOperand(varOperand);
    InterCode varInterCode = newInterCode(PARAM, varOperand, NULL, NULL);
    insertInterCode(varInterCode);
}

void IRCompSt(treeNode* parent){
#ifdef print_lab_3
    printf("IRCompSt\n");
#endif
    if(parent == NULL)  return;
    // CompSt: LC DefList StmtList RC
    if(strcmp(parent->firstChild->nextBrother->name, "DefList") == 0){
        IRDefList(parent->firstChild->nextBrother);
        if(strcmp(parent->firstChild->nextBrother->nextBrother->name, "StmtList") == 0){
            IRStmtList(parent->firstChild->nextBrother->nextBrother); 
        }
    }else if(strcmp(parent->firstChild->nextBrother->name, "StmtList") == 0){
        IRStmtList(parent->firstChild->nextBrother);
    }
}

void IRDefList(treeNode* parent){
#ifdef print_lab_3
    printf("IRDefList\n");
#endif
    if(parent == NULL)  return;
    // DefList: Def DefList
    IRDef(parent->firstChild);
    IRDefList(parent->firstChild->nextBrother);
}

void IRStmtList(treeNode* parent){
#ifdef print_lab_3
    printf("IRStmtList\n");
#endif
    if(parent == NULL || parent->firstChild == NULL)  return;
    // StmtList: Stmt StmtList
    IRStmt(parent->firstChild);
    IRStmtList(parent->firstChild->nextBrother);
}

void IRDef(treeNode* parent){
#ifdef print_lab_3
    printf("IRDef\n");
#endif
    // Def: Specifier DecList SEMI
    if(parent == NULL || parent->firstChild == NULL)  return;
    IRDecList(parent->firstChild->nextBrother);
}

void IRDecList(treeNode* parent){
#ifdef print_lab_3
    printf("IRDecList\n");
#endif
    if(parent == NULL)  return;
    if(parent->firstChild->nextBrother == NULL){
        // DecList: Dec
        IRDec(parent->firstChild);
    }else{
        // DecList: Dec COMMA DecList
        IRDec(parent->firstChild);
        IRDecList(parent->firstChild->nextBrother->nextBrother);
    }
}

void IRDec(treeNode* parent){
#ifdef print_lab_3
    printf("IRDec\n");
#endif
    if(parent->firstChild->nextBrother == NULL){
        // Dec: VarDec
        IRVarDec(parent->firstChild);
    }else{
        // Dec: VarDec ASSIGNOP Exp
        Operand left = IRVarDec(parent->firstChild);
        Operand right = IRExp(parent->firstChild->nextBrother->nextBrother);
        InterCode decInterCode = newInterCode(ASSIGN, right, NULL, left);
        insertInterCode(decInterCode);
    }
}

Operand IRVarDec(treeNode* parent){
#ifdef print_lab_3
    printf("IRVarDec\n");
#endif
    if(strcmp(parent->firstChild->name, "ID") == 0){
        // VarDec: ID
        Operand varOperand = newOperand(VARIABLE, var_num++, parent->firstChild->text);
        insertOperand(varOperand);
        return varOperand;
    }
    // VarDec: VarDec LB INT RB
    treeNode* cur = parent->firstChild;
    char* name = NULL;
    while(cur){
        if(strcmp(cur->name, "ID") == 0){
            name = getStr(cur->text);
            break;
        }
        /*VarDec is array*/
        cur = cur->firstChild;
    }
    Type type = getIDType(name);
    if(type == NULL)    return;
    if(type->kind == ARRAY && type->u.array.elem->kind == ARRAY){
        // 多维数组
        IRERROR = 1;
        return;
    }
    int size = getTypeSize(type);
    Operand varOperand1 = newOperand(VARIABLE, var_num++, name);
    insertOperand(varOperand1);
    Operand varOperand2 = newOperand(CONSTANT, size, NULL);
    InterCode varInterCode = newInterCode(DEC, varOperand1, varOperand2, NULL);
    insertInterCode(varInterCode);
    return varOperand1;
}

Operand IRExp(treeNode* parent){
#ifdef print_lab_3
    printf("IRExp\n");
#endif
    if(strcmp(parent->firstChild->name, "ID") == 0 && parent->firstChild->nextBrother == NULL){
        // Exp: ID
        Operand idOperand = findOperand(parent->firstChild->text);
        return idOperand;
    }else if(strcmp(parent->firstChild->name, "INT") == 0){
        // Exp: INT
        Operand intOperand = newOperand(CONSTANT, atoi(parent->firstChild->text), NULL);
        return intOperand;
    }else if(strcmp(parent->firstChild->name, "FLOAT") == 0){
        // TODO:???
        return NULL;
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
        return IRExp(parent->firstChild->nextBrother);
    }else{
        // Exp: ID LP (Args) RP
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

void IRStmt(treeNode* parent){
#ifdef print_lab_3
    printf("IRStmt\n");
#endif
    if(parent == NULL)  return;
    if(strcmp(parent->firstChild->name, "Exp") == 0){
        // Stmt: Exp SEMI
        IRExp(parent->firstChild);
    }else if(strcmp(parent->firstChild->name, "CompSt") == 0){
        // Stmt: CompSt
        IRCompSt(parent->firstChild);
    }else if(strcmp(parent->firstChild->name, "RETURN") == 0){
        // Stmt: RETURN Exp SEMI
        Operand returnOperand = IRExp(parent->firstChild->nextBrother);
        InterCode returnInterCode = newInterCode(RETURN, returnOperand, NULL, NULL);
        insertInterCode(returnInterCode);
    }else if(strcmp(parent->firstChild->name, "IF") == 0){
        Operand label1 = newOperand(LABEL_OPERAND, label_num++, NULL);
        Operand label2 = newOperand(LABEL_OPERAND, label_num++, NULL);
        InterCode labelCode1 = newInterCode(LABEL_INTERCODE, label1, NULL, NULL);
        InterCode labelCode2 = newInterCode(LABEL_INTERCODE, label2, NULL, NULL);
        IRCond(parent->firstChild->nextBrother->nextBrother, label1, label2);
        insertInterCode(labelCode1);
        IRStmt(parent->firstChild->nextBrother->nextBrother->nextBrother->nextBrother);
        // Stmt: IF
        if(parent->firstChild->nextBrother->nextBrother->nextBrother->nextBrother->nextBrother == NULL){
            // Stmt: IF LP Exp RP Stmt1
            // code1 [LABEL label1] code2 [LABEL label2]
            insertInterCode(labelCode2);
        }else{
            // Stmt: IF LP Exp RP Stmt ELSE Stmt
            // code1 [LABEL label1] code2 [GOTO label3] [LABEL label2] code3 [LABEL label3]
            Operand label3 = newOperand(LABEL_OPERAND, label_num++, NULL);
            InterCode labelCode3 = newInterCode(LABEL_INTERCODE, label3, NULL, NULL);
            InterCode gotoCode3 = newInterCode(GOTO, NULL, NULL, label3);
            insertInterCode(gotoCode3);
            insertInterCode(labelCode2);
            IRStmt(parent->firstChild->nextBrother->nextBrother->nextBrother->nextBrother->nextBrother->nextBrother);
            insertInterCode(labelCode3);
        }
    }else if(strcmp(parent->firstChild->name, "WHILE") == 0){
        // WHILE LP Exp RP Stmt1
        // [LABEL label1] code1 [LABEL label2] code2 [GOTO label1] [LABEL label3]
        Operand label1 = newOperand(LABEL_OPERAND, label_num++, NULL);
        Operand label2 = newOperand(LABEL_OPERAND, label_num++, NULL);
        Operand label3 = newOperand(LABEL_OPERAND, label_num++, NULL);
        InterCode labelCode1 = newInterCode(LABEL_INTERCODE, label1, NULL, NULL);
        InterCode labelCode2 = newInterCode(LABEL_INTERCODE, label2, NULL, NULL);
        InterCode labelCode3 = newInterCode(LABEL_INTERCODE, label3, NULL, NULL);
        InterCode gotoCode1 = newInterCode(GOTO, NULL, NULL, label1);
        insertInterCode(labelCode1);
        IRCond(parent->firstChild->nextBrother->nextBrother, label2, label3);
        insertInterCode(labelCode2);
        IRStmt(parent->firstChild->nextBrother->nextBrother->nextBrother->nextBrother);
        insertInterCode(gotoCode1);
        insertInterCode(labelCode3);
    }
}

void IRCond(treeNode* parent, Operand label_true, Operand label_false){
#ifdef print_lab_3
    printf("IRCond\n");
#endif
    if(strcmp(parent->firstChild->name, "NOT") == 0){
        // Exp: NOT Exp1
        IRCond(parent->firstChild->nextBrother, label_false, label_true);
    }else if(strcmp(parent->firstChild->name, "Exp") == 0 && strcmp(parent->firstChild->nextBrother->name, "AND") == 0){
        // Exp: Exp1 AND Exp2
        // code1 [LABEL labe1] code2
        Operand label1 = newOperand(LABEL_OPERAND, label_num++, NULL);
        InterCode labelCode1 = newInterCode(LABEL_INTERCODE, label1, NULL, NULL);
        IRCond(parent->firstChild, label1, label_false);
        insertInterCode(labelCode1);
        IRCond(parent->firstChild->nextBrother->nextBrother, label_true, label_false);
    }else if(strcmp(parent->firstChild->name, "Exp") == 0 && strcmp(parent->firstChild->nextBrother->name, "OR") == 0){
        // Exp: Exp1 OR Exp2
        // code1 [LABEL labe1] code2
        Operand label1 = newOperand(LABEL_OPERAND, label_num++, NULL);
        InterCode labelCode1 = newInterCode(LABEL_INTERCODE, label1, NULL, NULL);
        IRCond(parent->firstChild, label_true, label1);
        insertInterCode(labelCode1);
        IRCond(parent->firstChild->nextBrother->nextBrother, label_true, label_false);
    }else if(strcmp(parent->firstChild->name, "Exp") == 0 && strcmp(parent->firstChild->nextBrother->name, "RELOP") == 0){
        // Exp: Exp1 RELOP Exp2
        // code1 code2 code3 [GOTO label_false]
        Operand leftOperand = IRExp(parent->firstChild);
        Operand rightOperand = IRExp(parent->firstChild->nextBrother->nextBrother);
        InterCode relopInterCode = NULL;
        if(strcmp(parent->firstChild->nextBrother->text, ">") == 0){
            relopInterCode = newInterCode(JA, leftOperand, rightOperand, label_true);
        }else if(strcmp(parent->firstChild->nextBrother->text, ">=") == 0){
            relopInterCode = newInterCode(JAE, leftOperand, rightOperand, label_true);
        }else if(strcmp(parent->firstChild->nextBrother->text, "<") == 0){
            relopInterCode = newInterCode(JB, leftOperand, rightOperand, label_true);
        }else if(strcmp(parent->firstChild->nextBrother->text, "<=") == 0){
            relopInterCode = newInterCode(JBE, leftOperand, rightOperand, label_true);
        }else if(strcmp(parent->firstChild->nextBrother->text, "==") == 0){
            relopInterCode = newInterCode(JE, leftOperand, rightOperand, label_true);
        }else if(strcmp(parent->firstChild->nextBrother->text, "!=") == 0){
            relopInterCode = newInterCode(JNE, leftOperand, rightOperand, label_true);
        }
        insertInterCode(relopInterCode);
        InterCode gotoLabelFalse = newInterCode(GOTO, NULL, NULL, label_false);
        insertInterCode(gotoLabelFalse);
    }else{
        // Others
        // code1 code2 [GOTO label_false]
        Operand expOperand = IRExp(parent);
        Operand zeroOperand = newOperand(CONSTANT, 0, NULL);
        InterCode notEqualInterCode = newInterCode(JNE, expOperand, zeroOperand, label_true);
        InterCode gotoLabelFalse = newInterCode(GOTO, NULL, NULL, label_false);
        insertInterCode(notEqualInterCode);
        insertInterCode(gotoLabelFalse);
    }
}
