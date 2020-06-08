#include <stdio.h>
#include "treeNode.h"
#include "hashtable.h"
#include "ir.h"
extern void yyrestart(FILE * input_file );
extern int yyparse();
extern int yylineno;
extern treeNode* root;
extern int haveError;

extern void translateToMisp32(char* output);

int main(int argc, char** argv){
    if(argc < 2){                           //stdin
        return 0;
    }
    FILE* f = fopen(argv[1], "r");
    if(!f){
        perror(argv[1]);
        return 1;
    }
    yyrestart(f);
    yylineno = 1;
    yyparse();
    fclose(f);

    if(haveError == 0 && is_empty == 0){
        // printNode(root, 0);
        program(root);
        IRProgram(root);
        translateToMisp32(argv[2]);
    }
    // else if(is_empty == 1){
    //     printf("Program (%d)\n", empty_line_num);
    // }
    return 0;
}