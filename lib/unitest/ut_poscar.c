/**
 * @breif unittest for poscar.c
 * @author Zhi-Quan Huang
 * @date 2012-04-16
 */

#include "glib.h"
#include "vaspC.h"

#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define HIGH_PREC 1e-14

void check_POSCAR_Copy()
{
    int i,j;
    FILE* pf=NULL;
    POSCAR* pos=NULL;
    POSCAR* pos_ref=NULL;

    POSCAR_Init(pos_ref);

    /* Read File */
    if ((pf=fopen("data/poscar/POSCAR_v5","r"))==NULL)
    {
        g_assert(false);
    }

    g_assert_cmpint(POSCAR_Read(pos_ref, pf),==,0);

    /* Copy struct */
    g_assert_cmpint(POSCAR_Copy(pos_ref, pos),==,0);

    /* Compare */
    g_assert(pos_ref != pos);
    g_assert_cmpstr(pos_ref->comment,==,pos->comment);
    g_assert_cmpfloat(pos_ref->scale,==,pos->scale);
    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
        {
            g_assert_cmpfloat(pos_ref->lat->a[i][j],==,pos->lat->a[i][j]);
        }

    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
        {
            g_assert_cmpfloat(pos_ref->lat->b[i][j],==,pos->lat->b[i][j]);
        }

    g_assert_cmpint(pos_ref->nelem,==,pos->nelem);
    g_assert_cmpint(pos_ref->natom,==,pos->natom);

    if (pos_ref->elem_num==NULL)
    {
        g_assert(pos->elem_num==NULL);
    }
    else
    {
        g_assert(pos_ref->elem_num!=pos->elem_num);

        for (i=0; i<pos_ref->nelem; i++)
        {
            g_assert_cmpint(pos_ref->elem_num[i],==,pos->elem_num[i]);
        }
    }
        
    if (pos_ref->elem_count==NULL) 
        g_assert(pos->elem_count==NULL);
    else
    {
        g_assert(pos_ref->elem_count!=pos->elem_count);

        for (i=0; i<pos_ref->nelem; i++)
        {
            g_assert_cmpint(pos_ref->elem_count[i],==,pos->elem_count[i]);
        }
    }

    if (pos_ref->atom_pos==NULL)
        g_assert(pos->atom_pos==NULL);
    else
    {
        g_assert(pos_ref->atom_pos!=pos->atom_pos);

        for (i=0; i<pos_ref->natom; i++)
        {
            for (j=0; j<3; j++)
                g_assert_cmpint(pos_ref->atom_pos[i][j],
                                ==,pos->atom_pos[i][j]);
        }
    }

    if (pos_ref->atom_dyn==NULL)
        g_assert(pos->elem_num==NULL);
    else
    {
        g_assert(pos_ref->atom_dyn!=pos->atom_dyn);

        for (i=0; i<pos_ref->natom; i++)
        {
            for (j=0; j<3; j++)
                g_assert(pos_ref->atom_dyn[i][j]
                                ==pos->atom_dyn[i][j]);
        }
    }

    POSCAR_Free(pos);
    POSCAR_Free(pos_ref);
}

void check_POSCAR_A2B()
{
    int i,j;
    POSCAR* pos=NULL;

    POSCAR_Init(pos);

    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
        {
            if (i!=j)
                pos->lat->a[i][j]=0.5;
            else
                pos->lat->a[i][j]=0.0;
        }
    POSCAR_A2B(pos);
    
    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
        {
            if (i!=j)
                g_assert_cmpfloat(pos->lat->b[i][j],==,1.0);
            else
                g_assert_cmpfloat(pos->lat->b[i][j],==,-1.0);
        }

    POSCAR_Free(pos);
}

void check_POSCAR_LatXRec()
{
    int i,j,k;
    double d;
    double I[3][3];
    FILE *pf;

    POSCAR *pos=NULL;
    POSCAR_Init(pos);

    if ((pf=fopen("data/poscar/POSCAR_v5","r"))==NULL)
        g_assert(false);
    else
        g_assert_cmpint(POSCAR_Read(pos, pf),==,0);

    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
            I[i][j]=0;

    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
        {
            for (k=0; k<3; k++)
                I[i][j]+=pos->lat->a[i][k]*pos->lat->b[j][k];
        }

    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
        {
            if (i==j)
            {
                d= fabs(I[i][j]-1.0);
                g_assert(d<HIGH_PREC);
            }
            else
            {
                d= fabs(I[i][j]-0.0);
                g_assert(d<HIGH_PREC);
            }
        }

    POSCAR_Free(pos);
}

