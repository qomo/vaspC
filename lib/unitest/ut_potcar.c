/**
 * @breif unittest for potcar.c
 * @author Zhi-Quan Huang
 * @date 2012-05-08
 */
#include "glib.h"
#include "vaspC.h"

#include <stdio.h>
#include <math.h>
#define HIGH_PREC 1e-14

void check_POTCAR_Read()
{
    FILE* pf=NULL;
    POTCAR* pot=NULL;
    int npot=0;

    g_assert((pf=fopen("data/potcar/POTCAR_BCN_PAW_PBE","r"))!=NULL);
    POTCAR_Init(pot);

    npot=POTCAR_Read(pot, pf);
    g_assert_cmpint(npot,==,3);

    g_assert(fabs(pot[0].zval-3)<HIGH_PREC);
    g_assert(fabs(pot[1].zval-4)<HIGH_PREC);
    g_assert(fabs(pot[2].zval-5)<HIGH_PREC);

    g_assert(fabs(pot[0].rwigs-.905)<HIGH_PREC);
    g_assert(fabs(pot[1].rwigs-.863)<HIGH_PREC);
    g_assert(fabs(pot[2].rwigs-.741)<HIGH_PREC);

    g_assert(fabs(pot[0].rwigs-.905)<HIGH_PREC);
    g_assert(fabs(pot[1].rwigs-.863)<HIGH_PREC);
    g_assert(fabs(pot[2].rwigs-.741)<HIGH_PREC);


    POTCAR_Free(pot);
    fclose(pf);
}
