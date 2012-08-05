%option outfile="v2key.lex.c"
%option noyywrap nodefault yylineno
%x TAG ARG SKIP

%{
#include "v2key.tab.h"
#include <stdlib.h>
#include <string.h>
static int count=0;
%}

%%
<INITIAL>"RDATAB"[ \t]*"(" { count=0; BEGIN ARG;}
<ARG>")"[ \t]*\n { BEGIN INITIAL;}
<ARG>"," {
    count++;
    if (count==3||count==7||count==14){
        BEGIN TAG;
    }
}
<TAG>[^\n& \t,]+ { 
    char *pch= strtok(yytext,"'");
    yylval.s= malloc(sizeof(char)*(strlen(pch)+1));
    if (yylval.s==NULL)
    {
        fprintf(stderr,"Memory Allocate Error!");
        exit(1);
    }
    strncpy(yylval.s, pch, strlen(pch));
    yylval.s[strlen(pch)]='\0';
    BEGIN ARG;
    return VAR;
}
<ARG>"(" { BEGIN SKIP;}
<SKIP>")" { BEGIN ARG;}
<*>.|\n {}
%%
