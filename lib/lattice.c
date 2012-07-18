/**
 * @Date 2012-04-18
 * @Author Zhi-Quan Huang
 */

#include "lattice.h"
#include "vmath.h"
#include <stdlib.h>
#include <stdio.h>

void _LATTICE_Init(LATTICE** lat)
{
    int i,j;

    if (*lat!=NULL) _LATTICE_Free(lat);
    *lat= malloc(sizeof(LATTICE));
    if (*lat==NULL)
    {
        fprintf(stderr, "LATTICE_Init: Memory Allocate Error.\n");
        exit(1); 
    }

    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
        {
            (*lat)->a[i][j]= (i==j)?1:0;
            (*lat)->b[i][j]= (i==j)?1:0;
        }
}

void _LATTICE_Free(LATTICE** lat)
{
    if (*lat!=NULL)
    { 
        free(*lat);
        *lat=NULL;
    }
}

void LATTICE_Copy(LATTICE* lat, LATTICE** cplat)
{
    int i,j;

    if (*cplat!=NULL) _LATTICE_Free(cplat);
    _LATTICE_Init(cplat);

    for(i=0; i<3; i++)
        for (j=0; j<3; j++)
        {
            (*cplat)->a[i][j]= lat->a[i][j];
            (*cplat)->b[i][j]= lat->b[i][j];
        }
}

void LATTICE_A2B(LATTICE* lat)
{
    int i,j;
    double vol;

    cross3D(lat->a[1],lat->a[2], lat->b[0]);
    cross3D(lat->a[2],lat->a[0], lat->b[1]);
    cross3D(lat->a[0],lat->a[1], lat->b[2]);
    vol= dot3D(lat->b[0], lat->a[0]); 

    for (i=0; i<3; i++)
        for (j=0; j<3; j++)
            lat->b[i][j]/=vol; 

}

void LATTICE_D2C(LATTICE* lat, double pos[3])
{
    int i;
    double vec3[3];
    
    for (i=0; i<3; i++) vec3[i]=pos[i];

    pos[0]= vec3[0]*lat->a[0][0]+vec3[1]*lat->a[1][0]+vec3[2]*lat->a[2][0];
    pos[1]= vec3[0]*lat->a[0][1]+vec3[1]*lat->a[1][1]+vec3[2]*lat->a[2][1];
    pos[2]= vec3[0]*lat->a[0][2]+vec3[1]*lat->a[1][2]+vec3[2]*lat->a[2][2];

}

void LATTICE_C2D(LATTICE* lat, double pos[3])
{
    int i;
    double vec3[3];

    for (i=0; i<3; i++) vec3[i]=pos[i];

    pos[0]= vec3[0]*lat->b[0][0]+vec3[1]*lat->b[0][1]+vec3[2]*lat->b[0][2];
    pos[1]= vec3[0]*lat->b[1][0]+vec3[1]*lat->b[1][1]+vec3[2]*lat->b[1][2];
    pos[2]= vec3[0]*lat->b[2][0]+vec3[1]*lat->b[2][1]+vec3[2]*lat->b[2][2];
}


