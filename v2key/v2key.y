%{
#include "v2key.h"
#include <string.h>
%}

%union{
    char* s;
}

%token <s> VAR

%%
stmt: 
    | stmt VAR VAR VAR {
        char* key= $2;
        char* type= $3;
        char* count= $4;
        if (strcmp(type,"L")==0&&strcmp(count,"1")==0)
        {
            printf("%12s = %12s\n", key, "BOOL");
        }
        else if (strcmp(type,"L")==0&&strcmp(count,"1")!=0)
        {
            printf("%12s = %12s\n", key, "BOOL_LIST");
        }
        else if (strcmp(type,"I")==0&&strcmp(count,"1")==0)
        {
            printf("%12s = %12s\n", key, "INT");
        }
        else if (strcmp(type,"I")==0&&strcmp(count,"1")!=0)
        {
            printf("%12s = %12s\n", key, "INT_LIST");
        }
        else if (strcmp(type,"F")==0&&strcmp(count,"1")==0)
        {
            printf("%12s = %12s\n", key, "FLOAT");
        }
        else if (strcmp(type,"F")==0&&strcmp(count,"1")!=0)
        {
            printf("%12s = %12s\n", key, "FLOAT_LIST");
        }
        else if (strcmp(type,"S")==0)
        {
            printf("%12s = %12s\n", key, "STR");
        }
        else
        {
            printf("ERRORERRORERRORERRORERRORERROR\n", key);
            printf("%s\n", key);
            printf("%s\n", type);
            printf("%s\n", count);
            printf("ERRORERRORERRORERRORERRORERROR\n", key);
            YYABORT;
        }
    }
;
%%
