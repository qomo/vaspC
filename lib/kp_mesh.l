%option prefix="kp_mesh_"
%option outfile="kp_mesh.lex.c"
%option noyywrap nodefault yylineno
%x NGRID M_G MESH SHIFT SKIP 

%{
#include "kp_mesh.h"
#include "kp_mesh.tab.h"
#include "kpoints.h"
#include "line.h"
#include <stdlib.h>
#include <ctype.h>
static int count=0;
%}

EXP ([Ee][-+]?[0-9]+)

%%

<INITIAL>[^\n]+ {
    char* pch= rstrip(kp_mesh_text);   
    kp_mesh_lval.s= malloc(sizeof(char)*strlen(pch));    
    if (kp_mesh_lval.s==NULL) 
    {
        fprintf(stderr, "Memory Allocate Error!\n");
        exit(1);
    }
    strncpy(kp_mesh_lval.s, pch, strlen(pch));
    kp_mesh_lval.s[strlen(pch)]='\0';
    return STR;
}

<NGRID>[0-9]+ {
    kp_mesh_lval.i= atoi(kp_mesh_text);  
    return INT; 
}

<M_G>[^\n]+ {
    if (kp_mesh_text[0]=='G'||kp_mesh_text[0]=='g')
        kp_mesh_lval.b= true;
    else
        kp_mesh_lval.b= false;
    return  BOOL;
}

<MESH>[0-9]+ {
    kp_mesh_lval.i= atoi(kp_mesh_text);  
    return INT; 
}

<SHIFT>[-+]?[0-9]+{EXP}?|[-+]?[0-9]+"."[0-9]*{EXP}?|[-+]?"."[0-9]+{EXP}? {
    kp_mesh_lval.d= atof(kp_mesh_text);
    return FLOAT;
}

<*>[\n] {
    if (kp_mesh_lineno==2)
    {
        BEGIN NGRID;
        return EOL_COMMENT;
    }
    else if (kp_mesh_lineno==3)
    {
        BEGIN M_G;
        return EOL_NGRID;
    }
    else if (kp_mesh_lineno==4)
    {
        BEGIN MESH;
        return EOL_M_G;
    }
    else if (kp_mesh_lineno==5)
    { 
        BEGIN SHIFT;
        return EOL_MESH;
    }
    else if (kp_mesh_lineno==6)
    {
        BEGIN SKIP;
        return EOL_SHIFT;
    }
    else
    {
        return EOL;
    }
}

<*>.  {}

%%
