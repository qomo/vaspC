#include "glib.h"
#include "vaspC.h"

void check_FindVacX()
{
    int i,j;
    double vac[3][2];
    FILE* pf=NULL;
    POSCAR *pos=NULL;

    POSCAR_Init(pos);
    if ((pf=fopen("data/surface/InSb_VAC10_X","r"))==NULL)
    {
        g_assert(false);     
    }

    POSCAR_Read(pos, pf);

    FindVac(pos, vac);

    for (i=0; i<3; i++)
    {
        if (i!=0)
        {
            for (j=0; j<2; j++)
            {
                g_assert_cmpfloat(vac[i][j],==,0);
            } 
        }
        else
        {
            g_assert_cmpfloat(vac[i][0],==,0.2994904607365295);
            g_assert_cmpfloat(vac[i][1],==,1.0);
        }
    }

    fclose(pf);
    POSCAR_Free(pos);
}

void check_FindVacY()
{
    int i,j;
    double vac[3][2];
    FILE* pf=NULL;
    POSCAR *pos=NULL;

    POSCAR_Init(pos);
    if ((pf=fopen("data/surface/InSb_VAC10_Y","r"))==NULL)
    {
        g_assert(false);     
    }

    POSCAR_Read(pos, pf);

    FindVac(pos, vac);

    for (i=0; i<3; i++)
    {
        if (i!=1)
        {
            for (j=0; j<2; j++)
            {
                g_assert_cmpfloat(vac[i][j],==,0);
            } 
        }
        else
        {
            g_assert_cmpfloat(vac[i][0],==,0.2994904607365295);
            g_assert_cmpfloat(vac[i][1],==,1.0);
        }
    }

    fclose(pf);
    POSCAR_Free(pos);
}

void check_FindVacZ()
{
    int i,j;
    double vac[3][2];
    FILE* pf=NULL;
    POSCAR *pos=NULL;

    POSCAR_Init(pos);
    if ((pf=fopen("data/surface/InSb_VAC10_Z","r"))==NULL)
    {
        g_assert(false);     
    }

    POSCAR_Read(pos, pf);

    FindVac(pos, vac);

    for (i=0; i<3; i++)
    {
        if (i!=2)
        {
            for (j=0; j<2; j++)
            {
                g_assert_cmpfloat(vac[i][j],==,0);
            } 
        }
        else
        {
            g_assert_cmpfloat(vac[i][0],==,0.2994904607365295);
            g_assert_cmpfloat(vac[i][1],==,1.0);
        }
    }

    fclose(pf);
    POSCAR_Free(pos);
}

void check_FindVacXY()
{
    int i,j;
    double vac[3][2];
    FILE* pf=NULL;
    POSCAR *pos=NULL;

    POSCAR_Init(pos);
    if ((pf=fopen("data/surface/InSb_VAC10_X_VAC3_Y","r"))==NULL)
    {
        g_assert(false);     
    }

    POSCAR_Read(pos, pf);

    FindVac(pos, vac);

    for (i=0; i<3; i++)
    {
        if (i!=0)
        {
            for (j=0; j<2; j++)
            {
                g_assert_cmpfloat(vac[i][j],==,0);
            } 
        }
        else
        {
            g_assert_cmpfloat(vac[i][0],==,0.2994904607365295);
            g_assert_cmpfloat(vac[i][1],==,1.0);
        }
    }

    fclose(pf);
    POSCAR_Free(pos);
}

void check_FindVacXYZ()
{
    int i;
    double vac[3][2];
    FILE* pf=NULL;
    POSCAR *pos=NULL;

    POSCAR_Init(pos);
    if ((pf=fopen("data/surface/InSb_VAC10_XYZ","r"))==NULL)
    {
        g_assert(false);     
    }

    POSCAR_Read(pos, pf);

    FindVac(pos, vac);

    for (i=0; i<3; i++)
    {
        {
            g_assert_cmpfloat(vac[i][0],==,0.2994904607365295);
            g_assert_cmpfloat(vac[i][1],==,1.0);
        }
    }

    fclose(pf);
    POSCAR_Free(pos);
}

void check_InVac()
{
    int i,j,k;
    double pos[3];
    double vac[3][2];

    for (i=0; i<3; i++)
    {
        for (j=0; j<3; j++)
            for (k=0; k<2; k++)
                vac[j][k]= 0;
        for (j=0; j<3; j++) *(pos+j)= 0;
        vac[i][0]=-0.2;
        vac[i][1]=0.2;
        pos[i]= 0.5;
        g_assert(!InVac(vac,pos));

        for (j=0; j<3; j++)
            for (k=0; k<2; k++)
                vac[j][k]= 0;
        for (j=0; j<3; j++) *(pos+j)= 0;
        vac[i][0]=-0.2;
        vac[i][1]=0.2;
        pos[i]= 1.1;
        g_assert(InVac(vac,pos));


        for (j=0; j<3; j++)
            for (k=0; k<2; k++)
                vac[j][k]= 0;
        for (j=0; j<3; j++) *(pos+j)= 0;
        vac[i][0]=0.2;
        vac[i][1]=0.6;
        pos[i]= 0.5;
        g_assert(InVac(vac,pos));

        for (j=0; j<3; j++)
            for (k=0; k<2; k++)
                vac[j][k]= 0;
        for (j=0; j<3; j++) *(pos+j)= 0;
        vac[i][0]=0.8;
        vac[i][1]=1.2;
        pos[i]= 0.1;
        g_assert(InVac(vac,pos));


    }
}
