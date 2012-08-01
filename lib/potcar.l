%option prefix="potcar_"
%option outfile="potcar.lex.c"
%option noyywrap nodefault yylineno
%x SKIP ARG_FLOAT ARG_BOOL ARG_INT
%x ARG_VRHFIN ARG_TITEL ARG_LEXCH

%{
#include "potcar.h"
#include "potcar.tab.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
%}

EXP ([Ee][-+]?[0-9]+)

%%
<INITIAL>"End of Dataset" {return COUNT;}

 /*integer number*/
<INITIAL>"IUNSCR"|"ICORE" {
    potcar_lval.s=malloc(sizeof(char)*(strlen(potcar_text)+1));
    if (potcar_lval.s==NULL)
    {
        fprintf(stderr, "Memory Allocate Error!");
        exit(1);
    }
    else
    {
        strncpy(potcar_lval.s, potcar_text, strlen(potcar_text));
        potcar_lval.s[strlen(potcar_text)]='\0';
    }
    BEGIN ARG_INT;
    return LABEL;
}

<ARG_INT>[0-9]+ {
     potcar_lval.i=atoi(potcar_text);
     BEGIN SKIP;
     return INT;
}

<ARG_INT>"=" {return potcar_text[0];}

 /*float number*/
<INITIAL>"EATOM"|"RPACOR"|"POMASS"|"ZVAL"|"RCORE"|"RWIGS"|"ENMAX"|"ENMIN"|"EAUG"|"DEXC"|"RMAX"|"RAUG"|"RDEP"|"RDEPT"|"QCUT"|"QGAM" {
    potcar_lval.s=malloc(sizeof(char)*(strlen(potcar_text)+1));
    if (potcar_lval.s==NULL)
    {
        fprintf(stderr, "Memory Allocate Error!");
        exit(1);
    }
    else
    {
        strncpy(potcar_lval.s, potcar_text, strlen(potcar_text));
        potcar_lval.s[strlen(potcar_text)]='\0';
    }
    BEGIN ARG_FLOAT;
    return LABEL;
}

<ARG_FLOAT>[-+]?[0-9]+{EXP}|[-+]?[0-9]+"."[0-9]*{EXP}?|[-+]?"."[0-9]+{EXP}? {
     potcar_lval.d=atof(potcar_text);
     BEGIN SKIP;
     return FLOAT;
}

<ARG_FLOAT>"=" {return potcar_text[0];}

 /*boolean value*/
<INITIAL>"LULTRA"|"LCOR"|"LPAW" {
    potcar_lval.s=malloc(sizeof(char)*(strlen(potcar_text)+1));
    if (potcar_lval.s==NULL)
    {
        fprintf(stderr, "Memory Allocate Error!");
        exit(1);
    }
    else
    {
        strncpy(potcar_lval.s, potcar_text, strlen(potcar_text));
        potcar_lval.s[strlen(potcar_text)]='\0';
    } 
    BEGIN ARG_BOOL;
    return LABEL;
}

<ARG_BOOL>"T"|"F" {
     if (potcar_text[0]=='T')
        potcar_lval.b=true;
     else
        potcar_lval.b=false;
     BEGIN SKIP;
     return BOOL;
}

<ARG_BOOL>"=" {return potcar_text[0];}

 /*VRHFIN*/
<INITIAL>"VRHFIN" {
    potcar_lval.s=malloc(sizeof(char)*(strlen(potcar_text)+1));
    if (potcar_lval.s==NULL)
    {
        fprintf(stderr, "Memory Allocate Error!");
        exit(1);
    }
    else
    {
        strncpy(potcar_lval.s, potcar_text, strlen(potcar_text));
        potcar_lval.s[strlen(potcar_text)]='\0';
    } 
    BEGIN ARG_VRHFIN;
    return LABEL;
}

<ARG_VRHFIN>[a-zA-Z0-9]+ {
    potcar_lval.s=malloc(sizeof(char)*(strlen(potcar_text)+1));
    if (potcar_lval.s==NULL)
    {
        fprintf(stderr, "Memory Allocate Error!");
        exit(1);
    }
    else
    {
        strncpy(potcar_lval.s, potcar_text, strlen(potcar_text));
        potcar_lval.s[strlen(potcar_text)]='\0';
    } 
    return STR;
}

<ARG_VRHFIN>"=" {return potcar_text[0];}


 /*TITEL*/
<INITIAL>"TITEL" {
    potcar_lval.s=malloc(sizeof(char)*(strlen(potcar_text)+1));
    if (potcar_lval.s==NULL)
    {
        fprintf(stderr, "Memory Allocate Error!");
        exit(1);
    }
    else
    {
        strncpy(potcar_lval.s, potcar_text, strlen(potcar_text));
        potcar_lval.s[strlen(potcar_text)]='\0';
    } 
    BEGIN ARG_TITEL;
    return LABEL;
}

<ARG_TITEL>[a-zA-Z0-9_]+ {
    potcar_lval.s=malloc(sizeof(char)*(strlen(potcar_text)+1));
    if (potcar_lval.s==NULL)
    {
        fprintf(stderr, "Memory Allocate Error!");
        exit(1);
    }
    else
    {
        strncpy(potcar_lval.s, potcar_text, strlen(potcar_text));
        potcar_lval.s[strlen(potcar_text)]='\0';
    } 
    return STR;
}

<ARG_TITEL>"=" {return potcar_text[0];}

 /*LEXCH*/
<INITIAL>"LEXCH" {
    potcar_lval.s=malloc(sizeof(char)*(strlen(potcar_text)+1));
    if (potcar_lval.s==NULL)
    {
        fprintf(stderr, "Memory Allocate Error!");
        exit(1);
    }
    else
    {
        strncpy(potcar_lval.s, potcar_text, strlen(potcar_text));
        potcar_lval.s[strlen(potcar_text)]='\0';
    } 
    BEGIN ARG_LEXCH;
    return LABEL;
}

<ARG_LEXCH>[a-zA-Z0-9_]+ {
    potcar_lval.s=malloc(sizeof(char)*(strlen(potcar_text)+1));
    if (potcar_lval.s==NULL)
    {
        fprintf(stderr, "Memory Allocate Error!");
        exit(1);
    }
    else
    {
        strncpy(potcar_lval.s, potcar_text, strlen(potcar_text));
        potcar_lval.s[strlen(potcar_text)]='\0';
    } 
    return STR;
}

<ARG_LEXCH>"=" {return potcar_text[0];}

 /*common*/
<*>[\n;] {BEGIN INITIAL; return EOL;}
<*>. {}
<*><<EOF>> {return END;}
%%
