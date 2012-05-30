#include "glib.h"
#include "vaspC.h"

#define HIGH_PREC 1e-14

void check_SCALAR3D_ReadPOSCAR()
{
    int ret;
    FILE *pf=NULL;
    POSCAR *pos_ref=NULL, *pos=NULL;
    SCALAR3D *sca=NULL;

    POSCAR_Init(pos_ref);
    POSCAR_Init(pos);
    SCALAR3D_Init(sca);

    if ((pf=fopen("data/field/LOCPOT_E0.0","r"))==NULL)
    {
        g_assert(false);
    }
    POSCAR_Read(pos_ref,pf);
    fclose(pf);

    if ((pf=fopen("data/field/LOCPOT_E0.0","r"))==NULL)
    {
        g_assert(false);
    }

    ret= SCALAR3D_READ(sca,pos,pf);
    g_assert_cmpint(ret,==,0);
    fclose(pf);

    /* comment */
    g_assert_cmpstr(pos_ref->comment,==,pos->comment);
    /* scale */
    g_assert_cmpfloat(pos_ref->scale,==,pos->scale);

    POSCAR_Free(pos_ref);
    POSCAR_Free(pos);
    SCALAR3D_Free(sca);

}

void check_SCALAR3D_ReadLat()
{
    int i,j;
    int ret;
    FILE *pf=NULL;
    POSCAR *pos=NULL;
    SCALAR3D *sca=NULL;

    POSCAR_Init(pos);
    SCALAR3D_Init(sca);

    if ((pf=fopen("data/field/LOCPOT_E0.0","r"))==NULL)
    {
        g_assert(false);
    }
    ret= SCALAR3D_READ(sca,pos,pf);
    g_assert_cmpint(ret,==,0);
    fclose(pf);

    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
        {
            g_assert_cmpfloat(sca->axis[i][j],==,pos->lat->a[i][j]);
        }

    POSCAR_Free(pos);
    SCALAR3D_Free(sca);
}

void check_SCALAR3D_ReadGrid()
{
    int ret;
    FILE *pf=NULL;
    POSCAR *pos=NULL;
    SCALAR3D *sca=NULL;

    POSCAR_Init(pos);
    SCALAR3D_Init(sca);

    if ((pf=fopen("data/field/LOCPOT_E0.0","r"))==NULL)
    {
        g_assert(false);
    }
    ret= SCALAR3D_READ(sca,pos,pf);
    g_assert_cmpint(ret,==,0);
    fclose(pf);

    g_assert_cmpint(sca->ngrid[0],==,40);
    g_assert_cmpint(sca->ngrid[1],==,40);
    g_assert_cmpint(sca->ngrid[2],==,1050);
   
    POSCAR_Free(pos);
    SCALAR3D_Free(sca);

}

void check_SCALAR3D_ReadVal()
{

    int i, ngrid, ret;
    FILE *pf=NULL;
    POSCAR *pos=NULL;
    SCALAR3D *sca=NULL;

    POSCAR_Init(pos);
    SCALAR3D_Init(sca);

    if ((pf=fopen("data/field/LOCPOT_Simple","r"))==NULL)
    {
        g_assert(false);
    }
    ret= SCALAR3D_READ(sca,pos,pf);
    g_assert_cmpint(ret,==,0);
    fclose(pf);

    ngrid= sca->ngrid[0]*sca->ngrid[1]*sca->ngrid[2];

    for (i=0; i<ngrid; i++)
    {
        g_assert_cmpfloat(sca->val[i],==,i+1);
    }
   
    POSCAR_Free(pos);
    SCALAR3D_Free(sca);
}
