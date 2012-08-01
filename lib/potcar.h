#ifndef _POTCAR_H_
#define _POTCAR_H_

#include "hash.h"
#include <stdio.h>


extern int potcar_lineno; /* from lexer */
extern FILE *potcar_in;
extern int potcar_parse();
extern int potcar_lex();

typedef struct
{
    HASH* table;
} POTCAR;

POTCAR* POTCAR_New();
void POTCAR_Free(POTCAR* pot);

void* POTCAR_Set(POTCAR* pot, char* key, void* value);
void* POTCAR_Get(POTCAR *pot, char *key);
int File_Count_POTCAR(FILE* pf);

POTCAR** POTCAR_New_Array_From_File( FILE* pf, int* npot);
void POTCAR_Free_Array(POTCAR** pot_array, int npos);
#endif
