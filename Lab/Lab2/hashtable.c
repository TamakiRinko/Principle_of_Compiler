#include "hashtable.h"

Symbol symbolTable[TABLE_NUM];

unsigned int hash_pjw(char* name){
    unsigned int val = 0, i;
    for (; *name; ++name){
        val = (val << 2) + *name;
        if (i = val & ~0x3fff) val = (val ^ (i >> 12)) & TABLE_NUM;
    }
    return val;
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
                    if(!cur->type->isEqual(symbol->type)){                                                          // 类型不同
                        return 19;
                    }else if(cur->type->u.function->isDefined == 0 && symbol->type->u.function->isDefined == 1){    // 先声明后定义
                        cur->type->u.function->isDefined = 1;
                        return 0;
                    }else if(cur->type->u.function->isDefined == 1 && symbol->type->u.function->isDefined == 1){    // 两次定义
                        return 4;
                    }
                }
                return 3;
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

void program(treeNode* root){
    if(root->firstChild != NULL){
        extDefList(root->firstChild);
    }    
}

void extDefList(treeNode* root){
    
}
