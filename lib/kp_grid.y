%{
#include "kpoints.h"
#include "kp_grid.h"
#include "list.h"
#include <string.h>
#include <stdlib.h>
%}

%name-prefix "kp_grid_"
%parse-param {KPOINTS_GRID* grid}

%union{
    bool b;
    int i;
    char* s;
    double d;
}

%token<i> INT
%token<s> STR
%token<d> FLOAT
%token<b> BOOL
%token EOL_COMMENT EOL_NGRID EOL_LINE
%token EOL_GRID

%start stmt

%%
stmt:
    | stmt STR EOL_COMMENT {
        grid->comment= $2;
    }
    | stmt INT EOL_NGRID {
        grid->ngrid = $2;
    }
    | stmt BOOL EOL_LINE {
        grid->isRec= $2;
    }
    | stmt EOL_GRID {
        /*skip*/
    }
    | stmt FLOAT FLOAT FLOAT INT EOL_GRID {
        KP_GRID* kp_grid= malloc(sizeof(KP_GRID));     
        if (kp_grid==NULL)
        {
            fprintf(stderr, "Memory Allocate Error!");
            exit(1);
        }
        kp_grid->pt[0]= $2; 
        kp_grid->pt[1]= $3; 
        kp_grid->pt[2]= $4; 
        kp_grid->wt   = $5; 
        LIST_Append(grid->grid,kp_grid);
    }
;
%%
