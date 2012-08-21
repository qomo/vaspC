#include "integral.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * @fn double Simpson_int(const double h, const double* const y, const int period, const int size)
 * @brief simpson 積分
 * @param h    格點間隔
 * @param y    格點上的函數值
 * @param period y的週期性(通常等於y_array的大小+1)
 * @param size 格點數
 * @warning 只適用於偶數格點
 */
double Simpson_int( const double h, const double* const y, const int period, const int size)
{
    double ret= 0;
    int i;
    if (size%2!=0)
    {
        fprintf(stderr, "simpson: Number of intervals must be even.\n");
        exit(1);
    } 

    for (i=0; i+2<=size; i+=2)
    {
        int a=i;
        int m=i+1;
        int b=i+2;
        while (a>=period) a -= period;
        while (m>=period) m -= period;
        while (b>=period) b -= period;
        const double y_a= y[a];
        const double y_m= y[m];
        const double y_b= y[b];
        ret+= (2*h/6.0)*(y_a+4.0*y_m+y_b);
    }
    return ret;
}

/**
 * @fn double Simpson38_int(double h, double* y, int size)
 * @brief simpson 3/8 積分
 * @param h    格點間隔
 * @param y    格點上的函數值
 * @param period y的週期性(通常等於y array的大小)
 * @param size 格點數
 * @warning 只適用於3倍數格點
 */
double Simpson38_int(const double h, const double* const y, const int period, const int size)
{
    double ret= 0;
    int i;
    if (size%3!=0)
    {
        fprintf(stderr, "simpson: Number of intervals must be multiply of three.\n");
        exit(1);
    } 

    for (i=0; i+3<=size; i+=3)
    {
        int a =i;
        int m1=i+1;
        int m2=i+2;
        int b =i+3;
        while (a >=period) a-= period;
        while (m1>=period) m1-= period;
        while (m2>=period) m2-= period;
        while (b >=period) b-= period;

        const double y_a = y[a];
        const double y_m1= y[m1];
        const double y_m2= y[m2];
        const double y_b = y[b];
        ret+= (3*h/8.0)*(y_a+3.0*y_m1+3.0*y_m2+y_b);
    }

    return ret;
}

/**
 * @fn double Simpson_frac(const double h, const double y0, const double y1, const double y2, const double size)
 * @brief simpson 積分處理積分上限非整數格點
 * @param h    格點間隔
 * @param y0   第 0 格點函數值
 * @param y1   第 1 格點函數值
 * @param y2   第 2 格點函數值
 * @param size 積分範圍上限
 * @warning 積分範圍 0~size
 */
double Simpson_float(const double h, const double y0, const double y1, const double y2, const double size)
{
    double ret= 0;
    const double A= 2.0;

    const double x0_term= 6.0*A*A*y0;
    const double x1_term= -9.0*A*y0+12.0*A*y1-3.0*A*y2;
    const double x2_term= 4.0*y0-8.0*y1+4.0*y2;

    ret= (x2_term*size+x1_term)*size+x0_term;
    ret= (size/(6.0*A*A))*ret;

    return h*ret;
}

/**
 * @fn double Simpson38_float(const double h, const double y0, const double y1, const double y2, const double y3, const double size)
 * @brief simpson 3/8's rule 處理積分上限非整數格點
 * @param h    格點間隔
 * @param y0   第 0 格點函數值
 * @param y1   第 1 格點函數值
 * @param y2   第 2 格點函數值
 * @param y3   第 3 格點函數值
 * @param size 積分範圍上限
 * @warning 積分範圍 0~size
 */
double Simpson38_float(const double h, const double y0, const double y1, const double y2, const double y3, const double size)
{
    double ret=0 ;

    const double A= 3.0;
    const double AA= A*A;
    const double AAA= A*A*A;

    double x0_term= 8.0*AAA*y0;
    double x1_term= -22.0*AA*y0+36.0*AA*y1-18.0*AA*y2+4.0*AA*y3;
    double x2_term= 24.0*A*y0-60.0*A*y1+48.0*A*y2-12.0*A*y3;
    double x3_term= -9.0*y0+27.0*y1-27.0*y2+9.0*y3;

    ret= ((x3_term*size+x2_term)*size+x1_term)*size+x0_term;
    ret=((size)/(8.0*AAA))*ret;
    
    return h*ret;
}
