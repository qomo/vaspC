#include "line.h"
#include "element.h"
#include "poscar.h"
#include "vmath.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void _POSCAR_Init(POSCAR** ppos)
{
    int i;

    if ((*ppos)!=NULL) _POSCAR_Free(ppos);
    *ppos= malloc(sizeof(POSCAR));
    if ((*ppos)==NULL) 
    {
        fprintf(stderr, "POSCAR_Init: Memory Allocate Error.\n");
        exit(1);
    }

    for (i=0; i<POSCAR_COMMENT_LEN; i++)
        (*ppos)->comment[i]='\0';
    (*ppos)->scale=0.0;
    (*ppos)->lat=NULL;
    _LATTICE_Init(&((*ppos)->lat));
    (*ppos)->nelem=0;
    (*ppos)->natom=0;
    (*ppos)->elem_num=NULL;    
    (*ppos)->elem_count=NULL;    
    (*ppos)->isD=true;
    (*ppos)->atom_pos=NULL;    
    (*ppos)->atom_dyn=NULL;
}

int _POSCAR_Copy(POSCAR* pos, POSCAR** pcp)
{
    int i,j;

    _POSCAR_Init(pcp);

    strncpy((*pcp)->comment, pos->comment, POSCAR_COMMENT_LEN-1);
    (*pcp)->scale= pos->scale;
    LATTICE_Copy(pos->lat, &((*pcp)->lat));
    (*pcp)->nelem= pos->nelem;
    (*pcp)->natom= pos->natom;

    if (pos->elem_num!=NULL)  
    {
        (*pcp)->elem_num= malloc(sizeof(int)*pos->nelem);
        if ((*pcp)->elem_num==NULL) return POSCAR_MEM_ELEM_NUM;
        for (i=0; i<pos->nelem; i++)
        {
            (*pcp)->elem_num[i]= pos->elem_num[i]; 
        }
    }

    if (pos->elem_count!=NULL)  
    {
        (*pcp)->elem_count= malloc(sizeof(int)*pos->nelem);
        if ((*pcp)->elem_count==NULL) return POSCAR_MEM_ELEM_COUNT;
        for (i=0; i<pos->nelem; i++)
        {
            (*pcp)->elem_count[i]= pos->elem_count[i];
        }  
    }

    (*pcp)->isD= pos->isD;

    if (pos->atom_pos!=NULL)
    {
        (*pcp)->atom_pos= malloc(sizeof(double)*pos->natom*3);
        if ((*pcp)->atom_pos==NULL) return POSCAR_MEM_ATOM_POS;
        for (i=0; i<pos->natom; i++) 
            for (j=0; j<3; j++)
            {
                (*pcp)->atom_pos[i][j]= pos->atom_pos[i][j];
            }
    }

    if (pos->atom_dyn!=NULL)
    {
        (*pcp)->atom_dyn= malloc(sizeof(double)*pos->natom*3);
        if ((*pcp)->atom_dyn==NULL) return POSCAR_MEM_ATOM_DYN;
        for (i=0; i<pos->natom; i++) 
            for (j=0; j<3; j++)
            {
                (*pcp)->atom_dyn[i][j]= pos->atom_dyn[i][j];
            }

    }
    return 0;
}

void _POSCAR_Free(POSCAR** ppos)
{
    /*Argument*/
    if (*ppos==NULL) return;
    _LATTICE_Free(&((*ppos)->lat));
    if ((*ppos)->elem_num!=NULL)   free((*ppos)->elem_num);
    if ((*ppos)->elem_count!=NULL) free((*ppos)->elem_count);
    if ((*ppos)->atom_pos!=NULL)   free((*ppos)->atom_pos);
    if ((*ppos)->atom_dyn!=NULL)   free((*ppos)->atom_dyn);
    free(*ppos);
    *ppos=NULL;
}

void POSCAR_D2C(POSCAR* pos) 
{
    int i;
    if (pos->isD)
    {
        for (i=0; i<pos->natom; i++)
        {
            LATTICE_D2C(pos->lat, pos->atom_pos[i]);
        } 
        pos->isD=false;
    }
}

void POSCAR_C2D(POSCAR* pos) 
{
    int i;
    if (!pos->isD)
    {
        for (i=0; i<pos->natom; i++)
        {
            LATTICE_C2D(pos->lat, pos->atom_pos[i]);
        } 
        pos->isD=true;
    }
}

void POSCAR_A2B(POSCAR* pos) 
{
    LATTICE_A2B(pos->lat);
}

void POSCAR_Confined(POSCAR* pos)
{
    int i,j;
    bool isD= pos->isD;

    if (!isD) POSCAR_C2D(pos);

    for (i=0; i<pos->natom; i++)
    {
        for (j=0; j<3; j++)    
        {
            while((pos->atom_pos[i][j]<0)||(pos->atom_pos[i][j]>=1))
            {
                if (pos->atom_pos[i][j]<0)   
                {
                    pos->atom_pos[i][j]+=1; 
                }
                else if (pos->atom_pos[i][j]>=1)
                {
                    pos->atom_pos[i][j]-=1; 
                }
            }
        }
    }

    if (!isD) POSCAR_D2C(pos);
}

