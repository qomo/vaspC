/**
 * Date: 2012-04-16
 * Author: Zhi-Quan Huang
 */
#ifndef _FIELD_H_
#define _FIELD_H_

#include "poscar.h"
#include <stdio.h>

typedef struct
{
    double axis[3][3];
    int    ngrid[3];
    double* val;
} SCALAR3D;

typedef struct
{
    double axis[3];
    int    ngrid;
    double* val;
} SCALAR1D;

SCALAR3D* SCALAR3D_New();
void SCALAR3D_Free(SCALAR3D* sca);
int SCALAR3D_READ( SCALAR3D* sca, POSCAR* pos, FILE* pf);
void SCALAR3D_Write(SCALAR3D* sca, POSCAR* pos, FILE* pf);

SCALAR1D* SCALAR1D_New();
void SCALAR1D_Free(SCALAR1D* sca);
void SCALAR3D_AVE(SCALAR3D* sca3d, SCALAR1D* sca1d, int direction);

#endif
