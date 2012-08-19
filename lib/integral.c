#include "integral.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @fn double Simpson(double h, double* y, int size)
 * @brief simpson 積分
 * @param h    格點間隔
 * @param y    格點上的函數值
 * @param size 格點數
 * @warning 只適用於偶數格點
 */
double Simpson(double h, double* y, int size)
{
    double ret= 0;
    int i;
    int      a,   m,   b;
    double y_a, y_m, y_b;
    if ((size-1)%2!=0)
    {
        fprintf(stderr, "simpson: Number of intervals must be even.\n");
        exit(1);
    } 

    for (i=0; i+2<=size-1; i+=2)
    {
        a=i;
        m=i+1;
        b=i+2;
        y_a= y[a];
        y_m= y[m];
        y_b= y[b];
        ret+= (2*h/6.0)*(y_a+4.0*y_m+y_b);
    }
    return ret;
}

/**
 * @fn double Simpson38(double h, double* y, int size)
 * @brief simpson 3/8 積分
 * @param h    格點間隔
 * @param y    格點上的函數值
 * @param size 格點數
 * @warning 只適用於3倍數格點
 */
double Simpson38(double h, double* y, int size)
{
    double ret= 0;
    int i;
    int      a,   m1,   m2,   b;
    double y_a, y_m1, y_m2, y_b;
    if ((size-1)%3!=0)
    {
        fprintf(stderr, "simpson: Number of intervals must be multiply of three.\n");
        exit(1);
    } 

    for (i=0; i+3<=size-1; i+=3)
    {
        a =i;
        m1=i+1;
        m2=i+2;
        b =i+3;
        y_a = y[a];
        y_m1= y[m1];
        y_m2= y[m2];
        y_b = y[b];
        ret+= (3*h/8.0)*(y_a+3.0*y_m1+3.0*y_m2+y_b);
    }

    return ret;
}
