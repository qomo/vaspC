
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

void* Pointer_Malloc(void* obj, size_t nbytes)
{
    void* ret= malloc(nbytes);
    if (ret==NULL)
    {
        fprintf(stderr,"Copy_Object: Memory Allocate Error!");
        exit(1);
    }
    else
    {
        memcpy(ret, obj, nbytes);
    }

    return ret;
}