void check_POSCAR_D2C()
{
    int i,j;
    FILE* pf;
    POSCAR *posC=NULL, *posD=NULL;

    POSCAR_Init(posC);
    POSCAR_Init(posD);

    if ((pf=fopen("data/poscar/POSCAR_v5","r"))==NULL)
        g_assert(false);
    else
        g_assert_cmpint(POSCAR_Read(posD, pf),==,0);

    if ((pf=fopen("data/poscar/POSCAR_C","r"))==NULL)
        g_assert(false);
    else
        g_assert_cmpint(POSCAR_Read(posC, pf),==,0);

    POSCAR_D2C(posD);
    g_assert(!posD->isD);
    for (i=0; i<posD->natom; i++)
    {
        for (j=0; j<3; j++)
        {
            g_assert_cmpfloat(posD->atom_pos[i][j],==,posC->atom_pos[i][j]);
        } 
    }
    POSCAR_Free(posC);
    POSCAR_Free(posD);
}

void check_POSCAR_C2D()
{
    int i,j;
    double d;
    FILE* pf;
    POSCAR *posC=NULL, *posD=NULL;

    POSCAR_Init(posC);
    POSCAR_Init(posD);

    if ((pf=fopen("data/poscar/POSCAR_v5","r"))==NULL)
        g_assert(false);
    else
        g_assert_cmpint(POSCAR_Read(posD, pf),==,0);

    if ((pf=fopen("data/poscar/POSCAR_C","r"))==NULL)
        g_assert(false);
    else
        g_assert_cmpint(POSCAR_Read(posC, pf),==,0);

    POSCAR_C2D(posC);

    g_assert(posC->isD);
    for (i=0; i<posD->natom; i++)
    {
        for (j=0; j<3; j++)
        {
            d= posD->atom_pos[i][j]-posC->atom_pos[i][j];
            g_assert(fabs(d)<HIGH_PREC);
        } 
    }

    POSCAR_Free(posC);
    POSCAR_Free(posD);

}

void check_POSCAR_Read_v5()
{
    int i,j;
    bool b;
    double d;
    FILE *pf=NULL;
    POSCAR* pos=NULL;

    POSCAR_Init(pos);

    if ((pf=fopen("data/poscar/POSCAR_v5","r"))==NULL)
    {
        g_assert(false);
    }

    g_assert_cmpint(POSCAR_Read(pos, pf),==,0);

    /*comment*/
    g_assert_cmpstr((pos->comment),==,"InSb");
    /*scale*/
    g_assert_cmpfloat((pos->scale),==,2.0);
    /*lattice*/
    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
        {
            g_assert_cmpfloat((pos->lat->a[i][j]),==,(10*i+5*j+((i==j)?10:0))*pos->scale);
        }

    /* Atomic number */
    g_assert_cmpint(pos->nelem,==,2);
    g_assert_cmpint(pos->elem_num[0],==,49);
    g_assert_cmpint(pos->elem_num[1],==,51);
    g_assert_cmpint(pos->natom,==,8);
    g_assert_cmpint(pos->elem_count[0],==,4);
    g_assert_cmpint(pos->elem_count[1],==,4);

    /* Direct */
    g_assert(pos->isD);

    /* position */
    for (i=0; i<pos->natom; i++)
        for (j=0; j<3; j++)
        {
            d= pos->atom_pos[i][j] -(double)(i+j)*0.1;
            g_assert(fabs(d)<HIGH_PREC);
        }

    /* dynamics */
    for (i=0; i<pos->natom; i++)
        for (j=0; j<3; j++)
        {
            b=((i+j)%2==0)?true:false;
            g_assert(!(pos->atom_dyn[i][j]^b));
        }
    fclose(pf);
    
    POSCAR_Free(pos);

}

