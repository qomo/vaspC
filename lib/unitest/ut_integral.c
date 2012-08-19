#include "glib.h"
#include "vaspC.h"

void check_Simpson()
{
    double h  = 2.0;
    double y[]= { 0, 1, 2, 3, 4, 5, 6};
    double d;

    d= Simpson(h,y,3);
    g_assert_cmpfloat(d,==,4);

    d= Simpson(h,y,5);
    g_assert_cmpfloat(d,==,16);

    d= Simpson(h,y,7);
    g_assert_cmpfloat(d,==,36);
}

void check_Simpson38()
{
    double h  = 2.0;
    double y[]= { 0, 1, 2, 3, 4, 5, 6};
    double d;

    d= Simpson38(h,y,4);
    g_assert_cmpfloat(d,==,9);

    d= Simpson38(h,y,7);
    g_assert_cmpfloat(d,==,36);
}

