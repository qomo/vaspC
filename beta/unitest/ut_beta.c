/**
 * @breif unittest for beta.c
 * @author Zhi-Quan Huang
 * @date 2012-04-28
 */

#include "glib.h"
#include "vaspC.h"
#include "beta.h"
#include "zone.h"
#include <math.h>

#define HIGH_PREC 1e-14

#define PI (4.0*atan(1))


void check_beta_cubic();
void check_beta_hex();
void check_beta_vac();

void check_beta_cubic()
{
    int i,j;
    FILE *pf=NULL;
    FILE *pfE=NULL;
    POSCAR *pos=NULL;
    POSCAR *posE=NULL;
    SCALAR3D *sca=NULL;
    SCALAR3D *scaE=NULL;
    double beta_value;
    double skip[3][2];
    double vac[3][2];
    double max_pos[3];
    double max_vec[3];

    /*Init*/
    POSCAR_Init(pos);
    POSCAR_Init(posE);
    SCALAR3D_Init(sca);
    SCALAR3D_Init(scaE);

    for (i=0; i<3; i++)
        for (j=0; j<2; j++)
        {
            vac[i][j]=0;
           skip[i][j]=0;
        }

    /*Read*/
    if ((pf=fopen("data/beta/Cubic_E0.0","r"))==NULL)
    {
        g_assert(false);
    }
    else if ((pfE=fopen("data/beta/Cubic_E0.5","r"))==NULL)
    {
        g_assert(false);
    }

    g_assert_cmpint(SCALAR3D_READ(sca,pos,pf),==,0);
    g_assert_cmpint(SCALAR3D_READ(scaE,posE,pfE),==,0);

    beta_value=beta(sca, scaE, 0.5, 2, vac, max_pos, max_vec, 2);
    g_assert_cmpfloat(beta_value,==,3);

    for (i=0; i<3; i++)
        for (j=0; j<2; j++)
        {
            g_assert_cmpfloat(skip[i][j],==,0);
        }

    g_assert_cmpfloat(max_pos[0],==,1./3.);
    g_assert_cmpfloat(max_pos[1],==,1./3.);
    g_assert_cmpfloat(max_pos[2],==,1./3.);

    g_assert_cmpfloat(max_vec[0],==,0);
    g_assert_cmpfloat(max_vec[1],==,0);
    g_assert_cmpfloat(max_vec[2],==,1.5);

    fclose(pf);
    fclose(pfE);

    /*Free*/
    POSCAR_Free(pos);
    SCALAR3D_Free(sca);
    POSCAR_Free(posE);
    SCALAR3D_Free(scaE);
}

void check_beta_hex()
{
    int i,j;
    double d;
    FILE *pf=NULL;
    FILE *pfE=NULL;
    POSCAR *pos=NULL;
    POSCAR *posE=NULL;
    SCALAR3D *sca=NULL;
    SCALAR3D *scaE=NULL;
    double beta_value;
    double vac[3][2];
    double skip[3][2];
    double max_pos[3];
    double max_vec[3];

    /*Init*/
    POSCAR_Init(pos);
    POSCAR_Init(posE);
    SCALAR3D_Init(sca);
    SCALAR3D_Init(scaE);

    for (i=0; i<3; i++)
        for (j=0; j<2; j++)
        {
            vac[i][j]=0;
           skip[i][j]=0;
        }

    /*Read*/
    if ((pf=fopen("data/beta/Hex_E0.0","r"))==NULL)
    {
        g_assert(false);
    }
    else if ((pfE=fopen("data/beta/Hex_E1.0","r"))==NULL)
    {
        g_assert(false);
    }

    g_assert_cmpint(SCALAR3D_READ(sca,pos,pf),==,0);
    g_assert_cmpint(SCALAR3D_READ(scaE,posE,pfE),==,0);

    beta_value=beta(sca, scaE, 1.0, 2, vac, max_pos, max_vec, 2);
    d= pow(1.5*cos(PI/3.),2)+pow(6.+1.5*sin(PI/3.),2)+pow(3.,2);
    g_assert_cmpfloat(beta_value,==,sqrt(d));

    for (i=0; i<3; i++)
        for (j=0; j<2; j++)
            g_assert_cmpfloat(skip[i][j],==,0);

    g_assert_cmpfloat(max_pos[0],==,1/3.);
    g_assert_cmpfloat(max_pos[1],==,0/3.);
    g_assert_cmpfloat(max_pos[2],==,0/3.);

    g_assert_cmpfloat(max_vec[0],==,1.5/2.);
    g_assert_cmpfloat(max_vec[1],==,6.0+1.5*sin(PI/3.));
    g_assert_cmpfloat(max_vec[2],==,3.);


    fclose(pf);
    fclose(pfE);

    /*Free*/
    POSCAR_Free(pos);
    SCALAR3D_Free(sca);
    POSCAR_Free(posE);
    SCALAR3D_Free(scaE);
}