int POSCAR_Read(POSCAR* pos,  FILE* pf)
{
    int iline=0;  /* Readling iline-th line. */
    
    /*Temp Variable*/
    int i,j,k;
    char cdump[POSCAR_COMMENT_LEN];
    char cbool[3][POSCAR_COMMENT_LEN];
    const char *DELIMITERS= "\t \n";
    char* pch = NULL;
        
    /* Check arguments */
    if (!pos)
    {
        return POSCAR_NULL_POS;
    }
    else if (!pf)
    {
        return POSCAR_NULL_PF;
    }
 
    /* Init */
    POSCAR_Init(pos);
    /*1st Line*/
    READLINE(iline, pos->comment, POSCAR_COMMENT_LEN, pf);
    rstrip(pos->comment);
    /*2 Line*/
    READLINE(iline, cdump, POSCAR_COMMENT_LEN, pf);
    if(sscanf(cdump,"%lf",&pos->scale)!=1)
    {
        return iline;
    }
    /*3-5 Line*/
    for (i=0; i<3; i++)
    {
        READLINE(iline, cdump, POSCAR_COMMENT_LEN, pf);
        if (sscanf(cdump, "%lf %lf %lf", 
                        &pos->lat->a[i][0], &pos->lat->a[i][1], &pos->lat->a[i][2])!=3)
        {
            return iline;
        }
    }

    for (i=0; i<3; i++)
    {
        for (j=0; j<3; j++)
            pos->lat->a[i][j]*=pos->scale;
    }

    POSCAR_A2B(pos);

    /*6 Line*/
    READLINE(iline, cdump, POSCAR_COMMENT_LEN, pf); 
    pos->nelem= nitems(cdump, DELIMITERS);
    pch=NULL;
    for (i=0; i<strlen(cdump); i++)
    {
        if (isdigit(cdump[i]))
        {
            pch= &(cdump[i]);
            break;
        }
    }
    if (!pch)
    {
        pos->elem_num= (int*) malloc(sizeof(int)*pos->nelem);
        if (!pos->elem_num)
        {
            return POSCAR_MEM_ELEM_NUM;
        }

        /*Next line*/
        READLINE(iline, cdump, POSCAR_COMMENT_LEN, pf) ;
        i= nitems(cdump, DELIMITERS);
        if (i!=pos->nelem)
            return POSCAR_NUM_COUNT_DISMATCH;

        if((pos->elem_count= (int*) malloc(sizeof(int)*pos->nelem))==NULL)
            return POSCAR_MEM_ELEM_COUNT;
    }
    else
    {
        pos->elem_count= (int*) malloc(sizeof(int)*pos->nelem);
        if (!pos->elem_count)
        {
            return POSCAR_MEM_ELEM_COUNT;
        }
    }
    /*Re Read 5 Line*/
    fseek(pf, 0, SEEK_SET);
    iline=0;
    for (i=0; i<5; i++)
    {
        READLINE(iline, cdump, POSCAR_COMMENT_LEN, pf);
    }
    /*Read 6 Line*/
    if (pos->elem_num!=NULL)
    {
        READLINE(iline, cdump, POSCAR_COMMENT_LEN, pf);
        pch=strtok(cdump," \t");
        for (j=0; j<pos->nelem; j++)
        {
            k= PERIOD_TABLE_name2num(pch);
            if (k<=0) return iline;
            pos->elem_num[j]=k;
            pch=strtok(NULL," \t");
        }
    }

    READLINE(iline, cdump, POSCAR_COMMENT_LEN, pf);
    pch=strtok(cdump," \t");
    for (j=0; j<pos->nelem; j++)
    {
        if (sscanf(pch,"%d",&k)!=1) return iline;
        pos->elem_count[j]=k;
        pch=strtok(NULL," \t");
    }

    for (i=0; i<pos->nelem; i++)
    {
        pos->natom+= pos->elem_count[i];
    }

    /*Read 7 Line*/
    READLINE(iline, cdump, POSCAR_COMMENT_LEN, pf);
    if (cdump[0]=='s' || cdump[0]=='S')
    {
        pos->atom_dyn= malloc(sizeof(bool)*3*pos->natom);
        if(pos->atom_dyn==NULL)
        {
            return POSCAR_MEM_ATOM_DYN;
        }
        READLINE(iline, cdump, POSCAR_COMMENT_LEN, pf);
    }

    pos->atom_pos= malloc(sizeof(double)*3*pos->natom);
    if (pos->atom_pos==NULL)
    {
        return POSCAR_MEM_ATOM_POS;
    }
    if (cdump[0]=='c' || cdump[0]=='C' 
        || cdump[0]=='k' || cdump[0]=='K')
    {
        pos->isD=false;    
    }

    if (pos->atom_dyn!=NULL)
    {
        for (i=0; i<pos->natom; i++)
        {
            READLINE(iline, cdump, POSCAR_COMMENT_LEN, pf);
            k=sscanf(cdump,"%lf %lf %lf %s %s %s",
                     &pos->atom_pos[i][0],&pos->atom_pos[i][1],&pos->atom_pos[i][2],
                     cbool[0], cbool[1],cbool[2]);
            if (k!=6) return iline;
            for (j=0; j<3; j++)
            {
                if ( cbool[j][0]=='T' || cbool[j][0]=='t')
                    pos->atom_dyn[i][j]=true;
                else if ( cbool[j][0]=='F' || cbool[j][0]=='f')
                    pos->atom_dyn[i][j]=false;
                else
                    return iline;
            }
        }
    }
    else
    {
        for (i=0; i<pos->natom; i++)
        {
            READLINE(iline, cdump, POSCAR_COMMENT_LEN, pf);
            j=sscanf(cdump,"%lf %lf %lf",
                     &pos->atom_pos[i][0],&pos->atom_pos[i][1],&pos->atom_pos[i][2]);
            if (j!=3) return iline;   
        }
    }

    if (!pos->isD)
    {
        for(i=0; i<pos->natom; i++)
            for (j=0; j<3; j++)
                pos->atom_pos[i][j]*=pos->scale;
    }

    return 0;
}

