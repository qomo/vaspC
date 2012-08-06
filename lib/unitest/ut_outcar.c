#include "glib.h"
#include "vaspC.h"

void check_OUTCAR_New_Free()
{
    OUTCAR* out= OUTCAR_New();
    OUTCAR_Free(out);
}

void check_OUTCAR_Set_Get()
{
    OUTCAR* out= OUTCAR_New();

    int i=10; 
    int *pi= POINTER_MALLOC(&i, int, 1); 
    int *ret= OUTCAR_Set(out,"ten", pi);
    g_assert_cmpint(*ret,==,10);

    double j=10;
    double *pj= POINTER_MALLOC(&j, double, 1);
    double *ret2= OUTCAR_Set(out,"ten", pj);
    g_assert_cmpfloat(*ret2,==,10);

    double* ret3= OUTCAR_Get(out, "ten");

    g_assert_cmpfloat(*ret2,==,*ret3);

    OUTCAR_Free(out);
}

void check_OUTCAR_Read()
{
    int i;
    FILE *pf= NULL;

    if ((pf=fopen("data/outcar/OUTCAR","r"))==NULL)
        g_assert(false);

    OUTCAR* out= OUTCAR_New();
    OUTCAR_Read(out, pf);
    LIST* list_e_fermi= OUTCAR_Get(out, "E-fermi");
    double *d= LIST_Get(list_e_fermi, 0);
    g_assert_cmpfloat(*d, ==, 1.5917 );

    LIST* list_str_list= OUTCAR_Get(out, "TITEL");

    for (i=0; i<2; i++)
    {
        LIST* str_list= LIST_Get(list_str_list, i);
        char* ex= LIST_Get(str_list, 0);
        char* elem= LIST_Get(str_list, 1);
        char* date= LIST_Get(str_list, 2);
        if (i==0)
        {
            g_assert_cmpstr(ex, ==, "PAW_PBE");
            g_assert_cmpstr(elem, ==, "Pb");
            g_assert_cmpstr(date, ==, "08Apr2002");
        }
        else if (i==1)
        {
            g_assert_cmpstr(ex, ==, "PAW_PBE");
            g_assert_cmpstr(elem, ==, "Si");
            g_assert_cmpstr(date, ==, "05Jan2001");
        }
    }

    OUTCAR_Free(out);
}
