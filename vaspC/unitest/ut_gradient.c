#include "glib.h"
#include "vaspC.h"

void check_Threept3dX()
{
    int i;
    double val[10]={ 59, 62, 47, 94, 22, 74, 54, 87, 44, 80};
    double ans[10]={-9,-6, 16,-12.5,-10, 16, 6.5,-5, -3.5, 7.5};
    double vector[10][3];

    Threept3d(val, 10, 1, 1, 1.0, 1.0, 1.0, vector);

    for (i=0; i<10; i++)
    {
        g_assert_cmpfloat(vector[i][0],==,ans[i]);
        g_assert_cmpfloat(vector[i][1],==,0);
        g_assert_cmpfloat(vector[i][2],==,0);
    }
}

void check_Threept3dY()
{

    int i;
    double val[10]={ 59, 62, 47, 94, 22, 74, 54, 87, 44, 80};
    double ans[10]={-9,-6, 16,-12.5,-10, 16, 6.5,-5, -3.5, 7.5};
    double vector[10][3];

    Threept3d(val, 1, 10, 1, 1.0, 1.0, 1.0, vector);

    for (i=0; i<10; i++)
    {
        g_assert_cmpfloat(vector[i][0],==,0);
        g_assert_cmpfloat(vector[i][1],==,ans[i]);
        g_assert_cmpfloat(vector[i][2],==,0);
    }

}

void check_Threept3dZ()
{

    int i;
    double val[10]={ 59, 62, 47, 94, 22, 74, 54, 87, 44, 80};
    double ans[10]={-9,-6, 16,-12.5,-10, 16, 6.5,-5, -3.5, 7.5};
    double vector[10][3];

    Threept3d(val, 1, 1, 10, 1.0, 1.0, 1.0, vector);

    for (i=0; i<10; i++)
    {
        g_assert_cmpfloat(vector[i][0],==,0);
        g_assert_cmpfloat(vector[i][1],==,0);
        g_assert_cmpfloat(vector[i][2],==,ans[i]);
    }
}
