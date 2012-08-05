#include "hash.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static int ipow( int base, int exp)
{
    int result = 1;
    while (exp)
    {
        if (exp & 1)
            result *= base;
        exp >>= 1;
        base *= base;
    }

    return result;
}

HASH* HASH_New(int size, 
               int (*func)(char*),
               bool (*equal)(char*, char*))
{
    int s; 

    HASH* hash= malloc(sizeof(HASH));
    if (hash==NULL)
    {
        fprintf(stderr,"hash: Memory allocate error.");
        exit(1);
    }

    hash->size= size; 
    hash->func= func;
    hash->equal= equal;

    hash->table=  malloc(sizeof(KEY_VALUE)*(hash->size));
    if (hash->table==NULL)
    {
        fprintf(stderr, "hahs->table: Memory allocate error.");
        exit(1);
    }

    for (s=0; s<hash->size; s++)    
    {
        hash->table[s].key  = NULL;
        hash->table[s].value= NULL;
    }
    return hash;    
}

void HASH_Free(HASH* hash)
{
    int s;

    if (hash==NULL) return;
     
    for (s=0; s<hash->size; s++)  
    {
        if (hash->table[s].key!=NULL)
            free(hash->table[s].key);
        if (hash->table[s].value)
            free(hash->table[s].value);
    }
    free(hash->table);
    free(hash);
}

KEY_VALUE* HASH_Lookup(HASH* hash, char* key)
{
    int address= (hash->func(key))%(hash->size);
    int count= hash->size;
    KEY_VALUE* key_value= &(hash->table[address]);

    while(--count>=0)
    {
        if (key_value->key==NULL)
        {
            key_value->key=malloc(sizeof(char)*(strlen(key)+1));
            if (key_value->key==NULL)
            {
                fprintf(stderr, "Memory Allocate Error.");
                exit(1);
            }
            memcpy(key_value->key, key, strlen(key)+1);
            return key_value;
        }
        else if (hash->equal(key, key_value->key))
        {
           return key_value; 
        }
        if (++key_value>=(hash->table+hash->size))
            key_value=hash->table;
    }

    fprintf(stderr, "key=%s\n",key);
    fprintf(stderr, "Out of hash table\n");
    exit(1);
}

void* HASH_Set(HASH* hash, char* key, void* value)
{
    KEY_VALUE *key_value= HASH_Lookup(hash, key);

    if (key_value->value!=NULL) free(key_value->value);

    key_value->value= value;

    return key_value->value;
}

void* HASH_Get(HASH *hash, char *key)
{
    KEY_VALUE *key_value= HASH_Lookup(hash, key);
    return key_value->value;
}

bool equal_str(char* str1, char* str2)
{
    if (strcmp(str1,str2)==0)
        return true;
    else
        return false;
}

int base36(char* text)
{
    int num=0;
    int i;
    for ( i=strlen(text)-1; i>=0; i--)
    {
        const int j= strlen(text)-1-i;
        char c= tolower(text[j]);
        if (isdigit(c))
            num+=(c-48)*((int)(ipow(36,i)));          
        else if (isalpha(c))
            num+=(c-87)*((int)(ipow(36,i)));
        else
        {}
    }
    return num;
}

static int fold_length=0;
static int fold_mod=0;

void fold_set(int length, int mod)
{
    fold_length= length;
    fold_mod   =mod;
}

int fold(char* key)
{
    int ret=0;
    int s;     

    if (fold_length==0||fold_mod==0)   
    {
        fprintf(stderr, "Call fold_set beforce fold function.");
        exit(1);
    }

    for (s=0; s<strlen(key); s+=fold_length)
    {
        char* str= malloc(sizeof(char)*(fold_length+1));
        if (str==NULL)
        {
            fprintf(stderr, "Memory Allocate Error!");
            exit(1);
        }
        else
        {
            strncpy(str, key+s, fold_length);
            str[fold_length]='\0';
            ret+= base36(str);
        }
        free(str);
    }

    return ret%fold_mod;
}

