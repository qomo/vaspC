#include "outcar.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define OUTCAR_TABLE_SIZE 500

OUTCAR* OUTCAR_New()
{
    OUTCAR* out= malloc(sizeof(OUTCAR));
    if (out==NULL)
    {
        fprintf(stderr, "Memory Allocate Error!"); 
        exit(1);
    } 

    fold_set(3,OUTCAR_TABLE_SIZE);
    out->table= HASH_New(OUTCAR_TABLE_SIZE, fold, equal_str);

    return out;
}

void OUTCAR_Free(OUTCAR* out)
{
    if (out==NULL) return;
    HASH_Free(out->table);
    free(out);
}

void* OUTCAR_Set(OUTCAR* out, char* key, void* value)
{
    void* ret= HASH_Set(out->table, key, value);
    return ret;
}

void* OUTCAR_Get(OUTCAR* out, char* key)
{
    KEY_VALUE *key_value= HASH_Lookup(out->table, key);
    return key_value->value;
}

void OUTCAR_Read(OUTCAR* out,FILE* pf)
{
    if (out==NULL||pf==NULL) return;
    if (pf==stdin)
    {
        outcar_parse(out);  
    }
    else
    {
        outcar_in= pf;
        outcar_parse(out);
    }
}

void outcar_error(char *s, ...)
{
    va_list ap;
    va_start(ap, s);
    
    fprintf(stderr, "%d: error: ", outcar_lineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}
