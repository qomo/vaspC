#include "glib.h"
#include "vaspC.h"

void check_insort()
{
    double num[4][3]={
        {42, 34, 47},
        {10, 24,  5},
        {34,  5, 49},
        {43,  1, 50},
    };

    insort(&(num[0][0]),4,3,1,false);

    g_assert_cmpfloat(num[0][0],==,43);
    g_assert_cmpfloat(num[0][1],==,1);
    g_assert_cmpfloat(num[0][2],==,50);
    g_assert_cmpfloat(num[1][0],==,34);
    g_assert_cmpfloat(num[1][1],==,5);
    g_assert_cmpfloat(num[1][2],==,49);
    g_assert_cmpfloat(num[2][0],==,10);
    g_assert_cmpfloat(num[2][1],==,24);
    g_assert_cmpfloat(num[2][2],==,5);
    g_assert_cmpfloat(num[3][0],==,42);
    g_assert_cmpfloat(num[3][1],==,34);
    g_assert_cmpfloat(num[3][2],==,47);


    insort(&(num[0][0]),4,3,1,true);

    g_assert_cmpfloat(num[0][0],==,42);
    g_assert_cmpfloat(num[0][1],==,34);
    g_assert_cmpfloat(num[0][2],==,47);
    g_assert_cmpfloat(num[1][0],==,10);
    g_assert_cmpfloat(num[1][1],==,24);
    g_assert_cmpfloat(num[1][2],==,5);
    g_assert_cmpfloat(num[2][0],==,34);
    g_assert_cmpfloat(num[2][1],==,5);
    g_assert_cmpfloat(num[2][2],==,49);
    g_assert_cmpfloat(num[3][0],==,43);
    g_assert_cmpfloat(num[3][1],==,1);
    g_assert_cmpfloat(num[3][2],==,50);


}