void check_beta_vac()
{
    int i,j;
    double d;
    FILE *pf=NULL;
    FILE *pfE=NULL;
    POSCAR *pos=NULL;
    POSCAR *posE=NULL;
    SCALAR3D *sca=NULL;
    SCALAR3D *scaE=NULL;
    double beta_value;
    double vac[3][2];
    double skip[3][2];
    double max_pos[3];
    double max_vec[3];

    /*Init*/
    POSCAR_Init(pos);
    POSCAR_Init(posE);
    SCALAR3D_Init(sca);
    SCALAR3D_Init(scaE);

    /*Read*/
    if ((pf=fopen("data/beta/Vac_E0.0","r"))==NULL)
    {
        g_assert(false);
    }
    else if ((pfE=fopen("data/beta/Vac_E1.0_Z","r"))==NULL)
    {
        g_assert(false);
    }
    else
    {
        g_assert_cmpint(SCALAR3D_READ(sca,pos,pf),==,0);
        g_assert_cmpint(SCALAR3D_READ(scaE,posE,pfE),==,0);
    }

    fclose(pf);
    fclose(pfE);

    /* No Vaccumm*/
    for (i=0; i<3; i++)
        for (j=0; j<2; j++)
        {
            vac[i][j]=0;
           skip[i][j]=0;
        }

    beta_value=beta(sca, scaE, 1.0, 1, vac, max_pos, max_vec, 2);
    for (i=0; i<3; i++)
        for (j=0; j<2; j++)
        {
            g_assert_cmpfloat(skip[i][j],==,0);
        }
    g_assert_cmpfloat(max_pos[0],==,0);
    g_assert_cmpfloat(max_pos[1],==,5./6.);
    g_assert_cmpfloat(max_pos[2],==,0./6.);

    g_assert_cmpfloat(max_vec[0],==,0); /*-2187*/
    g_assert_cmpfloat(max_vec[1],==,(-9+729)/8.);
    g_assert_cmpfloat(max_vec[2],==,(-128-2187)/8.);

    d= sqrt(pow((-9+729)/8.,2)+pow((-128-2187)/8.,2));
    g_assert_cmpfloat(beta_value,==,d);

    /* Vaccumm*/
    skip[2][0]= -1./12.;
    skip[2][1]=  1./12.;

    beta_value=beta(sca, scaE, 1.0, 0, vac, max_pos, max_vec, 2);

    g_assert_cmpfloat(max_pos[0],==,0./6.);
    g_assert_cmpfloat(max_pos[1],==,5./6.);
    g_assert_cmpfloat(max_pos[2],==,5./6.);

    g_assert_cmpfloat(max_vec[0],==,0);    /*2187*/
    g_assert_cmpfloat(max_vec[1],==,(9-729)/8.);
    g_assert_cmpfloat(max_vec[2],==,(-2187-128)/8.);

    /* Vaccumm*/
    skip[2][0]= -3./12.;
    skip[2][1]=  1./12.;

    beta_value=beta(sca, scaE, 1.0, 0, vac, max_pos, max_vec, 2);

    g_assert_cmpfloat(max_pos[0],==,0);
    g_assert_cmpfloat(max_pos[1],==,5./6.);
    g_assert_cmpfloat(max_pos[2],==,1./6.);

    g_assert_cmpfloat(max_vec[0],==,0);    /*-128*/
    g_assert_cmpfloat(max_vec[1],==,(-4+64)/8.);
    g_assert_cmpfloat(max_vec[2],==,(-1+2187)/8.);

    /* Vaccumm*/
    skip[2][0]= -3./12.;
    skip[2][1]=  3./12.;

    beta_value=beta(sca, scaE, 1.0, 1, vac, max_pos, max_vec, 2);

    g_assert_cmpfloat(max_pos[0],==,0);
    g_assert_cmpfloat(max_pos[1],==,5./6.);
    g_assert_cmpfloat(max_pos[2],==,4./6.);

    g_assert_cmpfloat(max_vec[0],==,0);    /*128*/
    g_assert_cmpfloat(max_vec[1],==,(4-64)/8.);
    g_assert_cmpfloat(max_vec[2],==,(2187-1)/8.);

    /* Vaccumm*/
    skip[2][0]= -5./12.;
    skip[2][1]=  3./12.;

    beta_value=beta(sca, scaE, 1.0, 2, vac, max_pos, max_vec, 2);

    g_assert_cmpfloat(max_pos[0],==,0);
    g_assert_cmpfloat(max_pos[1],==,5./6.);
    g_assert_cmpfloat(max_pos[2],==,2./6.);

    g_assert_cmpfloat(max_vec[0],==,0);    /*-1*/
    g_assert_cmpfloat(max_vec[1],==,0);
    g_assert_cmpfloat(max_vec[2],==,(1+128)/8.);

    /* Vaccumm*/
    skip[2][0]= -5./12.;
    skip[2][1]=  5./12.;

    beta_value=beta(sca, scaE, 1.0, 2, vac, max_pos, max_vec, 2);

    g_assert_cmpfloat(max_pos[0],==,0);
    g_assert_cmpfloat(max_pos[1],==,5./6.);
    g_assert_cmpfloat(max_pos[2],==,3./6.);

    g_assert_cmpfloat(max_vec[0],==,0);    /*1*/
    g_assert_cmpfloat(max_vec[1],==,0);
    g_assert_cmpfloat(max_vec[2],==,(1+128)/8.);

    /* Vaccumm*/
    skip[2][0]= -7./12.;
    skip[2][1]=  5./12.;

    beta_value=beta(sca, scaE, 1.0, 0, vac, max_pos, max_vec, 2);

    g_assert_cmpfloat(max_pos[0],==,-1);
    g_assert_cmpfloat(max_pos[1],==,-1);
    g_assert_cmpfloat(max_pos[2],==,-1);

    g_assert_cmpfloat(max_vec[0],==,0);    /*1*/
    g_assert_cmpfloat(max_vec[1],==,0);
    g_assert_cmpfloat(max_vec[2],==,0);

    /* Vaccumm*/
    skip[1][0]= 9./12.;
    skip[1][1]= 11./12.;
    skip[2][0]= 0;
    skip[2][1]= 0;

    beta_value=beta(sca, scaE, 1.0, 0, vac, max_pos, max_vec, 2);

    g_assert_cmpfloat(max_pos[0],==,0);
    g_assert_cmpfloat(max_pos[1],==,0);
    g_assert_cmpfloat(max_pos[2],==,0.);

    g_assert_cmpfloat(max_vec[0],==,0);    /* -9 */
    g_assert_cmpfloat(max_vec[1],==,(-27+2187)/8.);
    g_assert_cmpfloat(max_vec[2],==,(-4-9)/8.);

    /*Free*/
    POSCAR_Free(pos);
    SCALAR3D_Free(sca);
    POSCAR_Free(posE);
    SCALAR3D_Free(scaE);
}

int main(int argc, char** argv)
{
    g_test_init(&argc, &argv, NULL);
    g_test_add_func ("/beta/cubic",     check_beta_cubic);
    g_test_add_func ("/beta/hex"  ,     check_beta_hex);
    g_test_add_func ("/beta/vac"  ,     check_beta_vac);
    return g_test_run();
 }

