#include "glib.h"
#include "vaspC.h"

#include <stdio.h>
#include <stdbool.h>

void check_POTCAR_New_Free()
{
    POTCAR* pot= POTCAR_New();
    POTCAR_Free(pot);
}

void check_POTCAR_Set_Get()
{
    POTCAR* pot= POTCAR_New();

    char* str1= "ten";
    char* ret1= POTCAR_Set(pot, "10", POINTER_MALLOC(str1, char, strlen(str1)+1));

    g_assert_cmpstr(str1,==,ret1);

    char* str2= "tenten";
    char* ret2= POTCAR_Set(pot, "10", POINTER_MALLOC(str2, char, strlen(str2)+1));
    g_assert_cmpstr(str2,==,ret2);

    char* ret3= POTCAR_Get(pot, "10");
    g_assert_cmpstr(ret3,==, str2);

    POTCAR_Free(pot);
}

void check_File_Count_POTCAR()
{
    FILE *pf= NULL;
    g_assert((pf=fopen("data/potcar/POTCAR_BCN_PAW_PBE","r"))!=NULL);
    int count= File_Count_POTCAR(pf);
    g_assert_cmpint(3,==,count);
}

void check_POTCAR_Array_New_Free()
 {
    FILE *pf= NULL;
    g_assert((pf=fopen("data/potcar/POTCAR_BCN_PAW_PBE","r"))!=NULL);

    int pot_array_num=0;
    POTCAR** pot_array= POTCAR_New_Array_From_File( pf, &pot_array_num);
    g_assert_cmpint(pot_array_num,==,3);

    /* POTCAR B */
    {
        POTCAR* pot= pot_array[0];

        /* VRHFIN */
        char** VRHFIN= POTCAR_Get(pot, "VRHFIN");
        g_assert(VRHFIN!=NULL);
        g_assert_cmpstr(VRHFIN[0],==,"B");
        g_assert_cmpstr(VRHFIN[1],==,"s2p1");
    
        /*LEXCH*/
        char* LEXCH= POTCAR_Get(pot, "LEXCH");
        g_assert(LEXCH!=NULL);
        g_assert_cmpstr(LEXCH,==,"PE");

        /*EATOM*/
        double* EATOM= POTCAR_Get(pot, "EATOM");
        g_assert(EATOM!=NULL);
        g_assert_cmpfloat(*EATOM,==,71.1810);

        /*TITEL*/
        char** TITEL= POTCAR_Get(pot, "TITEL");
        g_assert(TITEL!=NULL);
        g_assert_cmpstr(TITEL[0],==,"PAW_PBE");
        g_assert_cmpstr(TITEL[1],==,"B");
        g_assert_cmpstr(TITEL[2],==,"06Sep2000");

        /*LULTRA*/
        bool* LULTRA= POTCAR_Get(pot,"LULTRA");
        g_assert(LULTRA!=NULL);
        g_assert(!(*LULTRA));

        /*IUNSCR*/
        int* IUNSCR= POTCAR_Get(pot,"IUNSCR");
        g_assert(IUNSCR!=NULL);
        g_assert_cmpint(*IUNSCR,==,0);

        /*RPACOR*/
        double* RPACOR= POTCAR_Get(pot,"RPACOR");
        g_assert(RPACOR!=NULL);
        g_assert_cmpfloat(*RPACOR,==,0);

        /*POMASS*/
        double* POMASS= POTCAR_Get(pot,"POMASS");
        g_assert(POMASS!=NULL);
        g_assert_cmpfloat(*POMASS,==,10.811);

        /*ZVAL*/
        double* ZVAL= POTCAR_Get(pot,"ZVAL");
        g_assert(ZVAL!=NULL);
        g_assert_cmpfloat(*ZVAL,==,3);

        /*RCORE*/
        double* RCORE= POTCAR_Get(pot,"RCORE");
        g_assert(RCORE!=NULL);
        g_assert_cmpfloat(*RCORE,==,1.700);

        /*RWIGS*/
        double* RWIGS= POTCAR_Get(pot,"RWIGS");
        g_assert(RWIGS!=NULL);
        g_assert_cmpfloat(*RWIGS,==, .905);

        /*ENMAX*/
        double* ENMAX= POTCAR_Get(pot,"ENMAX");
        g_assert(ENMAX!=NULL);
        g_assert_cmpfloat(*ENMAX,==, 318.606);

        /*ENMIN*/
        double* ENMIN= POTCAR_Get(pot,"ENMIN");
        g_assert(ENMIN!=NULL);
        g_assert_cmpfloat(*ENMIN,==, 238.954);

        /*ICORE*/
        int* ICORE= POTCAR_Get(pot, "ICORE");
        g_assert(ICORE!=NULL);
        g_assert_cmpint(*ICORE,==,2);

        /*LCOR*/
        bool* LCOR= POTCAR_Get(pot, "LCOR");
        g_assert(LCOR!=NULL);
        g_assert(*LCOR);

        /*LPAW*/
        bool* LPAW= POTCAR_Get(pot, "LPAW");
        g_assert(LPAW!=NULL);
        g_assert(*LPAW);

        /*EAUG*/
        double* EAUG= POTCAR_Get(pot,"EAUG");
        g_assert(EAUG!=NULL);
        g_assert_cmpfloat(*EAUG,==, 535.514);

        /*DEXC*/
        double* DEXC= POTCAR_Get(pot,"DEXC");
        g_assert(DEXC!=NULL);
        g_assert_cmpfloat(*DEXC,==, 0);

        /*RMAX*/
        double* RMAX= POTCAR_Get(pot,"RMAX");
        g_assert(RMAX!=NULL);
        g_assert_cmpfloat(*RMAX,==, 2.583);

        /*RAUG*/
        double* RAUG= POTCAR_Get(pot,"RAUG");
        g_assert(RAUG!=NULL);
        g_assert_cmpfloat(*RAUG,==, 1.300);

        /*RDEP*/
        double* RDEP= POTCAR_Get(pot,"RDEP");
        g_assert(RDEP!=NULL);
        g_assert_cmpfloat(*RDEP,==, 1.757);

        /*QCUT*/
        double* QCUT= POTCAR_Get(pot,"QCUT");
        g_assert(QCUT!=NULL);
        g_assert_cmpfloat(*QCUT,==, -4.839);

        /*QGAM*/
        double* QGAM= POTCAR_Get(pot,"QGAM");
        g_assert(QGAM!=NULL);
        g_assert_cmpfloat(*QGAM,==, 9.678);
    } 

    /* POTCAR C */
    {
        POTCAR* pot= pot_array[1];

        /* VRHFIN */
        char** VRHFIN= POTCAR_Get(pot, "VRHFIN");
        g_assert(VRHFIN!=NULL);
        g_assert_cmpstr(VRHFIN[0],==,"C");
        g_assert_cmpstr(VRHFIN[1],==,"s2p2");
    
        /*LEXCH*/
        char* LEXCH= POTCAR_Get(pot, "LEXCH");
        g_assert(LEXCH!=NULL);
        g_assert_cmpstr(LEXCH,==,"PE");

        /*EATOM*/
        double* EATOM= POTCAR_Get(pot, "EATOM");
        g_assert(EATOM!=NULL);
        g_assert_cmpfloat(*EATOM,==, 147.1560);

        /*TITEL*/
        char** TITEL= POTCAR_Get(pot, "TITEL");
        g_assert(TITEL!=NULL);
        g_assert_cmpstr(TITEL[0],==,"PAW_PBE");
        g_assert_cmpstr(TITEL[1],==,"C");
        g_assert_cmpstr(TITEL[2],==,"08Apr2002");

        /*LULTRA*/
        bool* LULTRA= POTCAR_Get(pot,"LULTRA");
        g_assert(LULTRA!=NULL);
        g_assert(!(*LULTRA));

        /*IUNSCR*/
        int* IUNSCR= POTCAR_Get(pot,"IUNSCR");
        g_assert(IUNSCR!=NULL);
        g_assert_cmpint(*IUNSCR,==,0);

        /*RPACOR*/
        double* RPACOR= POTCAR_Get(pot,"RPACOR");
        g_assert(RPACOR!=NULL);
        g_assert_cmpfloat(*RPACOR,==,0);

        /*POMASS*/
        double* POMASS= POTCAR_Get(pot,"POMASS");
        g_assert(POMASS!=NULL);
        g_assert_cmpfloat(*POMASS,==,12.011);

        /*ZVAL*/
        double* ZVAL= POTCAR_Get(pot,"ZVAL");
        g_assert(ZVAL!=NULL);
        g_assert_cmpfloat(*ZVAL,==,4);

        /*RCORE*/
        double* RCORE= POTCAR_Get(pot,"RCORE");
        g_assert(RCORE!=NULL);
        g_assert_cmpfloat(*RCORE,==,1.500);

        /*RWIGS*/
        double* RWIGS= POTCAR_Get(pot,"RWIGS");
        g_assert(RWIGS!=NULL);
        g_assert_cmpfloat(*RWIGS,==, .863);

        /*ENMAX*/
        double* ENMAX= POTCAR_Get(pot,"ENMAX");
        g_assert(ENMAX!=NULL);
        g_assert_cmpfloat(*ENMAX,==, 400);

        /*ENMIN*/
        double* ENMIN= POTCAR_Get(pot,"ENMIN");
        g_assert(ENMIN!=NULL);
        g_assert_cmpfloat(*ENMIN,==, 300);

        /*ICORE*/
        int* ICORE= POTCAR_Get(pot, "ICORE");
        g_assert(ICORE!=NULL);
        g_assert_cmpint(*ICORE,==,2);

        /*LCOR*/
        bool* LCOR= POTCAR_Get(pot, "LCOR");
        g_assert(LCOR!=NULL);
        g_assert(*LCOR);

        /*LPAW*/
        bool* LPAW= POTCAR_Get(pot, "LPAW");
        g_assert(LPAW!=NULL);
        g_assert(*LPAW);

        /*EAUG*/
        double* EAUG= POTCAR_Get(pot,"EAUG");
        g_assert(EAUG!=NULL);
        g_assert_cmpfloat(*EAUG,==, 644.873);

        /*DEXC*/
        double* DEXC= POTCAR_Get(pot,"DEXC");
        g_assert(DEXC!=NULL);
        g_assert_cmpfloat(*DEXC,==, 0);

        /*RMAX*/
        double* RMAX= POTCAR_Get(pot,"RMAX");
        g_assert(RMAX!=NULL);
        g_assert_cmpfloat(*RMAX,==, 2.266);

        /*RAUG*/
        double* RAUG= POTCAR_Get(pot,"RAUG");
        g_assert(RAUG!=NULL);
        g_assert_cmpfloat(*RAUG,==, 1.300);

        /*RDEP*/
        double* RDEP= POTCAR_Get(pot,"RDEP");
        g_assert(RDEP!=NULL);
        g_assert_cmpfloat(*RDEP,==, 1.501);

        /*RDEPT*/
        double* RDEPT= POTCAR_Get(pot,"RDEPT");
        g_assert(RDEPT!=NULL);
        g_assert_cmpfloat(*RDEPT,==, 1.300);

        /*QCUT*/
        double* QCUT= POTCAR_Get(pot,"QCUT");
        g_assert(QCUT!=NULL);
        g_assert_cmpfloat(*QCUT,==, -5.516);

        /*QGAM*/
        double* QGAM= POTCAR_Get(pot,"QGAM");
        g_assert(QGAM!=NULL);
        g_assert_cmpfloat(*QGAM,==, 11.032);
    } 

    /* POTCAR N */
    {
        POTCAR* pot= pot_array[2];

        /* VRHFIN */
        char** VRHFIN= POTCAR_Get(pot, "VRHFIN");
        g_assert(VRHFIN!=NULL);
        g_assert_cmpstr(VRHFIN[0],==,"N");
        g_assert_cmpstr(VRHFIN[1],==,"s2p3");
    
        /*LEXCH*/
        char* LEXCH= POTCAR_Get(pot, "LEXCH");
        g_assert(LEXCH!=NULL);
        g_assert_cmpstr(LEXCH,==,"PE");

        /*EATOM*/
        double* EATOM= POTCAR_Get(pot, "EATOM");
        g_assert(EATOM!=NULL);
        g_assert_cmpfloat(*EATOM,==, 264.5486);

        /*TITEL*/
        char** TITEL= POTCAR_Get(pot, "TITEL");
        g_assert(TITEL!=NULL);
        g_assert_cmpstr(TITEL[0],==,"PAW_PBE");
        g_assert_cmpstr(TITEL[1],==,"N");
        g_assert_cmpstr(TITEL[2],==,"08Apr2002");

        /*LULTRA*/
        bool* LULTRA= POTCAR_Get(pot,"LULTRA");
        g_assert(LULTRA!=NULL);
        g_assert(!(*LULTRA));

        /*IUNSCR*/
        int* IUNSCR= POTCAR_Get(pot,"IUNSCR");
        g_assert(IUNSCR!=NULL);
        g_assert_cmpint(*IUNSCR,==,0);

        /*RPACOR*/
        double* RPACOR= POTCAR_Get(pot,"RPACOR");
        g_assert(RPACOR!=NULL);
        g_assert_cmpfloat(*RPACOR,==,0);

        /*POMASS*/
        double* POMASS= POTCAR_Get(pot,"POMASS");
        g_assert(POMASS!=NULL);
        g_assert_cmpfloat(*POMASS,==,14.001);

        /*ZVAL*/
        double* ZVAL= POTCAR_Get(pot,"ZVAL");
        g_assert(ZVAL!=NULL);
        g_assert_cmpfloat(*ZVAL,==,5);

        /*RCORE*/
        double* RCORE= POTCAR_Get(pot,"RCORE");
        g_assert(RCORE!=NULL);
        g_assert_cmpfloat(*RCORE,==,1.500);

        /*RWIGS*/
        double* RWIGS= POTCAR_Get(pot,"RWIGS");
        g_assert(RWIGS!=NULL);
        g_assert_cmpfloat(*RWIGS,==, .741);

        /*ENMAX*/
        double* ENMAX= POTCAR_Get(pot,"ENMAX");
        g_assert(ENMAX!=NULL);
        g_assert_cmpfloat(*ENMAX,==, 400);

        /*ENMIN*/
        double* ENMIN= POTCAR_Get(pot,"ENMIN");
        g_assert(ENMIN!=NULL);
        g_assert_cmpfloat(*ENMIN,==, 300);

        /*ICORE*/
        int* ICORE= POTCAR_Get(pot, "ICORE");
        g_assert(ICORE!=NULL);
        g_assert_cmpint(*ICORE,==,2);

        /*LCOR*/
        bool* LCOR= POTCAR_Get(pot, "LCOR");
        g_assert(LCOR!=NULL);
        g_assert(*LCOR);

        /*LPAW*/
        bool* LPAW= POTCAR_Get(pot, "LPAW");
        g_assert(LPAW!=NULL);
        g_assert(*LPAW);

        /*EAUG*/
        double* EAUG= POTCAR_Get(pot,"EAUG");
        g_assert(EAUG!=NULL);
        g_assert_cmpfloat(*EAUG,==, 627.112);

        /*DEXC*/
        double* DEXC= POTCAR_Get(pot,"DEXC");
        g_assert(DEXC!=NULL);
        g_assert_cmpfloat(*DEXC,==, 0);

        /*RMAX*/
        double* RMAX= POTCAR_Get(pot,"RMAX");
        g_assert(RMAX!=NULL);
        g_assert_cmpfloat(*RMAX,==, 2.247);

        /*RAUG*/
        double* RAUG= POTCAR_Get(pot,"RAUG");
        g_assert(RAUG!=NULL);
        g_assert_cmpfloat(*RAUG,==, 1.300);

        /*RDEP*/
        double* RDEP= POTCAR_Get(pot,"RDEP");
        g_assert(RDEP!=NULL);
        g_assert_cmpfloat(*RDEP,==, 1.514);

        /*QCUT*/
        double* QCUT= POTCAR_Get(pot,"QCUT");
        g_assert(QCUT!=NULL);
        g_assert_cmpfloat(*QCUT,==, -5.562);

        /*QGAM*/
        double* QGAM= POTCAR_Get(pot,"QGAM");
        g_assert(QGAM!=NULL);
        g_assert_cmpfloat(*QGAM,==, 11.124);
    } 


    POTCAR_Free_Array( pot_array, pot_array_num);
}
