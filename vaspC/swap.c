#include <string.h>

void swap(void* a, void* b, unsigned int byte)
{
    char tmp[byte];
    memcpy(tmp, a, byte);
    memcpy(a, b, byte);
    memcpy(b, tmp, byte);
}
