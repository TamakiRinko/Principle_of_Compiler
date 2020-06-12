#include "ir.h"

void printOperand(FILE* fp, Operand operand){
    if(operand == NULL) return;
    switch(operand->kind){
        case VARIABLE:{
            fprintf(fp, "v%d", operand->u.variable.var_num);
            break;
        }
        case CONSTANT:{
            fprintf(fp, "#%d", operand->u.const_value);
            break;
        }
        case ADDRESS:{
            fprintf(fp, "*v%d", operand->u.variable.var_num);
            break;
        }
        case REFERENCE:{
            fprintf(fp, "&v%d", operand->u.variable.var_num);
            break;
        }
        case LABEL_OPERAND:{
            fprintf(fp, "label%d", operand->u.num);
            break;
        }
        case FUNCTION_OPERAND:{
            fprintf(fp, "%s", operand->u.name);
            break;
        }
        case TEMPORARY_VARIABLE:{
            fprintf(fp, "t%d", operand->u.num);
            break;
        }
        case TEMPORARY_ADDRESS:{
            fprintf(fp, "*t%d", operand->u.num);
            break;
        }
        case STRUCTURE_ARRAY:
        case STRUCTURE_STRUCTURE:{
            fprintf(fp, "t%d", operand->u.variable.var_num);
            break;
        }
        default: break;
    }
}

void printInterCode(){
    // int num = 0;
    // InterCode cur1 = inter_code_head->next;
    // while(cur1 != inter_code_head){
    //     num++;
    //     printf("kind = %d\n", cur1->kind);
    //     cur1 = cur1->next;
    // }
    // printf("num = %d\n", num);


    FILE* fp = fopen("../Result/A_1.ir", "w");
    InterCode cur = inter_code_head->next;
    while(cur != inter_code_head){
        switch(cur->kind){
            case LABEL_INTERCODE:{
                fprintf(fp, "LABEL ");
                printOperand(fp, cur->op1);
                fprintf(fp, " :");
                break;
            }
            case FUNCTION_INTERCODE:{
                fprintf(fp, "FUNCTION ");
                printOperand(fp, cur->op1);
                fprintf(fp, " :");
                break;
            }
            case ASSIGN:{
                printOperand(fp, cur->result);
                fprintf(fp, " := ");
                printOperand(fp, cur->op1);
                break;
            }
            case PLUS:{
                printOperand(fp, cur->result);
                fprintf(fp, " := ");
                printOperand(fp, cur->op1);
                fprintf(fp, " + ");
                printOperand(fp, cur->op2);
                break;
            }
            case MINUS:{
                printOperand(fp, cur->result);
                fprintf(fp, " := ");
                printOperand(fp, cur->op1);
                fprintf(fp, " - ");
                printOperand(fp, cur->op2);
                break;
            }
            case STAR:{
                printOperand(fp, cur->result);
                fprintf(fp, " := ");
                printOperand(fp, cur->op1);
                fprintf(fp, " * ");
                printOperand(fp, cur->op2);
                break;
            }
            case DIV:{
                printOperand(fp, cur->result);
                fprintf(fp, " := ");
                printOperand(fp, cur->op1);
                fprintf(fp, " / ");
                printOperand(fp, cur->op2);
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
                fprintf(fp, "GOTO ");
                printOperand(fp, cur->result);
                break;
            }
            case JE:{
                fprintf(fp, "IF ");
                printOperand(fp, cur->op1);
                fprintf(fp, " == ");
                printOperand(fp, cur->op2);
                fprintf(fp, " GOTO ");
                printOperand(fp, cur->result);
                break;
            }
            case JNE:{
                fprintf(fp, "IF ");
                printOperand(fp, cur->op1);
                fprintf(fp, " != ");
                printOperand(fp, cur->op2);
                fprintf(fp, " GOTO ");
                printOperand(fp, cur->result);
                break;
            }
            case JA:{
                fprintf(fp, "IF ");
                printOperand(fp, cur->op1);
                fprintf(fp, " > ");
                printOperand(fp, cur->op2);
                fprintf(fp, " GOTO ");
                printOperand(fp, cur->result);
                break;
            }
            case JAE:{
                fprintf(fp, "IF ");
                printOperand(fp, cur->op1);
                fprintf(fp, " >= ");
                printOperand(fp, cur->op2);
                fprintf(fp, " GOTO ");
                printOperand(fp, cur->result);
                break;
            }
            case JB:{
                fprintf(fp, "IF ");
                printOperand(fp, cur->op1);
                fprintf(fp, " < ");
                printOperand(fp, cur->op2);
                fprintf(fp, " GOTO ");
                printOperand(fp, cur->result);
                break;
            }
            case JBE:{
                fprintf(fp, "IF ");
                printOperand(fp, cur->op1);
                fprintf(fp, " <= ");
                printOperand(fp, cur->op2);
                fprintf(fp, " GOTO ");
                printOperand(fp, cur->result);
                break;
            }
            case RETURN:{
                fprintf(fp, "RETURN ");
                printOperand(fp, cur->op1);
                break;
            }
            case DEC:{
                fprintf(fp, "DEC ");
                printOperand(fp, cur->op1);
                fprintf(fp, " %d", cur->op2->u.const_value);
                break;
            }
            case ARG:{
                fprintf(fp, "ARG ");
                printOperand(fp, cur->result);
                break;
            }
            case CALL:{
                printOperand(fp, cur->result);
                fprintf(fp, " := CALL ");
                printOperand(fp, cur->op1);
                break;
            }
            case PARAM:{
                fprintf(fp, "PARAM ");
                printOperand(fp, cur->op1);
                break;
            }
            case READ:{
                fprintf(fp, "READ ");
                printOperand(fp, cur->result);
                break;
            }
            case WRITE:{
                fprintf(fp, "WRITE ");
                printOperand(fp, cur->result);
                break;
            }
            default: break;
        }
        fprintf(fp, "\n");
        cur = cur->next;
    }
    fclose(fp);
}

