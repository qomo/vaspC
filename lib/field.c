#include "poscar.h"
#include "line.h"
#include "field.h"
#include "index.h"

#include <stdlib.h>
#include <stdio.h>

void _SCALAR3D_Init(SCALAR3D **psca)
{
    int i,j;

    if ((*psca)!=NULL) _SCALAR3D_Free(psca); 
    *psca= malloc(sizeof(SCALAR3D));
    if ((*psca)==NULL) 
    {
        fprintf(stderr, "SCALAR3D_Init: Memory Allocate Error.\n");
    }

    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
            (*psca)->axis[i][j]=(i==j)?1:0;

    for (i=0; i<3; i++)
        (*psca)->ngrid[i]=0;     

    (*psca)->val= NULL;
}

void _SCALAR3D_Free(SCALAR3D **psca)
{
    if ((*psca)->val!=NULL) free((*psca)->val);
    free(*psca);
    *psca=NULL;
}

int SCALAR3D_READ( SCALAR3D* sca, POSCAR* pos, FILE* pf)
{
    int i,j,count;
    int NGRID;
    int iline, ret;
    char cdump[POSCAR_COMMENT_LEN];

    if (sca==NULL) return FIELD_NULL_SCA;
    if (pos==NULL) return FIELD_NULL_POS;
    if (pf==NULL)  return FILED_NULL_PF ;

    POSCAR_Init(pos);
    SCALAR3D_Init(sca);

    ret= POSCAR_Read(pos,pf);
    if (ret!=0) return ret;

    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
            sca->axis[i][j]= pos->lat->a[i][j];

    if (pos->elem_num!=NULL)
        iline= pos->natom+8;
    else
        iline= pos->natom+7;

    /*blank line*/
    READLINE(iline, cdump, POSCAR_COMMENT_LEN, pf);

    /*NGX NGY NGZ*/
    READLINE(iline, cdump, POSCAR_COMMENT_LEN, pf);
    ret= sscanf(cdump, "%d %d %d", &sca->ngrid[0], &sca->ngrid[1], &sca->ngrid[2]);
    if (ret!=3)
    {
        fprintf(stderr,"SCALAR3D_READ: Parsing Number of grid failed.\n");
        exit(iline);
    }
    for (i=0; i<3; i++)
    {
        if (sca->ngrid[i]<=0)
        {
            fprintf(stderr,"SCALAR3D_READ: Numbers of grids must be postive.\n");
            exit(iline);
        }
    }

    NGRID= sca->ngrid[0]*sca->ngrid[1]*sca->ngrid[2];

    sca->val= malloc(sizeof(double)*NGRID);
    if (sca->val==NULL)
    {
        fprintf(stderr,"SCALAR3D_READ: Memroy Allocate for scalar field failed.\n");
        exit(FIELD_MEM_VAL);
    } 

    /*Data*/
    for (count=0; count<NGRID; count++)
    {
        fscanf(pf,"%lf", &(sca->val[count]));
    }

    READLINE(iline, cdump, POSCAR_COMMENT_LEN, pf);

    return 0;
}

void _SCALAR1D_Init(SCALAR1D **psca)
{
    if ((*psca)!=NULL) _SCALAR1D_Free(psca); 
    *psca= malloc(sizeof(SCALAR1D));
    if ((*psca)==NULL) 
    {
        fprintf(stderr, "SCALAR1D_Init: Memory Allocate Error.\n");
    }

    (*psca)->axis[0]=1;
    (*psca)->axis[1]=0;
    (*psca)->axis[2]=0;

    (*psca)->ngrid=0;     

    (*psca)->val= NULL;
}

void _SCALAR1D_Free(SCALAR1D **psca)
{
    if ((*psca)->val!=NULL) free((*psca)->val);
    free(*psca);
    *psca=NULL;
}

void SCALAR3D_AVE(SCALAR3D* sca3d, SCALAR1D* sca1d, int direction)
{
    int i,j,k, index, A;
    /* Check Argument */
    if ( (direction>=0) && (direction<3) )
    {
        fprintf(stderr, "SCALAR3D_AVE: direction out of range. %d",direction);
        exit(1);
    }
    else
    {
        SCALAR1D_Free(sca1d);
    }

    /* Copy */
    for (i=0; i<3; i++)
        sca1d->axis[i]= sca3d->axis[direction][i];

    sca1d->ngrid= sca3d->ngrid[direction];

    sca1d->val= malloc(sizeof(double)*sca1d->ngrid);
    if (sca1d->val==NULL)
    {
        fprintf(stderr, "SCALAR3D_AVE: Memory Allocate Error\n");
        exit(1);
    }
    else
    {
        for (i=0; i<sca1d->ngrid; i++)
            sca1d->val=0;
    }

    for (i=0; i< sca3d->ngrid[0]; i++)
        for (j=0; j< sca3d->ngrid[1]; j++)
            for (k=0; i< sca3d->ngrid[2]; k++)
    {
        index= M3dT1d(i,j,k,sca3d->ngrid[0],sca3d->ngrid[1],sca3d->ngrid[2]);
        if (direction==0) 
            sca1d->val[i] += sca3d->val[index];
        else if (direction==1)
            sca1d->val[j] += sca3d->val[index];
        else if (direction==2)
            sca1d->val[k] += sca3d->val[index];
        else
        {
            fprintf(stderr,"SCALAR3D_AVE: Out of range direction. %d\n",direction);
            exit(1);
        }
    }
    
    if (direction==0)
        A= sca3d->ngrid[1]*sca3d->ngrid[2];
    else if (direction==1)
        A= sca3d->ngrid[0]*sca3d->ngrid[2];
    else if (direction==2)
        A= sca3d->ngrid[0]*sca3d->ngrid[1];
    else
    {
        fprintf(stderr,"SCALAR3D_AVE: Out of range direction. %d\n",direction);
        exit(1);
    }

    for (i=0; i<sca1d->ngrid; i++)
    {
        sca1d->val[i]/= (double)A;
    }
}
