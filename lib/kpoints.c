#include "kpoints.h"
#include "kp_mesh.h"
#include "line.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

#define STR_LEN 512

KPOINTS_GRID* KPOINTS_GRID_New()
{
    KPOINTS_GRID* kp= malloc(sizeof(KPOINTS_GRID));
    if (kp==NULL)
    {
        fprintf(stderr, "KPOINTS_GRID_New: Memeory Allocate Error.\n");
        exit(1);
    }
    kp->type= TYPE_GRID;
    kp->comment= NULL;
    kp->ngrid= 0;
    kp->isRec= true;
    kp->pt= NULL;
    kp->wt= NULL;

    return kp;
}

KPOINTS_MESH* KPOINTS_MESH_New()
{
    int i;

    KPOINTS_MESH* kp= malloc(sizeof(KPOINTS_MESH));
    if (kp==NULL)
    {
        fprintf(stderr, "KPOINTS_MESH_New: Memory Allocate Error.");
        exit(1);
    }

    kp->type= TYPE_MESH;
    kp->comment= NULL;
    kp->isGamma=false;
    for (i=0; i<3; i++)
    {
        kp->nmesh[i]=0;
        kp->shift[i]=0;
    }

    return kp;
}

KPOINTS_LINE* KPOINTS_LINE_New()
{
    KPOINTS_LINE* kp= malloc(sizeof(KPOINTS_LINE));
    if (kp==NULL)
    {
        fprintf(stderr, "KPOINTS_LINE_New: Memroy Allocate Error!\n");
        exit(1);
    }

    kp->type   = TYPE_LINE; 
    kp->comment= NULL;
    kp->ngrid  = 0;
    kp->isRec  = true; 
    kp->pt     = NULL;
    kp->mark   = NULL;
    return kp;
}

KPOINTS* KPOINTS_New(const enum KP_TYPE type)
{
    KPOINTS* kp =NULL;   
    if (type==TYPE_GRID)
    {
        kp= (KPOINTS*) KPOINTS_GRID_New(); 
    }
    else if (type == TYPE_MESH)
    {
        kp= (KPOINTS*) KPOINTS_MESH_New(); 
    }
    else if (type== TYPE_LINE)
    {
        kp= (KPOINTS*) KPOINTS_LINE_New(); 
    }
    return kp;
}

void KPOINTS_GRID_Free(KPOINTS_GRID* kp)
{
    if (kp==NULL) return;
    if (kp->comment!=NULL) free(kp->comment);
    if (kp->pt!=NULL) free(kp->pt);
    if (kp->wt!=NULL) free(kp->wt);
    free(kp);
}

void KPOINTS_MESH_Free(KPOINTS_MESH* kp)
{
    if (kp==NULL) return;
    if (kp->comment!=NULL) free(kp->comment);
    free(kp);
}

void KPOINTS_LINE_Free(KPOINTS_LINE* kp)
{
    int i;
    if (kp==NULL) return;
    if (kp->comment!=NULL) free(kp->comment);
    if (kp->pt!=NULL) free(kp->pt);
    for (i=0; i<kp->ngrid; i++)
    {
        if (kp->mark[i]!=NULL) free(kp->mark[i]);
    }
    free(kp->mark);
    free(kp);
}

void KPOINTS_Free(KPOINTS* kp)
{
    if (kp==NULL) return;
    if (kp->type==TYPE_GRID) 
    {
        KPOINTS_GRID_Free((KPOINTS_GRID*)kp);    
    }
    else if (kp->type==TYPE_GRID)
    {
        KPOINTS_MESH_Free((KPOINTS_MESH*)kp);
    }
    else if (kp->type==TYPE_LINE)
    {
        KPOINTS_LINE_Free((KPOINTS_LINE*)kp);
    }
}

enum KP_TYPE KPOINTS_File_Type(FILE* pf)
{
    int line_count;  
    char line[STR_LEN];
    char* pch;

    if (pf==NULL) 
    {
        fprintf(stderr, "KPOINTS_File_type: File Pointer pf is a null pointer.\n");
        exit(1);
    }

    /*1st line -- comment */
    line_count=0;
    READLINE(line_count,line,STR_LEN,pf);

    /*2nd line*/
    line_count=0;
    READLINE(line_count,line,STR_LEN,pf);
    pch= strtok(line," \t");
    if (atoi(pch)==0)
        return TYPE_MESH;

    /*3rd line*/
    line_count=0;
    READLINE(line_count,line,STR_LEN,pf);
    if (line[0]=='L'||line[0]=='l') 
        return TYPE_LINE;
    else
        return TYPE_GRID;
}

void KPOINTS_MESH_Read(KPOINTS_MESH* mesh, FILE* pf)
{
    if (mesh==NULL||pf==NULL) return;
    
    kp_mesh_in= pf;
    kp_mesh_parse(mesh);
}

void kp_mesh_error(char *s, ...)
{
    va_list ap;
    va_start(ap, s);
    
    fprintf(stderr, "%d: error: ", kp_mesh_lineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}

