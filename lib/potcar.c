#include "potcar.h"
#include "list.h"
#include "line.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_LEN 1024

void _POTCAR_Init(POTCAR** ppot)
{
    if ((*ppot)!=NULL)
        return;
    else
        _POTCAR_Free(ppot); 
}

void _POTCAR_Free(POTCAR** ppot)
{
    /*Argument*/
    if (*ppot==NULL) return;
    free(*ppot);
    *ppot=NULL;
}

int _POTCAR_Read(POTCAR** ppot, FILE* pf)
{
    /* Temp Variable */
    int i;
    char cdump[STRING_LEN];
    char tag[2][STRING_LEN];
    double val[2];

    int nlist=0;
    int nlist_zval=0;
    int nlist_rwigs=0;
    int nlist_enmax=0;
    int nlist_enmin=0;
    LIST* node=NULL;
    LIST* list_zval=NULL;
    LIST* list_rwigs=NULL;
    LIST* list_enmax=NULL;
    LIST* list_enmin=NULL;

    LIST_Init(list_zval);
    LIST_Init(list_rwigs);
    LIST_Init(list_enmax);
    LIST_Init(list_enmin);

    while(readline(cdump,STRING_LEN,pf))
    {
        sscanf(cdump, "%10s%*1s%9lf%*1s%8s%*1s%9lf",tag[0],&val[0],tag[1],&val[1]);

        if (strcmp(tag[0],"ENMAX")==0)
        {
            LIST_Append(list_enmax, &(val[0]), sizeof(val[0])); 
            nlist_enmax++;
        }


        if (strcmp(tag[1],"ZVAL")==0)
        {
            LIST_Append(list_zval, &(val[1]), sizeof(val[1])); 
            nlist_zval++;
        } 
        else if (strcmp(tag[1],"RWIGS")==0)
        {
            LIST_Append(list_rwigs, &(val[1]), sizeof(val[1])); 
            nlist_rwigs++;
        }
        else if (strcmp(tag[1],"ENMIN")==0)
        {
            LIST_Append(list_enmin, &(val[1]), sizeof(val[1])); 
            nlist_enmin++;

        }
    }
    
    /* Check Parsing*/
    if (  (nlist_zval!=nlist_rwigs) 
        ||(nlist_rwigs!=nlist_enmax)
        ||(nlist_enmax!=nlist_enmin))
    {
        fprintf(stderr,"Parsing Missing\n\n");

        fprintf(stderr,"N of ZVAL = %3d\n", nlist_zval);
        fprintf(stderr,"N of RWIGS= %3d\n", nlist_rwigs);
        fprintf(stderr,"N of ENMIN= %3d\n", nlist_enmax);
        fprintf(stderr,"N of ENMAX= %3d\n", nlist_enmin);

        exit(1);
    }
    else
    {
        nlist= nlist_zval;
    }

    *ppot=malloc(sizeof(POTCAR)*nlist);
    if (ppot==NULL)
    {
        fprintf(stderr, "POTCAR_Read: Memory Allocate for ppot error.");
        exit(1);
    }
    else
    {
        for (i=0; i<nlist; i++)
        {
            node= LIST_Item(list_zval,i);
            (*ppot)[i].zval= *((double*)(node->val));

            node= LIST_Item(list_rwigs,i);
            (*ppot)[i].rwigs= *((double*)(node->val));

            node= LIST_Item(list_enmax,i);
            (*ppot)[i].enmax= *((double*)(node->val));

            node= LIST_Item(list_enmin,i);
            (*ppot)[i].enmin= *((double*)(node->val));
        }
    }


    /*Memory Allocate POTCAR*/

    LIST_Free(list_zval);
    LIST_Free(list_rwigs);
    LIST_Free(list_enmax);
    LIST_Free(list_enmin);

    return nlist;
}