int haveMultiDimensionalArray(){
    for(int i = 0; i < TABLE_NUM + 1; ++i){
        Symbol cur = symbolTable[i];
        while (cur != NULL){
            if(cur->type->kind == ARRAY && cur->type->u.array.elem->kind == ARRAY){
                return 1;
            }
            cur = cur->next;
        }
    }
    return 0;
}

int isArray(Operand operand){
    if(operand->kind == VARIABLE){
        Type leftType = getIDType(operand->u.variable.var_name);
        if(leftType->kind == ARRAY){
            return 1;
        }
    }else if(operand->kind == STRUCTURE_ARRAY){
        return 1;
    }
    return 0;
}

int isStructure(Operand operand){
    if(operand->kind == VARIABLE || operand->kind == STRUCTURE_ARRAY){
        Type leftType = getIDType(operand->u.variable.var_name);
        if(leftType->kind == ARRAY && leftType->u.array.elem->kind == STRUCTURE){
            return 1;
        }
    }
    return 0;
}

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
        case STRUCTURE_STRUCTURE:
        case STRUCTURE_ARRAY:
        case ADDRESS:
        case REFERENCE:
        case VARIABLE:{
            // 一般变量
            result->u.variable.var_num = num;
            result->u.variable.var_name = getStr(name);
            break;
        }
        case CONSTANT:{
            // 常量
            result->u.const_value = num;
            break;
        }
        case FUNCTION_OPERAND:{
            // 变量地址
            result->u.name = getStr(name);
            break;
        }
        case LABEL_OPERAND:
        case TEMPORARY_VARIABLE:
        case TEMPORARY_ADDRESS:{
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

// 在place后插入target
void insertAfter(InterCode target, InterCode place){
    target->next = place->next;
    place->next->prev = target;
    target->prev = place;
    place->next = target;
}

void deleteInterCode(InterCode intercode){
    intercode->prev->next = intercode->next;
    intercode->next->prev = intercode->prev;
}

void insertOperand(Operand operand){
    operand->next = operand_tail->next;
    operand_tail->next = operand;
    operand_tail = operand_tail->next;
}

Operand findOperand(char* name){
    Operand cur = operand_head->next;
    while (cur != NULL){
        if((cur->kind == VARIABLE || cur->kind == ADDRESS) && strcmp(cur->u.variable.var_name, name) == 0){
            return cur;
        }else if(cur->kind == FUNCTION_OPERAND && strcmp(cur->u.name, name) == 0){
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

Operand findStructure(char* name){
    Operand cur = operand_head->next;
    while (cur != NULL){
        if((cur->kind == VARIABLE || cur->kind == ADDRESS) && strcmp(cur->u.variable.var_name, name) == 0){
            return cur;
        }
        cur = cur->next;
    }
    return NULL;
}

int getStructureIndex(Type type, char* name){
    FieldList cur = type->u.structure.fieldList;
    int index = 0;
    while(cur != NULL){
        if(strcmp(cur->name, name) == 0){
            break;
        }
        index += getTypeSize(cur->type);
        cur = cur->tail;
    }

    FieldList cur2 = type->u.structure.fieldList;
    int index2 = 0;
    while(cur2 != NULL){
        index2 += getTypeSize(cur2->type);
        cur2 = cur2->tail;
    }

    int result = index2 - index - getTypeSize(cur->type);
    return result;
}

void IRProgram(treeNode* root){
#ifdef print_lab_3
    printf("IRProgram\n");
#endif
    if(root == NULL)    return;
    initIr();
    if(haveMultiDimensionalArray()){
        printf("Cannot translate: Code contains variables of multi-dimensional array type or parameters of array type.\n");
        return;
    }
    IRExtDefList(root->firstChild);
    changed = 0;
    // irOptimise();
    printInterCode();
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
    Operand funcOperand = newOperand(FUNCTION_OPERAND, 0, parent->firstChild->text);
    insertOperand(funcOperand);
    InterCode funcInterCode = newInterCode(FUNCTION_INTERCODE, funcOperand, NULL, NULL);
    insertInterCode(funcInterCode);
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
    // printf("param name = %s\n", name);
    Type type = getIDType(cur->text);
    Operand varOperand = NULL;
    if(type == NULL)    return;
    if(type->kind == ARRAY){
        // 函数参数为数组
        printf("Cannot translate: Code contains variables of multi-dimensional array type or parameters of array type.\n");
        IRERROR = 1;
        exit(0);
        return;
    }else if(type->kind == STRUCTURE){
        // 结构体，传入的是地址
        varOperand = newOperand(ADDRESS, var_num++, cur->text);
    }else{
        varOperand = newOperand(VARIABLE, var_num++, cur->text);
    }
    // varOperand = newOperand(VARIABLE, var_num++, cur->text);
    // Operand varOperand = newOperand(VARIABLE, var_num++, cur->text);
    insertOperand(varOperand);
    Operand varOperand2 = newOperand(VARIABLE, varOperand->u.variable.var_num, cur->text);
    InterCode varInterCode = newInterCode(PARAM, varOperand2, NULL, NULL);
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
        Operand right = IRExp(parent->firstChild->nextBrother->nextBrother, NULL);
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

        Type type = getIDType(parent->firstChild->text);
        if(type->kind == STRUCTURE){
            int size = getTypeSize(type);
            // printf("size = %d\n", size);
            Operand varOperand1 = newOperand(VARIABLE, var_num++, parent->firstChild->text);
            insertOperand(varOperand1);
            Operand varOperand2 = newOperand(CONSTANT, size, NULL);
            InterCode varInterCode = newInterCode(DEC, varOperand1, varOperand2, NULL);
            insertInterCode(varInterCode);
            return varOperand1;
        }else{
            Operand varOperand = newOperand(VARIABLE, var_num++, parent->firstChild->text);
            insertOperand(varOperand);
            return varOperand;
        }
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
    if(type == NULL)    return NULL;
    if(type->kind == ARRAY && type->u.array.elem->kind == ARRAY){
        // 多维数组
        IRERROR = 1;
        return NULL;
    }
    int size = getTypeSize(type);
    // printf("size = %d\n", size);
    Operand varOperand1 = newOperand(VARIABLE, var_num++, name);
    insertOperand(varOperand1);
    Operand varOperand2 = newOperand(CONSTANT, size, NULL);
    InterCode varInterCode = newInterCode(DEC, varOperand1, varOperand2, NULL);
    insertInterCode(varInterCode);
    return varOperand1;
}

Operand IRExp(treeNode* parent, Operand place){
#ifdef print_lab_3
    printf("IRExp\n");
#endif
    // printf("parent's name: %s\n", parent->name);
    // printf("first child's name: %s\n", parent->firstChild->name);
    // printNode(parent, 0);
    if(strcmp(parent->firstChild->name, "ID") == 0 && parent->firstChild->nextBrother == NULL){
        // Exp: ID
        Operand idOperand = findOperand(parent->firstChild->text);
        if(place == NULL){
            return idOperand;
        }else{
            InterCode idInterCode = newInterCode(ASSIGN, idOperand, NULL, place);
            insertInterCode(idInterCode);
            return NULL;
        }
    }else if(strcmp(parent->firstChild->name, "INT") == 0){
        // Exp: INT
        Operand intOperand = newOperand(CONSTANT, atoi(parent->firstChild->text), NULL);
        if(place == NULL){
            return intOperand;
        }else{
            InterCode intInterCode = newInterCode(ASSIGN, intOperand, NULL, place);
            insertInterCode(intInterCode);
            return NULL;
        }
    }else if(strcmp(parent->firstChild->name, "FLOAT") == 0){
        // TODO:???
        return NULL;
    }else if(strcmp(parent->firstChild->name, "Exp") == 0){
        if(strcmp(parent->firstChild->nextBrother->nextBrother->name, "Exp") == 0){
            if(strcmp(parent->firstChild->nextBrother->name, "LB") != 0){
                if(strcmp(parent->firstChild->nextBrother->name, "ASSIGNOP") == 0){
                    // Exp: Exp ASSIGNOP Exp
                    Operand leftOperand = IRExp(parent->firstChild, NULL);
                    if(isArray(leftOperand)){
                        // 数组赋值，右操作数返回值一定是数组
                        Operand rightOperand = IRExp(parent->firstChild->nextBrother->nextBrother, NULL);
                        // printf("leftName = %s, rightName = %s\n", leftOperand->u.variable.var_name, rightOperand->u.variable.var_name);
                        Type leftType = getIDType(leftOperand->u.variable.var_name);
                        Type rightType = getIDType(rightOperand->u.variable.var_name);
                        int minSize = leftType->u.array.size > rightType->u.array.size ? rightType->u.array.size : leftType->u.array.size;
                        int typeSize = getTypeSize(leftType->u.array.elem);
                        // printf("minSize = %d, typeSize = %d\n", minSize, typeSize);
                        Operand leftReferenceOperand;
                        if(leftOperand->kind == STRUCTURE_ARRAY){
                            // v1
                            leftReferenceOperand = leftOperand;
                        }else{
                            // &v1
                            leftReferenceOperand = newOperand(REFERENCE, leftOperand->u.variable.var_num, leftOperand->u.variable.var_name);
                        }
                        Operand rightReferenceOperand;
                        if(rightOperand->kind == STRUCTURE_ARRAY){
                            // v2
                            rightReferenceOperand = rightOperand;
                        }else{
                            // &v2
                            rightReferenceOperand = newOperand(REFERENCE, rightOperand->u.variable.var_num, rightOperand->u.variable.var_name);
                        }
                        for(int i = 0; i < minSize; ++i){
                            // i * 4
                            Operand leftIndexOperand = newOperand(CONSTANT, typeSize * i, NULL);
                            // t1
                            Operand leftResultOperand = newOperand(TEMPORARY_VARIABLE, temp_var_num++, NULL);
                            // t1 = &v1/v1 + i * 4
                            InterCode leftResultInterCode = newInterCode(PLUS, leftReferenceOperand, leftIndexOperand, leftResultOperand);
                            // i * 4
                            Operand rightIndexOperand = newOperand(CONSTANT, typeSize * i, NULL);
                            // t2
                            Operand rightResultOperand = newOperand(TEMPORARY_VARIABLE, temp_var_num++, NULL);
                            // t2 = &v2/v2 + i * 4
                            InterCode rightResultInterCode = newInterCode(PLUS, rightReferenceOperand, rightIndexOperand, rightResultOperand);
                            insertInterCode(leftResultInterCode);
                            insertInterCode(rightResultInterCode);
                            // *t1
                            Operand leftResultOperand2 = newOperand(TEMPORARY_ADDRESS, leftResultOperand->u.num, NULL);
                            // *t2
                            Operand rightResultOperand2 = newOperand(TEMPORARY_ADDRESS, rightResultOperand->u.num, NULL);
                            // *t1 = *t2
                            InterCode assignInterCode = newInterCode(ASSIGN, rightResultOperand2, NULL, leftResultOperand2);
                            insertInterCode(assignInterCode);
                        }
                    }else{
                        IRExp(parent->firstChild->nextBrother->nextBrother, leftOperand);
                        if(place != NULL){
                            InterCode assignInterCode = newInterCode(ASSIGN, leftOperand, NULL, place);
                            insertInterCode(assignInterCode);
                        }
                    }
                    return leftOperand;
                }
                // Exp: Exp operator Exp
                else if(strcmp(parent->firstChild->nextBrother->name, "AND") == 0 || 
                    strcmp(parent->firstChild->nextBrother->name, "OR") == 0 || 
                    strcmp(parent->firstChild->nextBrother->name, "RELOP") == 0){
                    if(place == NULL){
                        place = newOperand(TEMPORARY_VARIABLE, temp_var_num++, NULL);
                    }
                    Operand label1 = newOperand(LABEL_OPERAND, label_num++, NULL);
                    Operand label2 = newOperand(LABEL_OPERAND, label_num++, NULL);
                    Operand zeroOperand = newOperand(CONSTANT, 0, NULL);
                    Operand oneOperand = newOperand(CONSTANT, 1, NULL);
                    InterCode placeZeroInterCode = newInterCode(ASSIGN, zeroOperand, NULL, place);
                    InterCode placeOneInterCode = newInterCode(ASSIGN, oneOperand, NULL, place);
                    InterCode labelCode1 = newInterCode(LABEL_INTERCODE, label1, NULL, NULL);
                    InterCode labelCode2 = newInterCode(LABEL_INTERCODE, label2, NULL, NULL);
                    insertInterCode(placeZeroInterCode);
                    IRCond(parent, label1, label2);
                    insertInterCode(labelCode1);
                    insertInterCode(placeOneInterCode);
                    insertInterCode(labelCode2);
                    return place;
                }else{
                    // 加减乘除，类型不变
                    if(place == NULL){
                        place = newOperand(TEMPORARY_VARIABLE, temp_var_num++, NULL);
                    }
                    Operand leftOperand = IRExp(parent->firstChild, NULL);
                    Operand rightOperand = IRExp(parent->firstChild->nextBrother->nextBrother, NULL);
                    InterCode operationsInterCode = NULL;

                    if(place->kind == TEMPORARY_ADDRESS){
                        // 左边数组或结构体
                        // Operand place2 = newOperand(TEMPORARY_VARIABLE, place->u.variable.var_num, NULL);
                        Operand tempOperand = newOperand(TEMPORARY_VARIABLE, temp_var_num++, NULL);

                        if(strcmp(parent->firstChild->nextBrother->name, "PLUS") == 0){
                            operationsInterCode = newInterCode(PLUS, leftOperand, rightOperand, tempOperand);
                        }else if(strcmp(parent->firstChild->nextBrother->name, "MINUS") == 0){
                            operationsInterCode = newInterCode(MINUS, leftOperand, rightOperand, tempOperand);
                        }else if(strcmp(parent->firstChild->nextBrother->name, "STAR") == 0){
                            operationsInterCode = newInterCode(STAR, leftOperand, rightOperand, tempOperand);
                        }else if(strcmp(parent->firstChild->nextBrother->name, "DIV") == 0){
                            operationsInterCode = newInterCode(DIV, leftOperand, rightOperand, tempOperand);
                        }
                        insertInterCode(operationsInterCode);

                        InterCode assignInterCode = newInterCode(ASSIGN, tempOperand, NULL, place);
                        insertInterCode(assignInterCode);
                    }else{
                        if(strcmp(parent->firstChild->nextBrother->name, "PLUS") == 0){
                            operationsInterCode = newInterCode(PLUS, leftOperand, rightOperand, place);
                        }else if(strcmp(parent->firstChild->nextBrother->name, "MINUS") == 0){
                            operationsInterCode = newInterCode(MINUS, leftOperand, rightOperand, place);
                        }else if(strcmp(parent->firstChild->nextBrother->name, "STAR") == 0){
                            operationsInterCode = newInterCode(STAR, leftOperand, rightOperand, place);
                        }else if(strcmp(parent->firstChild->nextBrother->name, "DIV") == 0){
                            operationsInterCode = newInterCode(DIV, leftOperand, rightOperand, place);
                        }
                        insertInterCode(operationsInterCode);
                    }
                    return place;
                }
            }else{
                // Exp: Exp LB Exp RB
                // a[i] = j
                // a
                // Type arrayType = getIDType(parent->firstChild->firstChild->text);     // 一定是一维数组
                Operand firstOperand = IRExp(parent->firstChild, NULL);
                Type arrayType = getIDType(firstOperand->u.variable.var_name);
                // 4
                int size = getTypeSize(arrayType->u.array.elem);
                // v1
                // Operand arrayOperand = findOperand(parent->firstChild->firstChild->text);
                Operand arrayOperand = firstOperand;
                // 数组不会有地址类型出现
                // &v1
                Operand arrayReferenceOperand;
                if(firstOperand->kind == STRUCTURE_ARRAY){
                    // 结构体中的数组，直接当做地址
                    arrayReferenceOperand = firstOperand;
                }else{
                    arrayReferenceOperand = newOperand(REFERENCE, arrayOperand->u.variable.var_num, arrayOperand->u.variable.var_name);
                }
                // i
                Operand indexOperand = IRExp(parent->firstChild->nextBrother->nextBrother, NULL);
                // 4
                Operand sizeOperand;
                if(indexOperand->kind == CONSTANT){
                    // 下标为常数，直接加上
                    int index = indexOperand->u.const_value * size;
                    sizeOperand = newOperand(CONSTANT, index, NULL);
                    Operand resultOperand = newOperand(TEMPORARY_VARIABLE, temp_var_num++, NULL);
                    // t2 = &v1 + index
                    InterCode resultInterCode = newInterCode(PLUS, arrayReferenceOperand, sizeOperand, resultOperand);
                    insertInterCode(resultInterCode);
                    Operand resultOperand2 = newOperand(TEMPORARY_ADDRESS, resultOperand->u.num, NULL);
                    if(isStructure(firstOperand)){
                        resultOperand2 = newOperand(STRUCTURE_STRUCTURE, resultOperand->u.num, firstOperand->u.variable.var_name);
                    }
                    else if(place != NULL){
                        InterCode assignInterCode = newInterCode(ASSIGN, resultOperand2, NULL, place);
                        insertInterCode(assignInterCode);
                    }
                    return resultOperand2;
                }
                sizeOperand = newOperand(CONSTANT, size, NULL);
                // t1
                Operand tempIndexOperand = newOperand(TEMPORARY_VARIABLE, temp_var_num++, NULL);
                // t1 = i * 4
                InterCode indexInterCode = newInterCode(STAR, indexOperand, sizeOperand, tempIndexOperand);
                // t2
                Operand resultOperand = newOperand(TEMPORARY_VARIABLE, temp_var_num++, NULL);
                // t2 = &v1 + t1
                InterCode resultInterCode = newInterCode(PLUS, arrayReferenceOperand, tempIndexOperand, resultOperand);
                insertInterCode(indexInterCode);
                insertInterCode(resultInterCode);
                Operand resultOperand2 = newOperand(TEMPORARY_ADDRESS, resultOperand->u.num, NULL);

                if(isStructure(firstOperand)){
                    resultOperand2 = newOperand(STRUCTURE_STRUCTURE, resultOperand->u.num, firstOperand->u.variable.var_name);
                }
                // 结构体之间不会赋值
                else if(place != NULL){
                    InterCode assignInterCode = newInterCode(ASSIGN, resultOperand2, NULL, place);
                    insertInterCode(assignInterCode);
                }
                return resultOperand2;
            }
        }else{
            // Exp: Exp DOT ID
            // treeNode* cur = parent->firstChild;
            int index = 0;
            // while(strcmp(cur->firstChild->name, "Exp") == 0){
            //     Type type = getIDType(cur->firstChild->nextBrother->nextBrother->text);
            //     index += getStructureIndex(type, cur->nextBrother->nextBrother->text);
            //     cur = cur->firstChild;
            // }
            // printf("parent firstChild name = %s\n", parent->firstChild->text);
            Operand firstOperand = IRExp(parent->firstChild, NULL);
            Type type = getIDType(firstOperand->u.variable.var_name);
            // printf("type = %d, text = %s\n", type->kind, parent->firstChild->nextBrother->nextBrother->text);
            if(type->kind == ARRAY){
                // 结构体数组，得到ARRAY，需要使用elem拿到结构体类型
                index = getStructureIndex(type->u.array.elem, parent->firstChild->nextBrother->nextBrother->text);
            }else{
                index = getStructureIndex(type, parent->firstChild->nextBrother->nextBrother->text);
            }
            // id在Exp中的偏移量
            Operand indexOperand = newOperand(CONSTANT, index, NULL);
            Operand resultOperand = newOperand(TEMPORARY_VARIABLE, temp_var_num++, NULL);
            if(firstOperand->kind == STRUCTURE_STRUCTURE){
                // 结构体中的结构体
                InterCode indexInterCode = newInterCode(PLUS, firstOperand, indexOperand, resultOperand);
                insertInterCode(indexInterCode);
            }else if(firstOperand->kind == VARIABLE){
                // 普通结构体
                Operand structureReferenceOperand = newOperand(REFERENCE, firstOperand->u.variable.var_num, firstOperand->u.variable.var_name);
                InterCode indexInterCode = newInterCode(PLUS, structureReferenceOperand, indexOperand, resultOperand);
                insertInterCode(indexInterCode);
            }else if(firstOperand->kind == ADDRESS){
                // 参数结构体
                Operand structureReferenceOperand = newOperand(VARIABLE, firstOperand->u.variable.var_num, firstOperand->u.variable.var_name);
                InterCode indexInterCode = newInterCode(PLUS, structureReferenceOperand, indexOperand, resultOperand);
                insertInterCode(indexInterCode);
            }

            // Type type = getIDType(cur->firstChild->text);
            // index += getStructureIndex(type, cur->nextBrother->nextBrother->text);
            // // v1
            // Operand structureOperand = findStructure(cur->firstChild->text);
            
            // Operand resultOperand = newOperand(TEMPORARY_VARIABLE, temp_var_num++, NULL);
            // InterCode resultInterCode = NULL;
            // // if(structureOperand == NULL){
            // //     printf("null!\n");
            // // }
            // if(structureOperand->kind == VARIABLE){
            //     // 普通结构体使用，&v1
            //     // printf("2\n");
            //     Operand structureReferenceOperand = newOperand(REFERENCE, structureOperand->u.variable.var_num, structureOperand->u.variable.var_name);
            //     resultInterCode = newInterCode(PLUS, structureReferenceOperand, indexOperand, resultOperand);
            // }else if(structureOperand->kind == ADDRESS){
            //     // 参数结构体引用, v1
            //     // printf("3\n");
            //     Operand structureReferenceOperand = newOperand(VARIABLE, structureOperand->u.variable.var_num, structureOperand->u.variable.var_name);
            //     resultInterCode = newInterCode(PLUS, structureReferenceOperand, indexOperand, resultOperand);
            // }
            // // printf("4\n");
            // insertInterCode(resultInterCode);
            Type type1 = getIDType(parent->firstChild->nextBrother->nextBrother->text);
            if(type1->kind == ARRAY){
                // 结构体域为数组
                Operand resultOperand2 = newOperand(STRUCTURE_ARRAY, resultOperand->u.num, parent->firstChild->nextBrother->nextBrother->text);
                return resultOperand2;
            }
            else if(type1->kind == STRUCTURE){
                Operand resultOperand2 = newOperand(STRUCTURE_STRUCTURE, resultOperand->u.num, parent->firstChild->nextBrother->nextBrother->text);
                return resultOperand2;
            }
            
            else{
                Operand resultOperand2 = newOperand(TEMPORARY_ADDRESS, resultOperand->u.num, NULL);
                if(place != NULL){
                    // 处于等式右边，需赋值
                    InterCode assignInterCode = newInterCode(ASSIGN, resultOperand2, NULL, place);
                    insertInterCode(assignInterCode);
                }
                return resultOperand2;
            }
        }
    }else if(strcmp(parent->firstChild->name, "MINUS") == 0){
        // Exp: MINUS Exp
        Operand minusOperand = IRExp(parent->firstChild->nextBrother, NULL);
        if(place == NULL){
            place = newOperand(TEMPORARY_VARIABLE, temp_var_num++, NULL);
        }
        Operand zeroOperand = newOperand(CONSTANT, 0, NULL);
        if(place->kind == TEMPORARY_ADDRESS){
            Operand tempOperand = newOperand(TEMPORARY_VARIABLE, temp_var_num++, NULL);
            InterCode minusInterCode = newInterCode(MINUS, zeroOperand, minusOperand, tempOperand);
            insertInterCode(minusInterCode);
            InterCode assignInterCode = newInterCode(ASSIGN, tempOperand, NULL, place);
            insertInterCode(assignInterCode);
        }else{
            InterCode minusInterCode = newInterCode(MINUS, zeroOperand, minusOperand, place);
            insertInterCode(minusInterCode);
        }
        return place;
    }else if(strcmp(parent->firstChild->name, "NOT") == 0){
        // Exp: NOT Exp
        if(place == NULL){
            place = newOperand(TEMPORARY_VARIABLE, temp_var_num++, NULL);
        }
        Operand label1 = newOperand(LABEL_OPERAND, label_num++, NULL);
        Operand label2 = newOperand(LABEL_OPERAND, label_num++, NULL);
        Operand zeroOperand = newOperand(CONSTANT, 0, NULL);
        Operand oneOperand = newOperand(CONSTANT, 1, NULL);
        InterCode placeZeroInterCode = newInterCode(ASSIGN, zeroOperand, NULL, place);
        InterCode placeOneInterCode = newInterCode(ASSIGN, oneOperand, NULL, place);
        InterCode labelCode1 = newInterCode(LABEL_INTERCODE, label1, NULL, NULL);
        InterCode labelCode2 = newInterCode(LABEL_INTERCODE, label2, NULL, NULL);
        insertInterCode(placeZeroInterCode);
        IRCond(parent, label1, label2);
        insertInterCode(labelCode1);
        insertInterCode(placeOneInterCode);
        insertInterCode(labelCode2);
        return place;
    }else if(strcmp(parent->firstChild->name, "LP") == 0){
        // Exp: LP Exp RP
        return IRExp(parent->firstChild->nextBrother, place);
    }else if(strcmp(parent->firstChild->nextBrother->nextBrother->name, "Args") == 0){
        // Exp: ID LP Args RP
        PointToOperand args_list = IRArgs(parent->firstChild->nextBrother->nextBrother);
        if(strcmp(parent->firstChild->text, "write") == 0){
            // write
            InterCode writeInterCode = newInterCode(WRITE, NULL, NULL, args_list->next->point);
            insertInterCode(writeInterCode);
            return NULL;
        }else{
            if(place == NULL){
                place = newOperand(TEMPORARY_VARIABLE, temp_var_num++, NULL);
            }
            PointToOperand cur = args_list->next;
            while(cur != NULL){
                InterCode argInterCode = newInterCode(ARG, NULL, NULL, cur->point);
                insertInterCode(argInterCode);
                cur = cur->next;
            }
            Operand functionOperand = findOperand(parent->firstChild->text);
            if(place->kind == TEMPORARY_ADDRESS){
                // 返回值是数组元素或结构体域
                // Operand place2 = newOperand(TEMPORARY_VARIABLE, place->u.variable.var_num, NULL);
                Operand tempOperand = newOperand(TEMPORARY_VARIABLE, temp_var_num++, NULL);
                // read t1
                InterCode callInterCode = newInterCode(CALL, functionOperand, NULL, tempOperand);
                insertInterCode(callInterCode);
                // *t2 = t1
                InterCode assignInterCode = newInterCode(ASSIGN, tempOperand, NULL, place);
                insertInterCode(assignInterCode);
            }else{
                InterCode callInterCode = newInterCode(CALL, functionOperand, NULL, place);
                insertInterCode(callInterCode);
            }
            return place;
        }
    }else{
        // Exp: ID LP RP
        if(place == NULL){
            place = newOperand(TEMPORARY_VARIABLE, temp_var_num++, NULL);
        }
        // read
        if(strcmp(parent->firstChild->text, "read") == 0){
            if(place->kind == TEMPORARY_ADDRESS){
                // 读入数组或结构体
                // Operand place2 = newOperand(TEMPORARY_VARIABLE, place->u.variable.var_num, NULL);
                Operand tempOperand = newOperand(TEMPORARY_VARIABLE, temp_var_num++, NULL);
                // read t1
                InterCode readInterCode = newInterCode(READ, NULL, NULL, tempOperand);
                insertInterCode(readInterCode);
                // *t2 = t1
                InterCode assignInterCode = newInterCode(ASSIGN, tempOperand, NULL, place);
                insertInterCode(assignInterCode);
            }else{
                InterCode readInterCode = newInterCode(READ, NULL, NULL, place);
                insertInterCode(readInterCode);
            }
            return place;
        }
        Operand functionOperand = findOperand(parent->firstChild->text);
        if(place->kind == TEMPORARY_ADDRESS){
            // 返回值是数组元素或结构体域
            // Operand place2 = newOperand(TEMPORARY_VARIABLE, place->u.variable.var_num, NULL);
            Operand tempOperand = newOperand(TEMPORARY_VARIABLE, temp_var_num++, NULL);
            // read t1
            InterCode callInterCode = newInterCode(CALL, functionOperand, NULL, tempOperand);
            insertInterCode(callInterCode);
            // *t2 = t1
            InterCode assignInterCode = newInterCode(ASSIGN, tempOperand, NULL, place);
            insertInterCode(assignInterCode);
        }else{
            InterCode callInterCode = newInterCode(CALL, functionOperand, NULL, place);
            insertInterCode(callInterCode);
        }
        return place;
    }
}

void IRStmt(treeNode* parent){
#ifdef print_lab_3
    printf("IRStmt\n");
#endif
    if(parent == NULL)  return;
    if(strcmp(parent->firstChild->name, "Exp") == 0){
        // Stmt: Exp SEMI
        IRExp(parent->firstChild, NULL);
    }else if(strcmp(parent->firstChild->name, "CompSt") == 0){
        // Stmt: CompSt
        IRCompSt(parent->firstChild);
    }else if(strcmp(parent->firstChild->name, "RETURN") == 0){
        // Stmt: RETURN Exp SEMI
        Operand returnOperand = IRExp(parent->firstChild->nextBrother, NULL);
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
        Operand leftOperand = IRExp(parent->firstChild, NULL);
        Operand rightOperand = IRExp(parent->firstChild->nextBrother->nextBrother, NULL);
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
        Operand expOperand = IRExp(parent, NULL);
        Operand zeroOperand = newOperand(CONSTANT, 0, NULL);
        InterCode notEqualInterCode = newInterCode(JNE, expOperand, zeroOperand, label_true);
        InterCode gotoLabelFalse = newInterCode(GOTO, NULL, NULL, label_false);
        insertInterCode(notEqualInterCode);
        insertInterCode(gotoLabelFalse);
    }
}

PointToOperand IRArgs(treeNode* parent){
#ifdef print_lab_3
    printf("IRArgs\n");
#endif
    treeNode* cur = parent->firstChild;
    PointToOperand arg_list = (PointToOperand)malloc(sizeof(struct PointToOperand_));
    arg_list->next = NULL;
    // PointToOperand cur_list = arg_list;
    while(cur->nextBrother != NULL){
        PointToOperand point = (PointToOperand)malloc(sizeof(struct PointToOperand_));
        point->point = IRExp(cur, NULL);
        if(point->point->kind == VARIABLE){
            // ARG + 结构体，若是一般结构体变量，则需要增加&
            Type type = getIDType(point->point->u.variable.var_name);
            if(type->kind == STRUCTURE){
                Operand structureReferenceOperand = newOperand(REFERENCE, point->point->u.variable.var_num, point->point->u.variable.var_name);
                point->point = structureReferenceOperand;
            }
        }
        point->next = arg_list->next;
        arg_list->next = point;
        // point->next = cur_list->next;
        // cur_list->next = point;
        // cur_list = cur_list->next;
        cur = cur->nextBrother->nextBrother->firstChild;
    }
    PointToOperand point = (PointToOperand)malloc(sizeof(struct PointToOperand_));
    point->point = IRExp(cur, NULL);
    if(point->point->kind == VARIABLE){
        // ARG + 结构体，若是一般结构体变量，则需要增加&
        Type type = getIDType(point->point->u.variable.var_name);
        if(type->kind == STRUCTURE){
            Operand structureReferenceOperand = newOperand(REFERENCE, point->point->u.variable.var_num, point->point->u.variable.var_name);
            point->point = structureReferenceOperand;
        }
    }
    point->next = arg_list->next;
    arg_list->next = point;
    // point->next = cur_list->next;
    // cur_list->next = point;
    // cur_list = cur_list->next;
    return arg_list;
}


void irOptimise(){
    // computeConstant();
    // replaceTempAssignConstant();
    // reverseIf();
}

// 加减乘除中的常数直接结算
void computeConstant(){
    InterCode cur = inter_code_head->next;
    while(cur != inter_code_head){
        if(cur->kind == PLUS || cur->kind == MINUS || cur->kind == STAR || cur->kind == DIV){
            if(cur->op1->kind == CONSTANT && cur->op2->kind == CONSTANT){
                int op1Value = cur->op1->u.const_value;
                int op2Value = cur->op2->u.const_value;
                int resultValue = 0;
                switch(cur->kind){
                    case PLUS:{
                        resultValue = op1Value + op2Value;
                        break;
                    }
                    case MINUS:{
                        resultValue = op1Value - op2Value;
                        break;
                    }
                    case STAR:{
                        resultValue = op1Value * op2Value;
                        break;
                    }
                    case DIV:{
                        resultValue = op1Value / op2Value;
                        break;
                    }
                    default: break;
                }
                if(cur->result->kind == TEMPORARY_VARIABLE){
                    // 左边为临时变量，将后续该临时变量都替换为常数，并删除该InterCode
                    replaceTempConstant(cur->next, cur->result->u.num, resultValue);
                    InterCode temp = cur->prev;
                    deleteInterCode(cur);
                    cur = temp;
                    changed = 1;
                }else{
                    Operand resultOperand = newOperand(CONSTANT, resultValue, NULL);
                    cur->kind = ASSIGN;
                    cur->op1 = resultOperand;
                    cur->op2 = NULL;
                    changed = 1;
                }
            }
        }
        cur = cur->next;
    }
}

// 替换是常量的临时变量
void replaceTempConstant(InterCode start, int temp_num, int const_value){
    InterCode cur = start;
    while(cur != inter_code_head){
        if(cur->op1 != NULL && cur->op1->kind == TEMPORARY_VARIABLE && cur->op1->u.num == temp_num){
            cur->op1->kind = CONSTANT;
            cur->op1->u.const_value = const_value;
        }
        if(cur->op2 != NULL && cur->op2->kind == TEMPORARY_VARIABLE && cur->op2->u.num == temp_num){
            cur->op2->kind = CONSTANT;
            cur->op2->u.const_value = const_value;
        }
        cur = cur->next;
    }
}

void replaceTempAssignConstant(){
    InterCode cur = inter_code_head->next;
    while(cur != inter_code_head){
        if(cur->kind == ASSIGN){
            if(cur->result->kind == TEMPORARY_VARIABLE && cur->op1->kind == CONSTANT){
                replaceTempConstant(cur->next, cur->result->u.num, cur->op1->u.const_value);
                InterCode temp = cur->prev;
                deleteInterCode(cur);
                cur = temp;
            }
        }
        cur = cur->next;
    }
}

void reverseIf(){
    InterCode cur = inter_code_head->next;
    while(cur != inter_code_head){
        if(cur->kind == JE || cur->kind == JNE || cur->kind == JA || cur->kind == JAE || cur->kind == JB || cur->kind == JBE){
            // IF x relop y GOTO Label1
            // GOTO Label2
            // Label1:
            if(cur->next != inter_code_head && cur->next->kind == GOTO && cur->next->next != inter_code_head && cur->next->next->kind == LABEL_INTERCODE){
                if(cur->result->u.num == cur->next->next->op1->u.num){
                    InterCode reverseInterCode;
                    Operand label2Operand = newOperand(LABEL_OPERAND, cur->next->result->u.num, NULL);
                    switch(cur->kind){
                        case JE:{
                            reverseInterCode = newInterCode(JNE, cur->op1, cur->op2, label2Operand);
                            break;
                        }
                        case JNE:{
                            reverseInterCode = newInterCode(JE, cur->op1, cur->op2, label2Operand);
                            break;
                        }
                        case JA:{
                            reverseInterCode = newInterCode(JBE, cur->op1, cur->op2, label2Operand);
                            break;
                        }
                        case JAE:{
                            reverseInterCode = newInterCode(JB, cur->op1, cur->op2, label2Operand);
                            break;
                        }
                        case JB:{
                            reverseInterCode = newInterCode(JAE, cur->op1, cur->op2, label2Operand);
                            break;
                        }
                        case JBE:{
                            reverseInterCode = newInterCode(JA, cur->op1, cur->op2, label2Operand);
                            break;
                        }
                    }
                    InterCode temp = cur->prev;
                    deleteInterCode(temp->next);
                    deleteInterCode(temp->next);
                    deleteInterCode(temp->next);
                    insertAfter(reverseInterCode, temp);
                    cur = reverseInterCode;
                }
            }
            
        }
        cur = cur->next;
    }
}