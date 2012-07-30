#ifndef _HASH_H_
#define _HASH_H_

#include <stdbool.h>
#include <string.h>

typedef struct
{
    char *key;
    void *value;
} KEY_VALUE;

typedef struct
{
    int size;
    int (*func)(char*);  
    bool   (*equal)(char*, char*);
    KEY_VALUE *table;
} HASH;

HASH* HASH_New(int size, int (*func)(char*), bool (*equal)(char*,char*));
void HASH_Free(HASH* hash);
KEY_VALUE* HASH_Lookup(HASH* hash, char* key);
void* HASH_Set(HASH* hash, char* key, void* value, size_t nbyte);
void* HASH_Get(HASH *hash, char *key);

/*util*/
void fold_set(int length, int mod);
int fold(char* key);
bool equal_str(char *str1, char*str2);
int base36(char* text);

#endif
