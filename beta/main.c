/**
 * @breif Beta
 * @author Zhi-Quan Huang
 * @date 2012-05-01
 */
#include "vaspC.h"
#include "beta.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    int i,j;

    FILE *pf=NULL;
    FILE *pfE=NULL;
    POSCAR *pos=NULL;
    POSCAR *posE=NULL;
    SCALAR3D *sca=NULL;
    SCALAR3D *scaE=NULL;
    double beta_value;
    double E;
    double skip[3][2];
    double vac[3][2];
    double max_pos[3];
    double max_vec[3];

    if (argc!=4)
    {
        fprintf(stderr, "Usage: beta.x [LOCPOT] [LOCPOT in E] [EFIELD]\n"); 
        exit(1);
    }
    else if ((pf=fopen(argv[1],"r"))==NULL)
    {
        fprintf(stderr,"Open %s failed.\n", argv[0]);          
        exit(1);
    }
    else if ((pfE=fopen(argv[2],"r"))==NULL)
    {
        fprintf(stderr,"Open %s failed.\n", argv[1]);          
        exit(1);
    }
    else if ((sscanf(argv[3],"%lf",&E))!=1)
    {
        fprintf(stderr,"The third argument is floatint number.\n");          
        exit(1);
    }

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

    if ((SCALAR3D_READ(sca,pos,pf))!=0)
    {
        fprintf(stderr,"Read %s failed\n", argv[1]);
    }
    else if ((SCALAR3D_READ(scaE,posE,pfE))!=0)
    {
        fprintf(stderr,"Read %s failed\n", argv[2]);
    }
    else
    {
        FindVac(pos, vac);
    }
        
    beta_value=beta(sca, scaE, E, vac, skip, max_pos, max_vec);

    /*Close*/
    fclose(pf);
    fclose(pfE);

    /*Output*/
    printf("EFILED= %8.3f\n",E);
    printf("BETA  = %8.3f\n",beta_value);
    printf("VAC(a1)(Direct)  = %8.3f %8.3f \n",vac[0][0],vac[0][1]);
    printf("VAC(a2)          = %8.3f %8.3f \n",vac[1][0],vac[1][1]);
    printf("VAC(a3)          = %8.3f %8.3f \n",vac[2][0],vac[2][1]);
    printf("SKIP(a1)(Direct) = %8.3f %8.3f \n",skip[0][0],skip[0][1]);
    printf("SKIP(a2)         = %8.3f %8.3f \n",skip[1][0],skip[1][1]);
    printf("SKIP(a3)         = %8.3f %8.3f \n",skip[2][0],skip[2][1]);
    printf("POS              = %8.3f %8.3f %8.3f\n",max_pos[0],max_pos[1],max_pos[2]);
    printf("VEC              = %8.3f %8.3f %8.3f\n",max_vec[0],max_vec[1],max_vec[2]);

    /*Free*/
    POSCAR_Free(pos);
    SCALAR3D_Free(sca);
    POSCAR_Free(posE);
    SCALAR3D_Free(scaE);

    return 0;
}
