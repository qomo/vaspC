#include "kpoints.h"
#include "line.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STR_LEN 512

void _KPOINTS_Init(KPOINTS** pkp)
{
    int i;
    if ((*pkp)!=NULL) _KPOINTS_Free(pkp);

    *pkp= malloc(sizeof(KPOINTS));
    if ((*pkp)==NULL)
    {
        fprintf(stderr,"KPOINTS_Init: Malloc Error.\n");        
        exit(1);
    }

    (*pkp)->type=KP_UNKNOWN;
    (*pkp)->comment=NULL;
    (*pkp)->ngrid= 0;
    (*pkp)->isRev=true;
    (*pkp)->pt=NULL;
    (*pkp)->wt=NULL;
    (*pkp)->isGamma=false;
    for (i=0; i<3; i++) (*pkp)->nmesh[i]=0;
    for (i=0; i<3; i++) (*pkp)->shift[i]=0;
    (*pkp)->mark= NULL;
}

void _KPOINTS_Free(KPOINTS** pkp)
{
    int i;
    int total=1;

    if ((*pkp)->comment!=NULL) 
        free((*pkp)->comment);

    if ((*pkp)->pt!=NULL) 
        free((*pkp)->pt);

    if ((*pkp)->wt!=NULL) 
        free((*pkp)->wt);

    if ( ((*pkp)->type==KP_LINE) && ((*pkp)->mark!=NULL))
    {
        for (i=0; i<3; i++)
            total *= (*pkp)->nmesh[i];
        for (i=0; i<total; i++)
        {
            free((*pkp)->mark[i]);
        }
        free((*pkp)->mark);
    }
    free((*pkp));
    *pkp=NULL;
}

void KPOINTS_Read(KPOINTS* kp, FILE* pf)
{
    int iline=0;
    char cdump[STR_LEN];
    if ((*pkp)==NULL )
    {
        fprintf(stderr,"KPOINTS_Read: *pkp is a null pointer.\n");
        exit(1);
    }     
    else if (pf==NULL)
    {
        fprintf(stderr,"KPOINTS_Read: pf is a null pointer.\n");
        exit(1);
    }     

    READ_LINE(iline, cdump, STR_LEN, pf);
    if (kp->comment)
    {
        free(kp->comment);
        kp->comment=NULL;
    }
    kp->comment=malloc(sizeof(char*(strlen(cdump)+1)));
    if (!kp->comment)
    {
        fprintf(stderr, "KPOINTS: Memory Allocate Error.\n");
        exit(1);
    }
    strncpy(kp->comment,cdump,strlen(cdump));

    READ_LINE(iline, cdump, STR_LEN, pf);
    
    if (sscanf(cdump,"%d",&(kp->ngrid))!=1)
    {
        fprintf(stderr,"KPOINTS_Read: %d error\n", iline);
        exit(1); 
    }

    if (kp->ngrid == 0)
    {
        /*Auto Mesh*/
        READ_LINE(iline, cdump, STR_LEN, pf);
         
    }
    else
    {
        
    }



   
}
