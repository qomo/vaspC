/**
 * @Author Zhi-Quan Huang
 * @Date 2012-04-18
 */
#include "vaspC.h"
#include "zone.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

/**
 * @brief  
 * @param [in] loc     LOCPOT
 * @param [in] locE    LOCPOT in external E field
 * @param [in] applyE  external E field (eV/A)
 * @param [in] directionE 0-X 1-Y 2-Z
 * @param [in] allow   allowed zone (Direct coordinates) 
 * @param [out] max_pos position of max difference (Direct coordinate)
 * @param [out] max_vec vector of max difference (Direct coordinate)
 */
double beta(SCALAR3D* loc, SCALAR3D* locE, double applyE, int directionE,
            double allow[3][2], 
            double max_pos[3], double max_vec[3])
{
    int i,j,k,n;
    double temp[3];
    double d;
    double pos[3];
    
    
    int NGX,NGY,NGZ,TGRID;
    LATTICE *AXIS=NULL; 
    double LEN[3], DX,DY,DZ;

    LATTICE_Init(AXIS); 

    /* if (> skip[i][0]) and (< skip[i][1]) => ignore E Field (Direct) */
    double maxE;
    double (*diffE)[3]=NULL;
    double *diffLoc=NULL;

    /* check */
    if (loc==NULL)
    {
        fprintf(stderr, "Internal Error (beta): loc is NULL pointer.\n");
        exit(1);
    }
    else if (locE==NULL)
    {
        fprintf(stderr, "Internal Error (beta): loc is NULL pointer.\n");
        exit(1);
    }

    for (i=0; i<3; i++)
    {
        if (loc->ngrid[i]!=locE->ngrid[i])
        {
            fprintf(stderr, "Internal Error (beta): ngrid of loc and locE are different.\n");
            exit(1);
        }
        else
        {
            if (i==0) NGX= loc->ngrid[0];
            if (i==1) NGY= loc->ngrid[1];
            if (i==2) NGZ= loc->ngrid[2];
        }
    }
    TGRID= NGX*NGY*NGZ;

    for (i=0; i<3; i++)
    {
        for (j=0; j<3; j++) 
        {
            if(loc->axis[i][j]!=locE->axis[i][j])             
            {
                fprintf(stderr, "Internal Error (beta): axis of loc and locE are different.\n");
                exit(1);
            }
            else
            {
                AXIS->a[i][j]=loc->axis[i][j];
            }
        }
    }
    
    for (i=0; i<3; i++) LEN[i]= sqrt(dot3D(AXIS->a[i],AXIS->a[i]));
    LATTICE_A2B(AXIS);

    if ((diffLoc=malloc(sizeof(double)*TGRID))==NULL)
    {
        fprintf(stderr, "Internal Error (beta): diffLoc memory allocate error.\n");
        exit(1);
    }
    else if ((diffE=malloc(sizeof(double)*TGRID*3))==NULL)
    {
        fprintf(stderr, "Internal Error (beta): diffE memory allocate error.\n");
        exit(1);
    }

    DX= LEN[0]/(double)NGX;
    DY= LEN[1]/(double)NGY;
    DZ= LEN[2]/(double)NGZ;

    for (i=0; i<TGRID; i++)
    {
        diffLoc[i]= locE->val[i]-loc->val[i];
    }

    /*Threept3d(diffLoc, NGX, NGY, NGZ, DX, DY, DZ, diffE);*/
    Fivept3d(diffLoc, NGX, NGY, NGZ, DX, DY, DZ, diffE);

    for (i=0; i<NGX; i++)
    for (j=0; j<NGY; j++)
    for (k=0; k<NGZ; k++)
    {
        n=M3dT1d(i,j,k,NGX,NGY,NGZ);
        /*printf("(%2d %2d %2d)->(%2.2f %2.2f %2.2f)\n",i,j,k,diffE[n][0],diffE[n][1],diffE[n][2]);*/
    }
    /*Construct \frac{\parital a_i}{\partial x_j}*/
    for (i=0; i<3; i++) 
    {
        AXIS->a[0][i]/= LEN[0];
        AXIS->a[1][i]/= LEN[1];
        AXIS->a[2][i]/= LEN[2];
    }
    /*Translate to Cart Coordinates*/
    for (i=0; i<NGX; i++)
        for (j=0; j<NGY; j++)
            for (k=0; k<NGZ; k++)
            {
                n=M3dT1d(i,j,k,NGX,NGY,NGZ);
                temp[0]= diffE[n][0]*AXIS->a[0][0]+diffE[n][1]*AXIS->a[1][0]+diffE[n][2]*AXIS->a[2][0];
                temp[1]= diffE[n][0]*AXIS->a[0][1]+diffE[n][1]*AXIS->a[1][1]+diffE[n][2]*AXIS->a[2][1];
                temp[2]= diffE[n][0]*AXIS->a[0][2]+diffE[n][1]*AXIS->a[1][2]+diffE[n][2]*AXIS->a[2][2];
                
                diffE[n][0]= temp[0]; 
                diffE[n][1]= temp[1]; 
                diffE[n][2]= temp[2]; 
            }

    for (i=0; i<3; i++)
    {
        max_pos[i]= -1;
        max_vec[i]= 0;
        maxE=0;
    }

    for (i=0; i<NGX; i++)
        for (j=0; j<NGY; j++)
            for (k=0; k<NGZ; k++)
            {
                pos[0]= (double)i/(double)NGX;
                pos[1]= (double)j/(double)NGY;
                pos[2]= (double)k/(double)NGZ;

                if (!InZone(allow,pos)) continue;

                n=M3dT1d(i,j,k,NGX,NGY,NGZ);
                if (diffE[n][directionE]>=0) continue;
                d= sqrt(dot3D(diffE[n],diffE[n]));
                if (d>maxE)
                {
                    maxE=d;
                    max_pos[0]= (double)i/(double)NGX;
                    max_pos[1]= (double)j/(double)NGY;
                    max_pos[2]= (double)k/(double)NGZ;
                    max_vec[0]= diffE[n][0];
                    max_vec[1]= diffE[n][1];
                    max_vec[2]= diffE[n][2];
                }
            }

    LATTICE_Free(AXIS); 
    free(diffLoc);
    free(diffE);

    return maxE/(-applyE);
}
