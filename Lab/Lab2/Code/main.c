#include <stdio.h>
#include "treeNode.h"
#include "hashtable.h"
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

        if(haveError == 0 && is_empty == 0){
            // printNode(root, 0);
            program(root);
        }
        // else if(is_empty == 1){
        //     printf("Program (%d)\n", empty_line_num);
        // }
    }
    return 0;
}