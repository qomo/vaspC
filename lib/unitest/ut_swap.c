#include "vaspC.h"
#include "glib.h"

void check_swap()
{
    int ia=1, ib=2;
    double da=1, db=2;
    char ca='1', cb='2';
    double m[3]={0,1,2};
    double n[3]={10,20,30};

    swap(&ia,&ib,sizeof(int));
    g_assert_cmpint(ia,==,2);
    g_assert_cmpint(ib,==,1);

    swap(&da,&db,sizeof(double));
    g_assert_cmpfloat(da,==,2);
    g_assert_cmpfloat(db,==,1);

    swap(&ca,&cb,sizeof(char));
    g_assert(ca=='2');
    g_assert(cb=='1');

    swap(m,n,sizeof(double)*3);
    
    g_assert_cmpfloat(m[0],==,10);
    g_assert_cmpfloat(m[1],==,20);
    g_assert_cmpfloat(m[2],==,30);

    g_assert_cmpfloat(n[0],==,0);
    g_assert_cmpfloat(n[1],==,1);
    g_assert_cmpfloat(n[2],==,2);

}
