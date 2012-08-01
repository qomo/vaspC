#include "potcar.h"
#include "hash.h"
#include "line.h"
#include "hash.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define STRING_LEN 1024
#define POTCAR_TABLE_SIZE 150

POTCAR* POTCAR_New()
{
    POTCAR* pot=malloc(sizeof(POTCAR));
    if (pot==NULL)
    {
        fprintf(stderr, "Memory Allocate Error.");
        exit(1);
    }
    fold_set(3,POTCAR_TABLE_SIZE);
    pot->table= HASH_New(POTCAR_TABLE_SIZE, fold, equal_str);
    return pot;
}

void POTCAR_Free(POTCAR* pot)
{
    if (pot==NULL) return;
    HASH_Free(pot->table);
    free(pot);
}

void* POTCAR_Set(POTCAR* pot,     
                 char* key, void* value)
{
    void* ret= HASH_Set(pot->table, key, value);
    return ret;
}

void* POTCAR_Get(POTCAR *pot, char *key)
{
    KEY_VALUE *key_value= HASH_Lookup(pot->table, key);
    return key_value->value;
}

int File_Count_POTCAR(FILE* pf)
{
    int count=0;
    fpos_t position;

    if (pf==NULL) return count;
    fgetpos(pf,&position);

    char cdump[STRING_LEN];
    char tag[STRING_LEN];

    while(readline(cdump,STRING_LEN,pf))
    {
        sscanf(cdump, "%10s",tag);
        if (strcmp(tag,"TITEL")==0) count++;
    }

    fsetpos(pf,&position);
    return count;
}

POTCAR** POTCAR_New_Array_From_File( FILE* pf, int* npot)
{
    int i;
    POTCAR** pot_array;

    *npot= File_Count_POTCAR(pf);

    pot_array= malloc(sizeof(POTCAR*)*(*npot));
    if (pot_array==NULL)
    {
        fprintf(stderr, "Memory Allocate Error!");
        exit(1);
    }

    for (i=0; i<(*npot); i++)
        pot_array[i]= POTCAR_New(); 

    if (pf==stdin)
    {
        potcar_parse(pot_array, *npot);
    }
    else
    {
        potcar_in= pf;
        potcar_parse(pot_array, *npot);
    }


    return pot_array;
}

void POTCAR_Free_Array(POTCAR** pot_array, int npos)
{
    int i;
    for ( i=0; i<npos; i++)
    {
        POTCAR_Free(pot_array[i]);
    } 
    free(pot_array);
}

void potcar_error(char *s, ...)
{
    va_list ap;
    va_start(ap, s);
    
    fprintf(stderr, "%d: error: ", potcar_lineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}
