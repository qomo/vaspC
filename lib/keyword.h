#ifndef _KEYWORD_H_
#define _KEYWORD_H_

#include "hash.h"
#include <stdio.h>

extern int keyword_lineno; /* from lexer */
extern FILE *keyword_in;
extern int keyword_parse();
extern int keyword_lex();

enum KEYWORD_TYPE
{
    TYPE_BOOL,
    TYPE_BOOL_LIST,
    TYPE_INT,
    TYPE_INT_LIST,
    TYPE_FLOAT,
    TYPE_FLOAT_LIST,
    TYPE_STR,
};

typedef struct
{
    HASH* table;
} KEYWORD;

KEYWORD* KEYWORD_New();
void KEYWORD_Free();
void* KEYWORD_Set(KEYWORD* keyword, char* key, void* value);
void* KEYWORD_Get(KEYWORD* keyword, char* key);
void KEYWORD_Read(KEYWORD* keyword, FILE* pf);
#endif

