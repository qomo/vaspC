/**
 * Date: 2012-05-08
 * Author: Zhi-Quan Huang
 */
#ifndef _OUTCAR_H_
#define _OUTCAR_H_

#include <stdio.h>

typedef struct
{
    int nfermi;
    double *fermi;
} OUTCAR;

void _OUTCAR_Init(OUTCAR** pout);
void _OUTCAR_Free(OUTCAR** pout);
#define OUTCAR_Init(x) _OUTCAR_Init(&(x))
#define OUTCAR_Free(x) _OUTCAR_Free(&(x))
void OUTCAR_Read(OUTCAR* out, FILE* pf);
#endif 
