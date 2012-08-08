#ifndef _KPOINTS_H_
#define _KPOINTS_H_

#include "list.h"
#include "line.h"
#include <stdbool.h>
#include <stdio.h>

enum KP_TYPE
{
    TYPE_UNKOWN,
    TYPE_GRID,
    TYPE_MESH,
    TYPE_LINE
};

typedef struct
{
    enum KP_TYPE type;
} KPOINTS;

typedef struct
{
    enum KP_TYPE type;
    char* comment;
    int ngrid; 
    bool isRec;
    double(*pt)[3];
    double(*wt)[3];
} KPOINTS_GRID;

typedef struct
{
    double start[3];  
    double end[3];  
    char start_tag[20];
    char end_tag[20];
} KP_SEG;

typedef struct
{
    enum KP_TYPE type;
    char* comment;
    int ngrid;
    bool isRec;
    LIST* seg;
} KPOINTS_LINE;

typedef struct
{
    enum KP_TYPE type;
    char* comment; /*1st Line*/
    bool isGamma;        /* 3rd Line */
    int nmesh[3];        /* 4rd Line */
    double shift[3];     /* 5rd Line */ 
} KPOINTS_MESH;

KPOINTS* KPOINTS_New();
KPOINTS_GRID* KPOINTS_GRID_New();
KPOINTS_MESH* KPOINTS_MESH_New();
KPOINTS_LINE* KPOINTS_LINE_New();

void KPOINTS_GRID_Free(KPOINTS_GRID* kp);
void KPOINTS_MESH_Free(KPOINTS_MESH* kp);
void KPOINTS_LINE_Free(KPOINTS_LINE* kp);
void KPOINTS_Free(KPOINTS* kp);

enum KP_TYPE KPOINTS_File_Type(FILE* pf);
void KPOINTS_MESH_Read(KPOINTS_MESH* mesh, FILE* pf);
void KPOINTS_LINE_Read(KPOINTS_LINE* line, FILE* pf);
KP_SEG* KPOINTS_LINE_Get_Seg(KPOINTS_LINE* line, int i);

#endif
