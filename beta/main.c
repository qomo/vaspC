/**
 * @breif Beta
 * @author Zhi-Quan Huang
 * @date 2012-05-01
 */
#include "vaspC.h"
#include "beta.h"
#include "zone.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

static int zone_flag=2; /*1-full_zone, 0-restrict_zone, 2-outer surface zone*/
static int algo_flag=5; /*2-two points, 5-five points*/

int main(int argc, char* argv[])
{
    int c;
    int i,j;

    FILE *pf=NULL;
    FILE *pfE=NULL;
    POSCAR *pos=NULL;
    POSCAR *posE=NULL;
    SCALAR3D *sca=NULL;
    SCALAR3D *scaE=NULL;
    double beta_value=0;
    double E=0, EFIELD=0;
    int directionE=-1;
    double allow[3][2];
    double vac[3][2];
    double max_pos[3];
    double max_vec[3];
     
    /*Init*/
    for (i=0; i<3; i++)
    {
        max_pos[i]= 0;
        max_vec[i]= 0;
    }

    for (i=0; i<3; i++)
        for (j=0; j<2; j++)
        {
            vac[i][j]= 0;
            allow[i][j]=0;
        }
    
    /*getopt_long*/
    while(1)
    {
        static struct option long_options[]={
        {"full",     no_argument, 0, 'f'},
        {"restrict", no_argument, 0, 'r'},
        {"surface",  no_argument, 0, 's'},
        {"two_points", no_argument, 0, '2'},
        {"five_points", no_argument, 0, '5'},
        {         0,           0, 0, 0}
        };

        int option_index=0;

        c= getopt_long(argc, argv, "25rfs", long_options, &option_index); 

        if (c==-1) break;
        switch(c)
        {
            case 'f':
                zone_flag=1;
                break;
            case 'r':
                zone_flag=0;
                break;
            case 's':
                zone_flag=2;
                break;
            case '2':
                algo_flag=2;
                break;
            case '5':
                algo_flag=5;
                break;
            case '?':
                break;
            default:
                abort();
        }
    }   

    /*Check arguments*/
    if ((argc-optind)!=4)
    {
        fprintf(stderr, "Usage: beta.x [LOCPOT] [LOCPOT in E] [EFIELD] [0-X 1-Y 2-Z]\n"); 
        exit(1);
    }
    else if ((pf=fopen(argv[optind],"r"))==NULL)
    {
        fprintf(stderr,"Open %s failed.\n", argv[optind]);          
        exit(1);
    }
    else if ((pfE=fopen(argv[optind+1],"r"))==NULL)
    {
        fprintf(stderr,"Open %s failed.\n", argv[optind+1]);          
        exit(1);
    }
    else if ((sscanf(argv[optind+2],"%lf",&EFIELD))!=1)
    {
        fprintf(stderr,"The third argument is floatint number.\n");          
        exit(1);
    }
    else if ((sscanf(argv[optind+3],"%d",&directionE))!=1)
    {
        fprintf(stderr,"The forth argument is floatint number.\n");          
        exit(1);
    }

    if ((directionE>2)||(directionE<0))
    {
        fprintf(stderr,"The forth argument must be 0, 1, or 2.\n");          
        exit(1);
    }


    /*Init*/
    if (EFIELD < 0) fprintf(stderr, "ERROR: not support EFIELD < 0.\n");
    E= -EFIELD;
    POSCAR_Init(pos);
    POSCAR_Init(posE);
    SCALAR3D_Init(sca);
    SCALAR3D_Init(scaE);


    if ((SCALAR3D_READ(sca,pos,pf))!=0)
    {
        fprintf(stderr,"Read %s failed\n", argv[optind]);
    }
    else if ((SCALAR3D_READ(scaE,posE,pfE))!=0)
    {
        fprintf(stderr,"Read %s failed\n", argv[optind+1]);
    }
    else
    {
        FindAllowed( pos, vac, allow, zone_flag);
    }
        
    beta_value=beta(sca, scaE, E, directionE, allow, max_pos, max_vec, algo_flag);

    /*Close*/
    fclose(pf);
    fclose(pfE);

    /*Output*/
    printf("BETA  = %8.3f\n\n",beta_value);
    printf("EFILED              = %8.3f\n",EFIELD);
    printf("E_apply             = %8.3f\n",E);
    printf("Vacuum(a1)(Direct)  = %8.3f %8.3f \n",vac[0][0],vac[0][1]);
    printf("Vacuum(a2)          = %8.3f %8.3f \n",vac[1][0],vac[1][1]);
    printf("Vacuum(a3)          = %8.3f %8.3f \n",vac[2][0],vac[2][1]);
    printf("Allowed zone(a1)(Direct)= %8.3f %8.3f \n",allow[0][0],allow[0][1]);
    printf("Allowed zone(a2)        = %8.3f %8.3f \n",allow[1][0],allow[1][1]);
    printf("Allowed zone(a3)        = %8.3f %8.3f \n",allow[2][0],allow[2][1]);
    printf("POS        = %8.3f %8.3f %8.3f\n",max_pos[0],max_pos[1],max_pos[2]);
    printf("E_loc      = %8.3f %8.3f %8.3f\n",max_vec[0],max_vec[1],max_vec[2]);

    /*Free*/
    POSCAR_Free(pos);
    SCALAR3D_Free(sca);
    POSCAR_Free(posE);
    SCALAR3D_Free(scaE);

    return 0;
}
