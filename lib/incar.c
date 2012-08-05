#include "keyword.h"
#include "incar.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define INCAR_TABLE_SIZE 500

INCAR* INCAR_New()
{
    INCAR* incar= malloc(sizeof(INCAR));
    if (incar==NULL)
    {
        fprintf(stderr, "INCAR_New: Memory Allocate Error!");
        exit(1);
    }

    fold_set(3,INCAR_TABLE_SIZE);
    incar->table= HASH_New(INCAR_TABLE_SIZE, fold, equal_str);
    return incar;
}

void INCAR_Free(INCAR* incar)
{
    if (incar==NULL)return;
    HASH_Free(incar->table);
    free(incar);
}

void* INCAR_Set(INCAR* incar, char* key, void* value)
{
    void* ret= HASH_Set(incar->table, key, value);
    return ret;
}

void* INCAR_Get(INCAR* incar, char* key)
{
    KEY_VALUE *key_value= HASH_Lookup(incar->table, key);
    return key_value->value;
}

void INCAR_Read(INCAR* incar, KEYWORD* keyword, FILE* pf)
{
    if (incar==NULL||pf==NULL) return;

    if (pf==stdin)
    {
        incar_parse(incar, keyword);
    }
    else
    {
        incar_in=pf;
        incar_parse(incar, keyword);
    }
}

void INCAR_Default(INCAR* incar)
{
    char* SYSTEM= "unknown system";
    INCAR_Set(incar, "SYSTEM", POINTER_MALLOC( SYSTEM, char, strlen(SYSTEM)+1));

    int ISTART= 1;
    INCAR_Set(incar, "ISTART", POINTER_MALLOC( &ISTART, int, 1));

}

void incar_error(char *s, ...)
{
    va_list ap;
    va_start(ap, s);
    
    fprintf(stderr, "%d: error: ", incar_lineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}
