#include "keyword.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#define KEYWORD_TABLE_SIZE 500

KEYWORD* KEYWORD_New()
{
    KEYWORD* keyword= malloc(sizeof(KEYWORD));
    if (keyword==NULL)
    {
        fprintf(stderr, "KEYWORD_New: Memory Allocate Error!");
        exit(1);
    }
    fold_set(3,KEYWORD_TABLE_SIZE);
    keyword->table= HASH_New(KEYWORD_TABLE_SIZE, fold, equal_str);
    return keyword;
}

void KEYWORD_Free(KEYWORD* keyword)
{
    if (keyword==NULL) return;
    HASH_Free(keyword->table);
    free(keyword);
}

void* KEYWORD_Set(KEYWORD* keyword, char* key, void* value)
{
    void* ret= HASH_Set(keyword->table, key, value);
    return ret;
}

void* KEYWORD_Get(KEYWORD* keyword, char* key)
{
    KEY_VALUE *key_value= HASH_Lookup(keyword->table, key);
    return key_value->value;
}

void KEYWORD_Read(KEYWORD* keyword, FILE* pf)
{
    if (keyword==NULL||pf==NULL) return;

    if (pf==stdin)
    {
        keyword_parse(keyword);
    }
    else
    {
        keyword_in=pf;
        keyword_parse(keyword);
    }
}

void keyword_error(char *s, ...)
{
    va_list ap;
    va_start(ap, s);
    
    fprintf(stderr, "%d: error: ", keyword_lineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}
