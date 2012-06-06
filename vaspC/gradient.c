/**
 * Author: Zhi-Quan Huang
 * Date: 2012-05-18
 */

#include "index.h"
#include <stdio.h>

void Threept3d(double* val, int ngx, int ngy, int ngz,
          double dx, double dy, double dz, 
          double (*vector)[3])
{
    int i,j,k,index;    
    int preX,postX;
    int preY,postY;
    int preZ,postZ;

    for (k=0; k<ngz; k++)
    {
        for (j=0; j<ngy; j++)
            for (i=0; i<ngx; i++)
            {
                if (i!=0) 
                    preX=M3dT1d(  i-1, j, k, ngx,ngy,ngz);
                else
                    preX=M3dT1d(ngx-1, j, k, ngx,ngy,ngz);
    
                if (i!=ngx-1)
                    postX=M3dT1d( i+1, j, k, ngx,ngy,ngz);
                else
                    postX=M3dT1d(   0, j, k, ngx,ngy,ngz);

                if (j!=0)
                    preY= M3dT1d( i,   j-1, k, ngx,ngy,ngz);
                else
                    preY= M3dT1d( i, ngy-1, k, ngx,ngy,ngz);
            
                if (j!=ngy-1)
                    postY= M3dT1d( i, j+1, k,ngx,ngy,ngz);
                else
                    postY= M3dT1d( i,   0, k,ngx,ngy,ngz);

                if (k!=0)
                    preZ= M3dT1d( i, j, k-1, ngx,ngy,ngz);
                else
                    preZ= M3dT1d( i, j, ngz-1, ngx,ngy,ngz);

                if (k!=ngz-1)
                    postZ= M3dT1d( i, j, k+1, ngx,ngy,ngz);
                else
                    postZ= M3dT1d( i, j, 0, ngx,ngy,ngz);
            
                index=M3dT1d(i,j,k,ngx,ngy,ngz);
                vector[index][0]=val[postX]-val[preX];
                vector[index][1]=val[postY]-val[preY];
                vector[index][2]=val[postZ]-val[preZ];
            }
    }

    for (i=0; i<ngx*ngy*ngz; i++)
    {
        vector[i][0]/= 2*dx;
        vector[i][1]/= 2*dy;
        vector[i][2]/= 2*dz;
    }
}

void Fivept3d(double* val, int ngx, int ngy, int ngz,
          double dx, double dy, double dz, 
          double (*vector)[3])
{
    int i,j,k,index;    
    int X_ii, X_i, X_I, X_II;
    int Y_ii, Y_i, Y_I, Y_II;
    int Z_ii, Z_i, Z_I, Z_II;

    for (k=0; k<ngz; k++)
    {
        for (j=0; j<ngy; j++)
            for (i=0; i<ngx; i++)
            {
                X_ii= M3dT1d(  ((i-2)+10*ngx)%ngx, j, k, ngx,ngy,ngz);
                X_i = M3dT1d(  ((i-1)+10*ngx)%ngx, j, k, ngx,ngy,ngz);
                X_I = M3dT1d(  ((i+1)+10*ngx)%ngx, j, k, ngx,ngy,ngz);
                X_II= M3dT1d(  ((i+2)+10*ngx)%ngx, j, k, ngx,ngy,ngz);
            
                Y_ii= M3dT1d(  i,((j-2)+10*ngy)%ngy, k, ngx,ngy,ngz);
                Y_i = M3dT1d(  i,((j-1)+10*ngy)%ngy, k, ngx,ngy,ngz);
                Y_I = M3dT1d(  i,((j+1)+10*ngy)%ngy, k, ngx,ngy,ngz);
                Y_II= M3dT1d(  i,((j+2)+10*ngy)%ngy, k, ngx,ngy,ngz);

                Z_ii= M3dT1d(  i, j, ((k-2)+10*ngz)%ngz, ngx,ngy,ngz);
                Z_i = M3dT1d(  i, j, ((k-1)+10*ngz)%ngz, ngx,ngy,ngz);
                Z_I = M3dT1d(  i, j, ((k+1)+10*ngz)%ngz, ngx,ngy,ngz);
                Z_II= M3dT1d(  i, j, ((k+2)+10*ngz)%ngz, ngx,ngy,ngz);

                index=M3dT1d(i,j,k,ngx,ngy,ngz);
                vector[index][0]=val[X_ii]-8*val[X_i]+8*val[X_I]-val[X_II];
                vector[index][1]=val[Y_ii]-8*val[Y_i]+8*val[Y_I]-val[Y_II];
                vector[index][2]=val[Z_ii]-8*val[Z_i]+8*val[Z_I]-val[Z_II];
            }
    }

    for (i=0; i<ngx*ngy*ngz; i++)
    {
        vector[i][0]/= 12*dx;
        vector[i][1]/= 12*dy;
        vector[i][2]/= 12*dz;
    }
}
