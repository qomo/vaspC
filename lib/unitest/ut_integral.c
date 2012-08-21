#include "glib.h"
#include "vaspC.h"

void check_Simpson_int()
{
    const double h  = 2.0;
    const double y[]= { 0, 1, 2, 3, 4, 5, 6};
    double d;

    d= Simpson_int(h,y,7,2);
    g_assert_cmpfloat(d,==,4);

    d= Simpson_int(h,y,7,4);
    g_assert_cmpfloat(d,==,16);

    d= Simpson_int(h,y,7,6);
    g_assert_cmpfloat(d,==,36);

    d= Simpson_int(h,y,7,8);
    g_assert_cmpfloat(d,==,36+28./6.);

}

void check_Simpson38_int()
{
    double h  = 2.0;
    double y[]= { 0, 1, 2, 3, 4, 5, 6};
    double d;

    d= Simpson38_int(h,y,7,3);
    g_assert_cmpfloat(d,==,9);

    d= Simpson38_int(h,y,7,6);
    g_assert_cmpfloat(d,==,36);

    d= Simpson38_int(h,y,7,9);
    g_assert_cmpfloat(d,==,36+66./8.);

}

void check_Simpson_float()
{
    double h= 2.0;
    double y[]= { 0, 1, 2};    

    double d;
    
    d= Simpson_float(h,y[0],y[1],y[2],2.0);
    g_assert_cmpfloat(d,==,4);

    d= Simpson_float(h,y[0],y[1],y[2], 0.);
    g_assert_cmpfloat(d,==,0);
}

void check_Simpson38_float()
{
    
    double h= 2.0;
    double y[]= { 0, 1, 2, 3};    

    double d;
    
    d= Simpson38_float(h,y[0],y[1],y[2],y[3],3.0);
    g_assert_cmpfloat(d,==,9);

    d= Simpson38_float(h,y[0],y[1],y[2],y[3],0.);
    g_assert_cmpfloat(d,==,0);
}
