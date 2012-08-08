%option prefix="kp_line_"
%option outfile="kp_line.lex.c"
%option noyywrap nodefault yylineno
%x x_SKIP x_NGRID x_LINE x_REC x_POINTS x_TAG

%{
#include "kp_line.h"
#include "kp_line.tab.h"
#include "kpoints.h"
#include "line.h"
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
static bool isStart=false;
%}

EXP ([Ee][-+]?[0-9]+)

%%

<INITIAL>[^\n]+ {
    char* pch= rstrip(kp_line_text);   
    kp_line_lval.s= malloc(sizeof(char)*strlen(pch));    
    if (kp_line_lval.s==NULL) 
    {
        fprintf(stderr, "Memory Allocate Error!\n");
        exit(1);
    }
    strncpy(kp_line_lval.s, pch, strlen(pch));
    kp_line_lval.s[strlen(pch)]='\0';
    return STR;
}

<x_NGRID>[0-9]+ {
    kp_line_lval.i= atoi(kp_line_text);
    BEGIN x_SKIP; 
    return INT;    
}

<x_LINE>[^\n]+ {
    char* pch= rstrip(kp_line_text);   
    kp_line_lval.s= malloc(sizeof(char)*strlen(pch));    
    if (kp_line_lval.s==NULL) 
    {
        fprintf(stderr, "Memory Allocate Error!\n");
        exit(1);
    }
    strncpy(kp_line_lval.s, pch, strlen(pch));
    kp_line_lval.s[strlen(pch)]='\0';
    return STR;
}

<x_REC>[a-zA-Z] {
    char ch= kp_line_text[0]; 
    if (ch=='R'||ch=='r')
        kp_line_lval.b= true;
    else
        kp_line_lval.b= false;
    BEGIN x_SKIP;
    return BOOL;
}

<x_POINTS>[-+]?[0-9]+{EXP}?|[-+]?[0-9]+"."[0-9]*{EXP}?|[-+]?"."[0-9]+{EXP}? {
    static int count=0;
    kp_line_lval.d= atof(kp_line_text);
    count++;
    if (count==3)
    {
        isStart= !isStart; 
        count=0;
        BEGIN x_TAG;
    }
    return FLOAT;
}

<x_TAG>[a-zA-Z0-9_]+ {
    char* pch= rstrip(kp_line_text);   
    kp_line_lval.s= malloc(sizeof(char)*strlen(pch));    
    if (kp_line_lval.s==NULL) 
    {
        fprintf(stderr, "Memory Allocate Error!\n");
        exit(1);
    }
    strncpy(kp_line_lval.s, pch, strlen(pch));
    kp_line_lval.s[strlen(pch)]='\0';
    BEGIN x_SKIP;
    return TAG;
}

<*>\n {
    if (kp_line_lineno==2)
    {
        BEGIN x_NGRID;
        return EOL_COMMENT;
    }
    else if (kp_line_lineno==3)
    {
        BEGIN x_LINE;
        return EOL_NGRID;
    }
    else if (kp_line_lineno==4)
    {
        BEGIN x_REC;
        return EOL_LINE;
    }
    else if (kp_line_lineno==5)
    {
        BEGIN x_POINTS;
        return EOL_REC;
    }
    
    if (isStart)
    {
        BEGIN x_POINTS;
        return EOL_POINTS_START;
    }
    else
    {
        BEGIN x_POINTS;
        return EOL_POINTS_END;
    }
}

<*>. {}

%%
