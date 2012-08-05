#include "glib.h"
#include "vaspC.h"
#include <stdlib.h>

void check_KEYWORD_New_Free()
{
    KEYWORD* keyword= KEYWORD_New();
    KEYWORD_Free(keyword);
}

void check_KEYWORD_Set_Get()
{
    KEYWORD* keyword= KEYWORD_New();

    int i=10; 
    int *pi= POINTER_MALLOC(&i, int, 1); 
    int *ret= KEYWORD_Set(keyword,"ten", pi);
    g_assert_cmpint(*ret,==,10);

    double j=10;
    double *pj= POINTER_MALLOC(&j, double, 1);
    double *ret2= KEYWORD_Set(keyword,"ten", pj);
    g_assert_cmpfloat(*ret2,==,10);

    double* ret3= KEYWORD_Get(keyword, "ten");

    g_assert_cmpfloat(*ret2,==,*ret3);
    
    KEYWORD_Free(keyword);
}

void check_KEYWORD_Read()
{
    FILE* pf= NULL;
    if ((pf=fopen("data/keyword/KEYWORD","r"))==NULL)
        g_assert(false);
    KEYWORD* keyword= KEYWORD_New();
    KEYWORD_Read(keyword, pf);

    enum KEYWORD_TYPE* type;

    type= KEYWORD_Get(keyword, "LAECHG");
    g_assert_cmpint(*type,==,TYPE_BOOL); 

    type= KEYWORD_Get(keyword, "LRCTYPE");
    g_assert_cmpint(*type,==,TYPE_BOOL_LIST); 

    type= KEYWORD_Get(keyword, "ENCUTAE");
    g_assert_cmpint(*type,==,TYPE_FLOAT); 

    type= KEYWORD_Get(keyword, "M_CONSTR");
    g_assert_cmpint(*type,==,TYPE_FLOAT_LIST); 

    type= KEYWORD_Get(keyword, "NOMEGA");
    g_assert_cmpint(*type,==,TYPE_INT); 

    type= KEYWORD_Get(keyword, "NSUBSYS");
    g_assert_cmpint(*type,==,TYPE_INT_LIST); 

    type= KEYWORD_Get(keyword, "GGA");
    g_assert_cmpint(*type,==,TYPE_STR); 

    KEYWORD_Free(keyword);
    fclose(pf);
}
