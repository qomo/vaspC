%option prefix="incar_"
%option outfile="incar.lex.c"
%option noyywrap nodefault yylineno
%x ARG_BOOL1 ARG_INT1 ARG_FLOAT1 ARG_STR1 
%x ARG_BOOL_LIST ARG_INT_LIST ARG_FLOAT_LIST
%x SKIP

%{
#include "util.h"
#include "incar.h"
#include "incar.tab.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define YY_DECL int yylex( KEYWORD *keyword)
%}

 /* float exponent */
EXP ([Ee][-+]?[0-9]+)

%%

 /*category*/

<INITIAL>[a-zA-Z0-9]+[ \t]*= {
    char* pch= strtok(incar_text, " \t=");
    incar_lval.s= malloc(sizeof(char)*(strlen(pch)+1));
    if (incar_lval.s==NULL)
    {
        fprintf(stderr,"Memory Allocate Error!");
        exit(1);
    }
    strncpy(incar_lval.s,pch,strlen(pch));
    incar_lval.s[strlen(pch)]='\0';

    enum KEYWORD_TYPE* type= KEYWORD_Get(keyword, incar_lval.s); 
    if (*type==TYPE_BOOL)
    {
        BEGIN ARG_BOOL1;
        return  LABEL;
    }
    else if (*type==TYPE_BOOL_LIST) 
    {
        BEGIN ARG_BOOL_LIST;
        return  LABEL_LIST;
    } 
    else if (*type==TYPE_INT)
    {
        BEGIN ARG_INT1;
        return  LABEL;
    }
    else if (*type==TYPE_INT_LIST)
    {
        BEGIN ARG_INT_LIST;
        return  LABEL_LIST;
    }
    else if (*type==TYPE_FLOAT)
    {
        BEGIN ARG_FLOAT1;
        return  LABEL;
    }
    else if (*type==TYPE_FLOAT_LIST)
    {
        BEGIN ARG_FLOAT_LIST;
        return  LABEL_LIST;
    }
    else if (*type==TYPE_STR)
    {
        BEGIN ARG_STR1;
        return  LABEL;
    }

}

 /*BOOL*/
<ARG_BOOL1>"T" {
     incar_lval.b=true;
     BEGIN SKIP;
     return BOOL;
}

<ARG_BOOL1>"F" {
     incar_lval.b=false;
     BEGIN SKIP;
     return BOOL;
}

 /*BOOL_LIST*/
<ARG_BOOL_LIST>"T" {
     incar_lval.b=true;
     return BOOL;
}

<ARG_BOOL_LIST>"F" {
     incar_lval.b=false;
     return BOOL;
}
<ARG_BOOL_LIST>[^[:space:]#\n;] {BEGIN SKIP;}


 /*INT*/
<ARG_INT1>[0-9]+ {
    incar_lval.i= atoi(incar_text);
    BEGIN SKIP;
    return INT;
}

 /*INT_LIST*/
<ARG_INT_LIST>[0-9]+ {
    incar_lval.i= atoi(incar_text);
    return INT;
}

<ARG_INT_LIST>[^[:space:]#\n;] {BEGIN SKIP;}

 /*FLOAT*/
<ARG_FLOAT1>[-+]?[0-9]+{EXP}?|[-+]?[0-9]+"."[0-9]*{EXP}?|[-+]?"."[0-9]+{EXP}? {
     incar_lval.d=atof(incar_text);
     BEGIN SKIP;
     return FLOAT;
}

 /*FLOAT_LIST*/
<ARG_FLOAT_LIST>[-+]?[0-9]+{EXP}?|[-+]?[0-9]+"."[0-9]*{EXP}?|[-+]?"."[0-9]+{EXP}? {
     incar_lval.d=atof(incar_text);
     return FLOAT;
}
<ARG_FLOAT_LIST>[^[:space:]#\n;] {BEGIN SKIP;}

 /*STR*/
<ARG_STR1>[^#;\n=[:space:]][^#;\n=]+[^#;\n=[:space:]] {
    incar_lval.s= malloc(sizeof(char)*(strlen(incar_text)+1));
    if (incar_lval.s==NULL)
    {
        fprintf(stderr,"Memory Allocate Error!");
        exit(1);
    }
    strncpy(incar_lval.s, incar_text, strlen(incar_text));
    incar_lval.s[strlen(incar_text)]='\0';
    BEGIN SKIP;
    return STR;
}

<*>"#"   {BEGIN SKIP;}
<*>[\n;] {BEGIN INITIAL; return EOL;}
<*>. {}
%%
