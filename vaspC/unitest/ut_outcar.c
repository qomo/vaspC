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

void check_OUTCAR_Read()
{

    FILE *pf= NULL;
    OUTCAR* out=NULL;
    OUTCAR_Init(out);
    
    g_assert((pf=fopen("data/outcar/OUTCAR","r"))!=NULL);

    OUTCAR_Read(out, pf);
    
    g_assert_cmpint(out->nfermi,==,1);
    g_assert(fabs(out->fermi[0]-1.5917)<HIGH_PREC);
    fclose(pf);

    OUTCAR_Free(out);
}
