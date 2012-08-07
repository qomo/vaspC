/**
    Date: 2012-04-16
    Author: Zhi-Quan Huang
*/
#ifndef _READLINE_H_
#define _READLINE_H_

#define READLINE(line_count,string,string_len,file) do{\
    line_count++; \
    if(!readline(string, string_len, file))\
        return line_count;\
    }while(0)

#include <stdio.h>
char* readline(char* str, int num, FILE* stream);
int nitems(const char* str, const char* delimiters);
char *rstrip(char* str);
#endif
