%option prefix="keyword_"
%option outfile="keyword.lex.c"
%option noyywrap nodefault yylineno
%x ARG SKIP

%{
#include "util.h"
#include "keyword.h"
#include "keyword.tab.h"
#include <stdio.h>
#include <stdlib.h>
%}

%%

<INITIAL>[^[:space:]#\n=]+ {
    keyword_lval.s= malloc(sizeof(char)*(strlen(keyword_text)+1));
    if (keyword_lval.s==NULL)
    {
        fprintf(stderr,"Memory Allocate Error!");
        exit(1);
    }
    strncpy(keyword_lval.s, keyword_text,strlen(keyword_text));
    keyword_lval.s[strlen(keyword_text)]='\0';
    return KEY;   
}


<ARG>"BOOL" {
    BEGIN SKIP;
    return BOOL; 
}

<ARG>"BOOL_LIST" {
    BEGIN SKIP;
    return BOOL_LIST; 
}

<ARG>"INT" {
    BEGIN SKIP;
    return INT; 
}

<ARG>"INT_LIST" {
    BEGIN SKIP;
    return INT_LIST; 
}


<ARG>"FLOAT" {
    BEGIN SKIP;  
    return FLOAT; 
}

<ARG>"FLOAT_LIST" {
    BEGIN SKIP;  
    return FLOAT_LIST; 
}

<ARG>"STR" {
    BEGIN SKIP;  
    return STR; 
}

<INITIAL>"=" {BEGIN ARG; return keyword_text[0];}
<*>"#" {BEGIN SKIP;}
<*>[\n;] {BEGIN INITIAL; return EOL;}
<*>. {}
%%
