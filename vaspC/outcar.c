#include "outcar.h"
#include "line.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void _OUTCAR_Init(OUTCAR** pout)
{
    if ((*pout)!=NULL) _OUTCAR_Free(pout);
    *pout=malloc(sizeof(OUTCAR));
    if ((*pout)==NULL)
    {
        fprintf(stderr, "OUTCAR_Init: Memory Allocate Error.\n");
        exit(1);
    }
    (*pout)->nfermi=0;
    (*pout)->fermi=NULL;
}

void _OUTCAR_Free(OUTCAR** pout)
{
    if ((*pout)==NULL) return;
    if ((*pout)->fermi!=NULL) free((*pout)->fermi);
    free(*pout);
    *pout=NULL;
}

void OUTCAR_Read(OUTCAR* out,FILE* pf)
{
    int i;
    LIST* node;
    LIST* list_fermi=NULL;
    char cdump[1024];
    char tag[1024];
    double value;

    LIST_Init(list_fermi);

    while(readline(cdump, 1024, pf))
    {
        sscanf(cdump,"%9s%*1s%9lf",tag,&value);
        if (strcmp(tag,"E-fermi")!=0)
            continue;        
        else
        {
            LIST_Append(list_fermi,&value,sizeof(double));     
            out->nfermi++;  
        }
    }

    out->fermi= malloc(out->nfermi*sizeof(OUTCAR));
    if (out->fermi ==NULL)
    {
        fprintf(stderr, "OUTCAR_Read: Memory Allocate Error.");
        exit(1);
    }

    for (i=0; i<out->nfermi; i++)
    {
        node= LIST_Item(list_fermi,i);
        out->fermi[i]= *((double*)(node->val));
    }

    LIST_Free(list_fermi);
}
