/**
 * @brief Handle POTCAR file
 * @author Zhi-Quan Huang
 * @date 2012-05-01
 */
#ifndef _POTCAR_H_
#define _POTCAR_H_

#include <stdio.h>

typedef struct
{
    double zval;  /*Numbers of valence electron*/
    double rwigs; /*Wigner-Sieitz radius (A)*/ 
    double enmax; /*Max of energy*/
    double enmin; /*Min of energy*/
} POTCAR;

void _POTCAR_Init(POTCAR** ppot);
void _POTCAR_Free(POTCAR** ppot);
int _POTCAR_Read(POTCAR** ppot, FILE* pf);
#define POTCAR_Init(x) _POTCAR_Init(&x)
#define POTCAR_Free(x) _POTCAR_Free(&x)
#define POTCAR_Read(x,y) _POTCAR_Read(&x,y)
#endif
