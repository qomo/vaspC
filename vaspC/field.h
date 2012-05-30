/**
 * Date: 2012-04-16
 * Author: Zhi-Quan Huang
 */
#ifndef _FIELD_H_
#define _FIELD_H_

#include "poscar.h"
#include <stdio.h>

enum{
    FIELD_NULL_SCA=-8, 
    FIELD_NULL_POS=-9, 
    FILED_NULL_PF=-10, 
    FIELD_MEM_VAL=-11
    };

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

void _SCALAR3D_Init(SCALAR3D** sca);
void _SCALAR3D_Free(SCALAR3D** sca);
#define SCALAR3D_Init(x) _SCALAR3D_Init(&x)
#define SCALAR3D_Free(x) _SCALAR3D_Free(&x)
int SCALAR3D_READ( SCALAR3D* sca, POSCAR* pos, FILE* pf);
void SCALAR3D_Write(SCALAR3D* sca, POSCAR* pos, FILE* pf);

void _SCALAR1D_Init(SCALAR1D** sca);
void _SCALAR1D_Free(SCALAR1D** sca);
#define SCALAR1D_Init(x) _SCALAR1D_Init(&x)
#define SCALAR1D_Free(x) _SCALAR1D_Free(&x)
void SCALAR3D_AVE(SCALAR3D* sca3d, SCALAR1D* sca1d, int direction);

#endif
