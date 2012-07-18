/**
 * @Date 2012-04-18
 * @Author Zhi-Quan Huang
 */

#include "vaspC.h"
#include "glib.h"
#include <math.h>

void check_LATTICE_A2B()
{
    int i,j;
    double d[3][3];
    LATTICE* lat=NULL;

    LATTICE_Init(lat);

    lat->a[0][0]=0;
    lat->a[0][1]=1;
    lat->a[0][2]=2;
    lat->a[1][0]=2;
    lat->a[1][1]=1;
    lat->a[1][2]=4;
    lat->a[2][0]=1;
    lat->a[2][1]=4;
    lat->a[2][2]=1;

    LATTICE_A2B(lat);

    d[0][0]= lat->b[0][0]-(-15./16.); 
    d[0][1]= lat->b[0][1]-(  2./16.); 
    d[0][2]= lat->b[0][2]-(  7./16.); 

    d[1][0]= lat->b[1][0]-(  7./16.); 
    d[1][1]= lat->b[1][1]-( -2./16.); 
    d[1][2]= lat->b[1][2]-(  1./16.); 

    d[2][0]= lat->b[2][0]-(  2./16.); 
    d[2][1]= lat->b[2][1]-(  4./16.); 
    d[2][2]= lat->b[2][2]-( -2./16.); 

    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
        {
            g_assert_cmpfloat(fabs(d[i][j]),<,1e-14); 
        }
    LATTICE_Free(lat);
}

void check_LATTICE_D2C()
{
    int i;
    double d[3];
    double pos[3]={0.25, 0.5, 0.75};

    LATTICE* lat=NULL;

    /*init*/
    LATTICE_Init(lat);
    lat->a[0][0]=0;
    lat->a[0][1]=1;
    lat->a[0][2]=2;
    lat->a[1][0]=2;
    lat->a[1][1]=1;
    lat->a[1][2]=4;
    lat->a[2][0]=1;
    lat->a[2][1]=4;
    lat->a[2][2]=1;
    LATTICE_A2B(lat);

    LATTICE_D2C(lat, pos);

    d[0]= pos[0]- 7./4.; 
    d[1]= pos[1]- 15./4.; 
    d[2]= pos[2]- 13./4.; 

    for (i=0; i<3; i++)    
    {
        g_assert_cmpfloat(fabs(d[i]),<,1e-14); 
    } 

    LATTICE_Free(lat);
}

void check_LATTICE_C2D()
{
    int i;
    double d[3];
    double pos[3]={7./4., 15./4., 13./4.};
    LATTICE* lat=NULL;

    LATTICE_Init(lat);

    /*init*/
    LATTICE_Init(lat);
    lat->a[0][0]=0;
    lat->a[0][1]=1;
    lat->a[0][2]=2;
    lat->a[1][0]=2;
    lat->a[1][1]=1;
    lat->a[1][2]=4;
    lat->a[2][0]=1;
    lat->a[2][1]=4;
    lat->a[2][2]=1;
    LATTICE_A2B(lat);
    
    LATTICE_C2D(lat, pos);

    d[0]= pos[0]- 1./4.; 
    d[1]= pos[1]- 2./4.; 
    d[2]= pos[2]- 3./4.; 

    for (i=0; i<3; i++)    
    {
        g_assert_cmpfloat(fabs(d[i]),<,1e-14); 
    } 

    LATTICE_Free(lat);
}
