%option prefix="outcar_"
%option outfile="outcar.lex.c"
%option noyywrap nodefault yylineno
%x ARG_FLOAT1 ARG_STR_LIST SKIP

%{
#include "outcar.h"
#include "outcar.tab.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
%}

EXP ([Ee][-+]?[0-9]+)

%%

 /*float*/
<INITIAL>"E-fermi" {
    char* pch= strtok(outcar_text, " \t:");
    outcar_lval.s= malloc(sizeof(char)*(strlen(pch)+1));
    if (outcar_lval.s==NULL)
    {
        fprintf(stderr,"Memory Allocate Error!");
        exit(1);
    }
    strncpy(outcar_lval.s,pch,strlen(pch));
    outcar_lval.s[strlen(pch)]='\0';
    BEGIN ARG_FLOAT1;
    return LABEL;
}

<ARG_FLOAT1>[-+]?[0-9]+{EXP}?|[-+]?[0-9]+"."[0-9]*{EXP}?|[-+]?"."[0-9]+{EXP}? {
     outcar_lval.d=atof(outcar_text);
     BEGIN INITIAL;
     return FLOAT;
}

 /*str*/
<INITIAL>"TITEL" {
    char* pch= strtok(outcar_text, " \t:");
    outcar_lval.s= malloc(sizeof(char)*(strlen(pch)+1));
    if (outcar_lval.s==NULL)
    {
        fprintf(stderr,"Memory Allocate Error!");
        exit(1);
    }
    strncpy(outcar_lval.s,pch,strlen(pch));
    outcar_lval.s[strlen(pch)]='\0';
    BEGIN ARG_STR_LIST;
    return LABEL_LIST;
}

<ARG_STR_LIST>[a-zA-Z0-9_]+ {
    outcar_lval.s= malloc(sizeof(char)*(strlen(outcar_text)+1));
    if (outcar_lval.s==NULL)
    {
        fprintf(stderr,"Memory Allocate Error!");
        exit(1);
    }
    strncpy(outcar_lval.s, outcar_text, strlen(outcar_text));
    outcar_lval.s[strlen(outcar_text)]='\0';
    return STR;
}

<*>\n {BEGIN INITIAL; return EOL;}
<*>.  {}

%%