void check_POSCAR_Read_v4()
{
    int i,j;
    FILE* pf;
    POSCAR* posv4=NULL;
    POSCAR* posv5=NULL;

    POSCAR_Init(posv4);
    POSCAR_Init(posv5);
    
    if ((pf=fopen("data/poscar/POSCAR_v5","r"))==NULL)
        g_assert(false);
    else
        g_assert_cmpint(POSCAR_Read(posv5, pf),==,0);

    if ((pf=fopen("data/poscar/POSCAR_v4","r"))==NULL)
        g_assert(false);
    else
        g_assert_cmpint(POSCAR_Read(posv4, pf),==,0);
    
    /*Comment*/  
    g_assert_cmpstr(posv4->comment,==,posv5->comment);

    /*Scale*/  
    g_assert_cmpfloat(posv4->scale,==,posv5->scale);
    
    /*Lat*/
    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
        {
            g_assert_cmpfloat(posv4->lat->a[i][j],==,posv5->lat->a[i][j]);
        }

    /*Rec*/
    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
        {
            g_assert_cmpfloat(posv4->lat->b[i][j],==,posv5->lat->b[i][j]);
        }

    /*Count*/
    g_assert_cmpint(posv4->nelem,==,posv5->nelem);
    for (i=0; i<posv4->nelem; i++)
    {
        g_assert_cmpint(posv4->elem_count[i],==,posv5->elem_count[i]);
    }

    /*Select*/
    g_assert(!((posv4->atom_dyn!=NULL)^(posv5->atom_dyn!=NULL)));

    /*Cart Direct*/
    g_assert(!(posv4->isD^posv5->isD));

    /*Position*/
    g_assert_cmpint(posv4->natom,==,posv5->natom);
    for (i=0; i<posv4->natom; i++)
        for (j=0; j<3; j++)
        {
            g_assert_cmpfloat(posv4->atom_pos[i][j],==,posv5->atom_pos[i][j]);
        }

    /*Dyn*/
    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
        {
            g_assert(!(posv4->atom_dyn[i][j]^posv5->atom_dyn[i][j]));
        }

    POSCAR_Free(posv4);
    POSCAR_Free(posv5);

}

void check_POSCAR_Read_NDYN()
{
    int i,j;
    FILE* pf;
    POSCAR* posv5=NULL;
    POSCAR* posndyn=NULL;
    
    POSCAR_Init(posv5);
    POSCAR_Init(posndyn);

    if ((pf=fopen("data/poscar/POSCAR_v5","r"))==NULL)
        g_assert(false);
    else
        g_assert_cmpint(POSCAR_Read(posv5, pf),==,0);

    if ((pf=fopen("data/poscar/POSCAR_NDYN","r"))==NULL)
        g_assert(false);
    else
        g_assert_cmpint(POSCAR_Read(posndyn, pf),==,0);
    
    /*Comment*/  
    g_assert_cmpstr(posndyn->comment,==,posv5->comment);

    /*Scale*/  
    g_assert_cmpfloat(posndyn->scale,==,posv5->scale);
    
    /*Lat*/
    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
        {
            g_assert_cmpfloat(posndyn->lat->a[i][j],==,posv5->lat->a[i][j]);
        }

    /*Rec*/
    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
        {
            g_assert_cmpfloat(posndyn->lat->b[i][j],==,posv5->lat->b[i][j]);
        }

    /*num*/
    g_assert_cmpint(posndyn->nelem,==,posv5->nelem);
    for (i=0; i<posndyn->nelem; i++)
    {
        g_assert_cmpint(posndyn->elem_num[i],==,posv5->elem_num[i]);
    }
    /*Count*/
    for (i=0; i<posndyn->nelem; i++)
    {
        g_assert_cmpint(posndyn->elem_count[i],==,posv5->elem_count[i]);
    }

    /*Select*/
    g_assert(!((posndyn->atom_dyn==NULL)^(posv5->atom_dyn!=NULL)));

    /*Cart Direct*/
    g_assert(!(posndyn->isD^posv5->isD));

    /*Position*/
    g_assert_cmpint(posndyn->natom,==,posv5->natom);
    for (i=0; i<posndyn->natom; i++)
        for (j=0; j<3; j++)
        {
            g_assert_cmpfloat(posndyn->atom_pos[i][j],==,posv5->atom_pos[i][j]);
        }

    POSCAR_Free(posv5);
    POSCAR_Free(posndyn);

}

void check_POSCAR_Confined()
{
    int i,j;
    double d;
    POSCAR* pos=NULL; 
    POSCAR* pos_ref=NULL; 
    FILE* pf=NULL;

    POSCAR_Init(pos);
    POSCAR_Init(pos_ref);

    if ((pf=fopen("data/poscar/POSCAR_v5","r"))==NULL)
    {
        g_assert(false);
    }
    g_assert_cmpint(POSCAR_Read(pos_ref, pf),==,0);

    if ((pf=fopen("data/poscar/POSCAR_v5_+1","r"))==NULL)
    {
        g_assert(false);
    }
    g_assert_cmpint(POSCAR_Read(pos, pf),==,0);

    POSCAR_Confined(pos);

    for (i=0; i<pos->natom; i++) 
        for (j=0; j<3; j++)
        {
            d= fabs(pos_ref->atom_pos[i][j]-pos->atom_pos[i][j]);
            g_assert(d<HIGH_PREC);
        }

    POSCAR_Free(pos_ref);
    POSCAR_Free(pos);

}


