#include "glib.h"
#include "vaspC.h"
#include <math.h>

#define PREC 1e-7

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

void check_Fivept3dX()
{

    int i;
    double val[10]={ 59, 62, 47, 94, 22, 74, 54, 87, 44, 80};
    double ans[10]={-12.25,
                    -9.166666666667,
                    24.416666666667,
                   -17.666666666667,
                   -13.916666666667,
                    21.916666666667,
                     6.833333333333,  
                    -7.166666666667,
                    -5.083333333333,
                     12.08333333333};
    double vector[10][3];

    Fivept3d(val, 10, 1, 1, 1.0, 1.0, 1.0, vector);

    for (i=0; i<10; i++)
    {
        g_assert_cmpfloat(fabs(vector[i][0]-ans[i]),<,PREC);
        g_assert_cmpfloat(vector[i][1],==,0);
        g_assert_cmpfloat(vector[i][2],==,0);
    }
}

void check_Fivept3dY()
{

    int i;
    double val[10]={ 59, 62, 47, 94, 22, 74, 54, 87, 44, 80};
    double ans[10]={-12.25,
                    -9.166666666667,
                    24.416666666667,
                   -17.666666666667,
                   -13.916666666667,
                    21.916666666667,
                     6.833333333333,  
                    -7.166666666667,
                    -5.083333333333,
                     12.08333333333};
    double vector[10][3];

    Fivept3d(val, 1, 10, 1, 1.0, 1.0, 1.0, vector);

    for (i=0; i<10; i++)
    {
        g_assert_cmpfloat(vector[i][0],==,0);
        g_assert_cmpfloat(fabs(vector[i][1]-ans[i]),<,PREC);
        g_assert_cmpfloat(vector[i][2],==,0);
    }
}

void check_Fivept3dZ()
{

    int i;
    double val[10]={ 59, 62, 47, 94, 22, 74, 54, 87, 44, 80};
    double ans[10]={-12.25,
                    -9.166666666667,
                    24.416666666667,
                   -17.666666666667,
                   -13.916666666667,
                    21.916666666667,
                     6.833333333333,  
                    -7.166666666667,
                    -5.083333333333,
                     12.08333333333};
    double vector[10][3];

    Fivept3d(val, 1, 1, 10, 1.0, 1.0, 1.0, vector);

    for (i=0; i<10; i++)
    {
        g_assert_cmpfloat(vector[i][0],==,0);
        g_assert_cmpfloat(vector[i][1],==,0);
        g_assert_cmpfloat(fabs(vector[i][2]-ans[i]),<,PREC);
    }
}

