#include "v2key.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void yyerror(char *s, ...)
{
    va_list ap;
    va_start(ap, s);

    fprintf(stderr, "%d: error: ", yylineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
    exit(1);
}

int main(int argc, char* argv[])
{
    int i;
    if (argc==1)
    {
        fprintf(stderr, "v2key.x [*.F]\n");
        exit(1);
    }
    
    for (i=1; i<argc; i++)
    {
        FILE *pf= fopen(argv[i],"r");
        if (pf==NULL) 
        {
            fprintf(stderr, "Open %s failed.", argv[i]); 
            exit(1);
        }
        else
        {
            printf("#%s\n", argv[i]); 
        }
        yyin= pf;
        yyparse();
        fclose(pf);
    }
    return 0;
}
