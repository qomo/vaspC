#include "vaspC.h"
#include <stdbool.h>
#include <math.h>

#define ALLOW_SPACE 10

bool InZone(double vac[3][2], double pos[3])
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

void FindAllowed(POSCAR* pos, double vac[3][2], double allow[3][2])
{
    int i,j;
    double len[3]={ 0, 0, 0};
    for (i=0; i<3; i++)
        for (j=0; j<2; j++)
        {
            vac[i][j]=0;
            allow[i][j]=0;
        }
    
    for (i=0; i<3; i++)
    {
        len[i]=sqrt(dot3D(pos->lat->a[i], pos->lat->a[i]));
    }

    FindVac(pos, vac);

    for (i=0; i<3; i++) 
    {
        if (vac[i][0]==vac[i][1]) continue;
        allow[i][0]= vac[i][0] - ALLOW_SPACE/len[i];
        allow[i][1]= vac[i][0] + ALLOW_SPACE/len[i];
    }
}

