#include <stdio.h>
extern void yyrestart(FILE * input_file );
extern int yyparse();

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
        yyparse();
        fclose(f);
    }
    return 0;
}