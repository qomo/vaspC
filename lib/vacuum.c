/**
 * @Author Zhi-Quan Huang
 * @Date 2012-04-18
 */

#include "vaspC.h"
#include "insort.h"
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#define VAC_SPACE 6

/**
 * @brief Find the largest interval of projection coordinates
          if the interval is large then VAC_SPACE.
          If we can find any one are satified in the i dierction, 
          then
             vac[i][0]= 0   
             vac[i][1]= 0   
 * @param pos
 * @param vac (Direct Coordinates)
 */
void FindVac( POSCAR* pos, double vac[3][2])
{
    int i,j,v;
    double post;
    double len[3];
    double *interval=NULL;
    double max_interval=-1;
    POSCAR* posTmp=NULL;

    /*Init*/
    for (i=0; i<3; i++)
        for (j=0; j<2; j++)
            vac[i][j]=0;

    POSCAR_Copy(pos, posTmp);
    POSCAR_C2D(posTmp);
    POSCAR_Confined(posTmp);

    for (i=0; i<3; i++)
    {
        len[i]= dot3D(posTmp->lat->a[i], posTmp->lat->a[i]);
        len[i]= sqrt(len[i]);
    }

    interval= malloc(sizeof(double)*posTmp->natom); 
    if (interval==NULL)
    {
        fprintf(stderr, "POSCAR_FindVac: Memory Allocate Error.\n");
        exit(1);
    }

    for (v=0; v<3; v++)
    {
        insort(&(posTmp->atom_pos[0][0]), posTmp->natom, 3, v, false);
        for (i=0; i<posTmp->natom; i++)
        {
            if (i==posTmp->natom-1)
                post= posTmp->atom_pos[0][v]+1.0; 
            else
                post= posTmp->atom_pos[i+1][v]; 
            interval[i]=(post-posTmp->atom_pos[i][v])*len[v];

            if (interval[i]>max_interval &&  interval[i]>VAC_SPACE)
            {
                vac[v][0]= posTmp->atom_pos[i][v];
                vac[v][1]= post; 
            }
        }
    }

    free(interval);
    POSCAR_Free(posTmp);
}

/**
 * @brief determine the pos is in vacuum.
 * @detail if we can find one of pos with the period conditions in vacuum (>vac[][0] and <vac[][1]),
           then return true
 * @param vac (Direct Coordinates)
 * @param pos (Direct Coordinates)
 */
bool InVac(double vac[3][2], double pos[3])
{
    int i;
    double posShift[3]; 

    for (i=0; i<3; i++) posShift[i]= pos[i];

    for (i=0; i<3; i++) 
    {
        while (posShift[i]<vac[i][0])
        {
            posShift[i]++;
        }

        if (posShift[i]<vac[i][1])
        {
            return true;
        }
    }
    
    for (i=0; i<3; i++) 
    {
        while (posShift[i]>vac[i][1])
        {
            posShift[i]--;
        }
        if (posShift[i]>vac[i][0])
        {
            return true;
        }
    }
    return false;
}
