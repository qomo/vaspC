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

void Five3d(double* val, int ngx, int ngy, int ngz,
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
