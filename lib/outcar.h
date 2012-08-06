#ifndef _OUTCAR_H_
#define _OUTCAR_H_

#include "list.h"
#include "hash.h"
#include <stdio.h>

extern int outcar_lineno; /* from lexer */
extern FILE *outcar_in;
extern int outcar_parse();
extern int outcar_lex();

typedef struct
{
    HASH* table; 
} OUTCAR;

OUTCAR* OUTCAR_New();
void OUTCAR_Free(OUTCAR* out);
void* OUTCAR_Set(OUTCAR* out, char* key, void* value);
void* OUTCAR_Get(OUTCAR* out, char* key);
void OUTCAR_Read(OUTCAR* out, FILE* pf);
#endif 
