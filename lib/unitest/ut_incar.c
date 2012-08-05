#include "glib.h"
#include "vaspC.h"
#include <stdlib.h>

void check_INCAR_New_Free()
{
    INCAR* incar= INCAR_New();
    INCAR_Free(incar);
}

void check_INCAR_Set_Get()
{
    INCAR* incar= INCAR_New();

    int i=10; 
    int *pi= POINTER_MALLOC(&i, int, 1); 
    int *ret= INCAR_Set(incar,"ten", pi);
    g_assert_cmpint(*ret,==,10);

    double j=10;
    double *pj= POINTER_MALLOC(&j, double, 1);
    double *ret2= INCAR_Set(incar,"ten", pj);
    g_assert_cmpfloat(*ret2,==,10);

    double* ret3= INCAR_Get(incar, "ten");

    g_assert_cmpfloat(*ret2,==,*ret3);
    
    INCAR_Free(incar);
}

void check_INCAR_Read()
{
    FILE* pf= NULL;
    KEYWORD* keyword;
    
    if ((pf=fopen("data/keyword/KEYWORD","r"))==NULL)
        g_assert(false);

    keyword= KEYWORD_New();
    KEYWORD_Read(keyword, pf);
    fclose(pf);

    if ((pf=fopen("data/incar/INCAR","r"))==NULL)
        g_assert(false);

    INCAR* incar= INCAR_New();
    INCAR_Read(incar, keyword, pf);
    fclose(pf);
    
    char* s= INCAR_Get(incar, "SYSTEM");
    g_assert_cmpstr(s,==,"TEST");

    bool* b= INCAR_Get(incar, "LVTOT");
    g_assert((*b)==false);

    int* i= INCAR_Get(incar, "ISTART");
    g_assert_cmpint(*i,==, 0);

    double* d= INCAR_Get(incar, "EDIFF");
    g_assert_cmpfloat(*d ,==, 1E-4);

    LIST* list_b= INCAR_Get(incar, "LRCTYPE");
    b= LIST_Get(list_b, 0);
    g_assert((*b)==true);
    b= LIST_Get(list_b, 1);
    g_assert((*b)==false);
    b= LIST_Get(list_b, 2);
    g_assert((*b)==false);
    b= LIST_Get(list_b, 3);
    g_assert((*b)==false);
    b= LIST_Get(list_b, 4);
    g_assert((*b)==true);

    LIST* list_i= INCAR_Get(incar, "NSUBSYS");
    i= LIST_Get(list_i, 0);
    g_assert_cmpint(*i, ==, 1);
    i= LIST_Get(list_i, 1);
    g_assert_cmpint(*i, ==, 2);
    i= LIST_Get(list_i, 2);
    g_assert_cmpint(*i, ==, 3);
    i= LIST_Get(list_i, 3);
    g_assert_cmpint(*i, ==, 4);
    i= LIST_Get(list_i, 4);
    g_assert_cmpint(*i, ==, 5);

    LIST* list_d= INCAR_Get(incar, "RWIGS");
    d= LIST_Get(list_d, 0);
    g_assert_cmpfloat(*d, ==, .01);
    d= LIST_Get(list_d, 1);
    g_assert_cmpfloat(*d, ==, 2E-1);
    d= LIST_Get(list_d, 2);
    g_assert_cmpfloat(*d, ==, 3);
    d= LIST_Get(list_d, 3);
    g_assert_cmpfloat(*d, ==, -40.);
    d= LIST_Get(list_d, 4);
    g_assert_cmpfloat(*d, ==, -5E3);
    d= LIST_Get(list_d, 5);
    g_assert_cmpfloat(*d, ==, -60000.00);

    KEYWORD_Free(keyword);
    INCAR_Free(incar);
}
