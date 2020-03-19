#include <stdio.h>
#include "treeNode.h"
extern void yyrestart(FILE * input_file );
extern int yyparse();
extern int yylineno;
extern treeNode* root;
extern int haveError;

int main(int argc, char** argv){
    if(argc < 2){                           //stdin
        return 0;
    }
    for(int i = 1; i < argc; ++i){
        FILE* f = fopen(argv[i], "r");
        if(!f){
            perror(argv[i]);
            return 1;
        }
        yyrestart(f);
        yylineno = 1;
        yyparse();
        fclose(f);
        if(!haveError){
            printNode(root, 0);
        }
    }
    return 0;
}