void POSCAR_Write(POSCAR* pos, FILE* pf, bool isLong, bool isElem, bool isDyn)
{
    int i,j;
    double scale=1.0;
    char* elem_name;
    bool isTempDyn=false;

    fprintf(pf,"%s\n", pos->comment);
    fprintf(pf," %18.14f\n", pos->scale);
    for (i=0; i<3; i++){
        for (j=0; j<3; j++)
        {
            if (isLong)
                fprintf(pf, " %22.16f",pos->lat->a[i][j]/pos->scale);
            else
                fprintf(pf, " %12.16f",pos->lat->a[i][j]/pos->scale);
        }
        fprintf(pf, "\n");
    }

    if (isElem && pos->elem_num!=NULL)
    {
        for (i=0; i<pos->nelem; i++)
        {
            elem_name= PERIOD_TABLE_num2name(pos->elem_num[i]);
            if (elem_name==NULL)
            {
                fprintf(stderr, "Internal Error: The name of element can not be found. %d %d",i,pos->elem_num[i]);    
                exit(1);
            } 
            else
                fprintf(pf, "%5s",elem_name);    
        }
        fprintf(pf,"\n");
    }

    for (i=0; i<pos->nelem; i++) 
    {
        fprintf(pf, "%6d",pos->elem_count[i]);    
    }
    fprintf(pf,"\n");

    if (pos->atom_dyn==NULL && isDyn) 
    {
        pos->atom_dyn= malloc(sizeof(bool)*(3*pos->natom));
        for (i=0; i<pos->natom; i++)
            for (j=0; j<3; j++)
            pos->atom_dyn[i][j]=true;

        isTempDyn=true;
    }
    
    if (isDyn)
        fprintf(pf,"Selective dynamics\n");

    if (pos->isD)
        fprintf(pf,"Direct\n");
    else
    {
        fprintf(pf,"Cart\n");
        scale= pos->scale;
    }

    for (i=0; i<pos->natom; i++)
    {
        if(isLong && isDyn)
            fprintf(pf," %19.16f %19.16f %19.16f %4c %4c %4c\n",
                    pos->atom_pos[i][0]/scale,pos->atom_pos[i][1]/scale,pos->atom_pos[i][2]/scale,
                    pos->atom_dyn[i][0]?'T':'F', pos->atom_dyn[i][1]?'T':'F', pos->atom_dyn[i][2]?'T':'F');
        else if (isLong && !isDyn)      
            fprintf(pf," %19.16f %19.16f %19.16f\n",
                       pos->atom_pos[i][0]/scale,pos->atom_pos[i][1]/scale,pos->atom_pos[i][2]/scale);    
        else if(!isLong && isDyn)
            fprintf(pf," %9.16f %9.16f %9.16f %2c %2c %2c\n",
                         pos->atom_pos[i][0]/scale,pos->atom_pos[i][1]/scale,pos->atom_pos[i][2]/scale,
                         pos->atom_dyn[i][0]?'T':'F', pos->atom_dyn[i][1]?'T':'F', pos->atom_dyn[i][2]?'T':'F');
        else if(!isLong && !isDyn)
            fprintf(pf," %9.6f %9.6f %9.6f\n",
                         pos->atom_pos[i][0]/scale,pos->atom_pos[i][1]/scale,pos->atom_pos[i][2]/scale);    
    }

    if (isTempDyn)
    {
        free(pos->atom_dyn);
        pos->atom_dyn=NULL;
    }

    if (!isLong) printf("\n");
}
