%option prefix="kp_grid_"
%option outfile="kp_grid.lex.c"
%option noyywrap nodefault yylineno
%x x_NGRID x_R_C x_GRID x_WT x_SKIP

%{
#include "kp_grid.h"
#include "kp_grid.tab.h"
#include "kpoints.h"
%}

EXP ([Ee][-+]?[0-9]+)

%%

<INITIAL>[^\n]+ {
    char* pch= rstrip(kp_grid_text);   
    kp_grid_lval.s= malloc(sizeof(char)*strlen(pch));    
    if (kp_grid_lval.s==NULL) 
    {
        fprintf(stderr, "Memory Allocate Error!\n");
        exit(1);
    }
    strncpy(kp_grid_lval.s, pch, strlen(pch));
    kp_grid_lval.s[strlen(pch)]='\0';
    return STR;
}

<x_NGRID>[0-9]+ {
    kp_grid_lval.i= atoi(kp_grid_text);
    BEGIN x_SKIP; 
    return INT;    
}

<x_R_C>[^\n]+ {
    char ch= kp_grid_text[0];   
    if (ch=='R'||ch=='r')
        kp_grid_lval.b= true;
    else
        kp_grid_lval.b= false;
    BEGIN x_SKIP;
    return BOOL;
}

<x_GRID>[-+]?[0-9]+{EXP}?|[-+]?[0-9]+"."[0-9]*{EXP}?|[-+]?"."[0-9]+{EXP}? {
    static int count= 0;
    kp_grid_lval.d= atof(kp_grid_text);
    if (++count==3)
    {
        count=0;
        BEGIN x_WT;
    }
    return FLOAT;
} 

<x_WT>[0-9]+ {
    kp_grid_lval.i= atoi(kp_grid_text);
    BEGIN x_SKIP;
    return INT;
}

<*>\n {
    if (kp_grid_lineno==2)
    {
        BEGIN x_NGRID;
        return EOL_COMMENT;
    }
    else if (kp_grid_lineno==3)
    {
        BEGIN x_R_C;
        return EOL_NGRID;
    }
    else if (kp_grid_lineno==4)
    {
        BEGIN x_GRID;
        return EOL_LINE;
    }
    else
    {
        BEGIN x_GRID;
        return EOL_GRID;
    }
}

<*>. {}

%%

