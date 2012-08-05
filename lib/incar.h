#ifndef _INCAR_H_
#define _INCAR_H_

#include "hash.h"
#include "keyword.h"
#include "list.h"
#include <stdio.h>

extern int incar_lineno; /* from lexer */
extern FILE *incar_in;
extern int incar_parse();
extern int incar_lex();

typedef struct
{
    HASH* table;
} INCAR;

INCAR* INCAR_New();
void INCAR_Free(INCAR* incar);
void INCAR_Read(INCAR* incar, KEYWORD* keyword, FILE* pf);
void* INCAR_Set(INCAR* incar, char* key, void* value);
void* INCAR_Get(INCAR* incar, char* key);
#endif
