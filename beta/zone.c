#include "vaspC.h"
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>

bool InZone(double vac[3][2], double pos[3])
{
    int i;
    double posShift[3]; 

    for (i=0; i<3; i++) posShift[i]= pos[i];

    for (i=0; i<3; i++) 
    {
        if (vac[i][0] == vac[i][1]) continue;

        if ((posShift[i]<vac[i][0]) && (posShift[i]<vac[i][1]))
        {
            while (posShift[i]<vac[i][0])
            {
                posShift[i]++;
            }

            if (posShift[i]>vac[i][1])
            {
                return false;
            }
        }
        else if ((posShift[i]>vac[i][0]) && (posShift[i]>vac[i][1]))
        {
            while (posShift[i]>vac[i][1])
            {
                posShift[i]--;
            }
            if (posShift[i]<vac[i][0])
            {
                return false;
            }
        }
    }
    return true;
}

void FindAllowed(POSCAR* pos, double vac[3][2], double allow[3][2], int flag)
{
    int i,j;
    double d;

    for (i=0; i<3; i++)
        for (j=0; j<2; j++)
        {
            vac[i][j]=0;
            allow[i][j]=0;
        }

    FindVac(pos, vac);
    if (flag==1) /*full_zone*/ 
    {
        for (i=0; i<3; i++) 
        {
            if (vac[i][0]==vac[i][1]) continue;
            d= fabs(vac[i][1]-vac[i][0]);
            allow[i][0]= vac[i][1] - 0.25*d;
            allow[i][1]= 1.0 + vac[i][0] + 0.25*d;
        }
    }
    else if (flag==0) /*restrict zone*/
    {
        double len[3];

        for (i=0; i<3; i++)
            len[i]=sqrt(dot3D(pos->lat->a[i], pos->lat->a[i]));     

        for (i=0; i<3; i++) 
        {
            int index_surface=-1;
            if (vac[i][0]==vac[i][1]) continue;
            insort(&(pos->atom_pos[0][0]), pos->natom, 3, i, false);
            
            for (j=0; j<pos->natom; j++)
            {
                if (pos->atom_pos[j][i]==vac[i][0])
                {
                    index_surface= j;
                    break;
                }
            }
            if (index_surface==-1) fprintf(stderr,"FindAllowed: Internal Error. index_surface\n");

            double len_min= DBL_MAX;
            int index_min= -1;
            for (j=0; j<pos->natom; j++)
            {
                if (j<=index_surface)       
                    d= pos->atom_pos[index_surface][i]-pos->atom_pos[j][i];
                else
                    d= pos->atom_pos[index_surface][i]-(pos->atom_pos[j][i]-1.0);
                if ((d>(1.0/len[i])) && (d<len_min))
                {
                    len_min= d;
                    index_min= j;
                }
            }
            if (index_min==-1) fprintf(stderr,"FindAllowed: Internal Error. index_min\n");
            allow[i][0]= vac[i][0] - 0.5*len_min;
            allow[i][1]= vac[i][0] + 0.25*(vac[i][1]-vac[i][0]);
        }
    }
    else if (flag==2) /*surface zone*/
    {
        for (i=0; i<3; i++) 
        {
            if (vac[i][0]==vac[i][1]) continue;
            allow[i][0]= vac[i][0];
            allow[i][1]= vac[i][0] + 0.25*(vac[i][1]-vac[i][0]);
        }
    }
    else
    {
        fprintf(stderr, "FindAllowed: Interal Error %d\n", flag);
        exit(1);
    }
}
