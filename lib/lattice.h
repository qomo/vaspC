/**
 * @Date 2012-04-18
 * @Author Zhi-Quan Huang
 */
#ifndef _LATTICE_H_
#define _LATTICE_H_

typedef struct
{
    double a[3][3];
    double b[3][3];
} LATTICE;

void _LATTICE_Init(LATTICE** lat);
void _LATTICE_Free(LATTICE** lat);
#define LATTICE_Init(x) _LATTICE_Init(&x)
#define LATTICE_Free(x) _LATTICE_Free(&x)
void LATTICE_Copy(LATTICE* lat, LATTICE** cplat);
void LATTICE_C2D(LATTICE* lat, double pos[3]);
void LATTICE_D2C(LATTICE* lat, double pos[3]);
void LATTICE_A2B(LATTICE* lat);
#endif
