#include "treeNode.h"


treeNode* initLexical(char* name, char* text, int lineno){
    treeNode* temp = (treeNode*)malloc(sizeof(treeNode));
    temp->cellType = Lexical;
    temp->firstChild = temp->nextBrother = NULL;
    temp->lineno = lineno;
    temp->name = (char*)malloc(strlen(name) + 1);
    strcpy(temp->name, name);
    temp->text = (char*)malloc(strlen(text) + 1);
    strcpy(temp->text, text);
    return temp;
}

treeNode* initSyntax(char* name){
    treeNode* temp = (treeNode*)malloc(sizeof(treeNode));
    temp->cellType = Syntax;
    temp->firstChild = temp->nextBrother = NULL;
    temp->name = (char*)malloc(strlen(name) + 1);
    strcpy(temp->name, name);
    return temp;
}

void buildTree(treeNode* parent, int childNum, ...){
    if(parent == NULL) return;
    if(childNum == 0)    return;
    
    //------------- 可变参数，孩子个数可变 --------------
    va_list valist;
    va_start(valist, childNum);
    // //首孩子，用firstChild标示
    // treeNode* firstChild = va_arg(valist, treeNode*);
    // printf("firstChild's name = %s\n", firstChild->name);
    // parent->firstChild = firstChild;
    // parent->lineno = firstChild->lineno;                //父亲的行号为首词素的行号
    // //其他孩子，用nextBrother标示
    // treeNode* end = firstChild;
    // for(int i = 0; i < childNum - 1; ++i){
    //     treeNode* child = va_arg(valist, treeNode*);
    //     printf("child's name = %s\n", child->name);
    //     end->nextBrother = child;
    //     end = child;
    // }
    // va_end(valist);



    for(int i = 0 ; i < childNum ; i++){
		treeNode* child = va_arg(valist, treeNode*);
        if(child == NULL){                              //可能第一个孩子就是NULL
            continue;
        }
		if(parent->firstChild == NULL){
			parent->lineno = child->lineno;
			parent->firstChild = child;
		}
		else{                                           //可能孩子为NULL
			treeNode* temp = parent->firstChild;
			while(temp->nextBrother != NULL)
				temp = temp->nextBrother;
			temp->nextBrother = child;
		}
	}
    va_end(valist);

}

void printNode(treeNode* root, int lineno){
    if(root == NULL)    return;
    //打印空格
    for(int i = 0; i < lineno; ++i){
        printf("  ");
    }
    switch (root->cellType){
        case Lexical:{
            if(!strcmp("INT", root->name)){
                printf("INT: %d\n", (int)strtol(root->text, NULL, 0));
            }else if(!strcmp("FLOAT", root->name)){
                printf("FLOAT: %f\n", atof(root->text));
            }else if(!strcmp("ID", root->name)){
                printf("ID: %s\n", root->text);
            }else if(!strcmp("TYPE", root->name)){
                printf("TYPE: %s\n", root->text);
            }else{
                printf("%s\n", root->name);
            }
            break;
        }
        case Syntax:{
            //先自身
            printf("%s (%d)\n", root->name, root->lineno);
            //再遍历所有孩子
            treeNode* firstChild = root->firstChild;
            printNode(firstChild, lineno + 1);
            treeNode* end = firstChild;
            while(end != NULL){
                treeNode* child = end->nextBrother;
                printNode(child, lineno + 1);
                end = child;
            }
            break;
        }
        default:
            break;
    }
}