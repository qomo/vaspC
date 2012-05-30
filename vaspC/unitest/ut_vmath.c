#include "glib.h"
#include "vaspC.h"

void check_vmath_dot3D()
{
    double lvec[3]={1,2,3};
    double rvec[3]={3,4,5};
    double ans= dot3D(lvec,rvec);
    g_assert_cmpfloat(ans,==,26);
}

void check_vmath_cross3D()
{
    double lvec[3]={1,2,3};
    double rvec[3]={3,4,5};
    double vec[3];
    
    cross3D(lvec, rvec, vec); 

    g_assert_cmpfloat(vec[0],==,-2);
    g_assert_cmpfloat(vec[1],==,4);
    g_assert_cmpfloat(vec[2],==,-2);
}
