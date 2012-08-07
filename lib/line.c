#include "line.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char* readline(char* str, int num, FILE* stream)
{
    char buf[1024]; 
    char *p=NULL;
    char* ret= NULL;
    
    /*Check Arguemnts*/
    if (str == NULL || stream == NULL) return NULL;

    ret= fgets(str,num,stream);
    if (ret)
    {
        p=strchr(str,'\n');
        if (p)
        {
            *p='\0';
        }
        else
        {
            /*Out of size of str, skipping*/
            do{
                if (!fgets(buf, 1024, stream)) break;
                p=strchr(buf,'\n');
            }while(!p);
        }
    }
    return ret;
}

int nitems(const char* const str, const char* const delimiters)
{
    char* sdump=NULL;
    char* pch= NULL;
    int ret=0;

    sdump= (char*)malloc(sizeof(char)*(strlen(str)+1));
    if (!sdump) return -1;
    memcpy(sdump, str, sizeof(char)*(strlen(str)+1));

    pch= strtok(sdump, delimiters);
    while (pch!=NULL)
    {
        ret++;
        pch= strtok(NULL, delimiters);
    }
    free(sdump);
    return ret;
}

char *rstrip(char* str)
{
    int i;
    const int str_len= strlen(str);
    for (i=str_len-1; i>=0; i--)
    {
        if (str[i]==' ')
            str[i]='\0';
        else if (str[i]=='\t')
            str[i]='\0';
        else
            break;
    }
    return str;
}
