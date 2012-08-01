#ifndef _UTIL_H_
#define _UTIL_H_

#include <stddef.h>

void* Pointer_Malloc(void* obj, size_t nbytes);

#define POINTER_MALLOC(obj,type,num) (Pointer_Malloc(obj,sizeof(type)*num))

#endif 
