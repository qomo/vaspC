#ifndef _KPOINTS_H_
#define _KPOINTS_H_

#include <stdbool.h>
#include <stdio.h>

enum
{
    KP_UNKNOWN,
    KP_GRID,
    KP_MESH,
    KP_LINE
};

typedef struct 
{
    int type;
    /*GRID*/  
    char* comment; /*1st Line*/         
    int ngrid;     /*2nd Line*/
    bool isRev;    /*3rd Line*/
    double (*pt)[3]; /* 4th~ Line (0-2 token)*/
    double (*wt)[3];    /* 4th~ Line (  3 token)*/
    /*MESH*/  
    /*char* comment;*/   /* 1st Line */
    /*int ngrid;*/       /* 2nd Line==0*/
    bool isGamma;        /* 3rd Line */
    int nmesh[3];        /* 4rd Line */
    double shift[3];     /* 5rd Line */ 
    /*LINE*/
    /*char* comment;*//* 1st Line   */
    /*int ngrid;*/    /* 2nd Line!=0*/
                      /* 3rd Line[0]=='L'*/
    /*bool isRev;*/   /* 4nd Line   */
    /*double (*pt)[3];*//* 5th~ Line*/
    char** mark;
}KPOINTS;

void _KPOINTS_Init(KPOINTS** pkp);
#define KPOINTS_Init(x) _KPOINTS_Init(&(x))
void _KPOINTS_Free(KPOINTS** pkp);
#define KPOINTS_Free(x) _KPOINTS_Free(&(x))
void KPOINTS_Read(KPOINTS* kp, FILE* pf);

#endif
