/**
 * @brief Handle POSCAR file
 * @details This file contains POSCAR struct and relative functions.
 * @author Zhi-Quan Huang
 * @date 2012-04-01
 */
#ifndef _POSCAR_H_
#define _POSCAR_H_

#include "lattice.h"
#include <stdio.h>
#include <stdbool.h>

#define POSCAR_COMMENT_LEN 512


enum{
    POSCAR_NULL_POS=-1, 
    POSCAR_NULL_PF=-2, 
    POSCAR_MEM_ELEM_NUM=-3, 
    POSCAR_NUM_COUNT_DISMATCH=-4, 
    POSCAR_MEM_ELEM_COUNT=-5,
    POSCAR_MEM_ATOM_DYN=-6,
    POSCAR_MEM_ATOM_POS=-7
    };

typedef struct
{
    char  comment[POSCAR_COMMENT_LEN]; /* comment*/
    double scale;       /* scale constant*/
    LATTICE* lat;       /*lattice and reciprocal vector*/
    int   nelem, natom; 
    int   *elem_num;    /* atomic number*/
    int   *elem_count;  /* numbers of atoms*/
    bool  isD;          /* bool with direct coordinates*/
    double (*atom_pos)[3];  /*  position of atoms */
    bool   (*atom_dyn)[3];  /* selective dynamics of atoms */
} POSCAR;

void _POSCAR_Init(POSCAR** ppos);
int _POSCAR_Copy(POSCAR* pos, POSCAR** pcp);
void _POSCAR_Free(POSCAR** ppos);
#define POSCAR_Init(x)   _POSCAR_Init(&(x))
#define POSCAR_Copy(x,y) _POSCAR_Copy((x),&(y))
#define POSCAR_Free(x)   _POSCAR_Free(&(x))
void POSCAR_D2C(POSCAR* pos);
void POSCAR_C2D(POSCAR* pos);
int  POSCAR_Read(POSCAR* pos, FILE* pf);
void POSCAR_A2B(POSCAR* pos);
void POSCAR_Confined(POSCAR* pos);
void POSCAR_Write(POSCAR* pos, FILE* pf, bool isLong, bool isElem, bool isDyn);
#endif
