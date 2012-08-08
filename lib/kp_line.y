%{
#include "kpoints.h"
#include "kp_line.h"
#include "list.h"
#include <string.h>
#include <stdlib.h>
%}

%name-prefix "kp_line_"
%parse-param {KPOINTS_LINE* line}

%union{
    bool b;
    int i;
    char* s;
    double d;
}

%token<i> INT
%token<s> STR TAG
%token<d> FLOAT
%token<b> BOOL
%token EOL_COMMENT EOL_NGRID EOL_LINE EOL_REC
%token EOL_POINTS_START EOL_POINTS_END

%start stmt

%%

stmt:
    | stmt STR EOL_COMMENT {
        line->comment= $2;        
    }
    | stmt INT EOL_NGRID {
        line->ngrid= $2;
    }
    | stmt STR EOL_LINE {
        /*skip*/ 
    }
    | stmt BOOL EOL_REC {
        line->isRec= $2;
    }
    | stmt FLOAT FLOAT FLOAT TAG EOL_POINTS_START {
        int i;
        KP_SEG* seg= malloc(sizeof(KP_SEG)); 
        if (seg==NULL) 
        {
            fprintf(stderr, "Memory Allocate Error!");
            exit(1);
        }
        for (i=0; i<3; i++)
        {
            seg->start[i]=0;
            seg->end[i]=0;
        }
        for (i=0; i<20; i++) 
        {
            seg->start_tag[i]='\0';
            seg->end_tag[i]='\0';
        }

        seg->start[0]= $2;        
        seg->start[1]= $3;        
        seg->start[2]= $4;        
        strncpy(seg->start_tag, $5, 19);

        LIST_Append(line->seg, seg); 
    }
    | stmt FLOAT FLOAT FLOAT EOL_POINTS_START {
        int i;
        KP_SEG* seg= malloc(sizeof(KP_SEG)); 
        if (seg==NULL) 
        {
            fprintf(stderr, "Memory Allocate Error!");
            exit(1);
        }
        for (i=0; i<3; i++)
        {
            seg->start[i]=0;
            seg->end[i]=0;
        }
        for (i=0; i<20; i++) 
        {
            seg->start_tag[i]='\0';
            seg->end_tag[i]='\0';
        }

        seg->start[0]= $2;        
        seg->start[1]= $3;        
        seg->start[2]= $4;        
        LIST_Append(line->seg, seg); 
    }
    | stmt EOL_POINTS_START {
        /*skip*/
    }
    | stmt FLOAT FLOAT FLOAT TAG EOL_POINTS_END {
        KP_SEG* seg= LIST_Get(line->seg,-1);
        seg->end[0]= $2;        
        seg->end[1]= $3;        
        seg->end[2]= $4;        
        strncpy(seg->end_tag, $5, 19);
    }
    | stmt FLOAT FLOAT FLOAT EOL_POINTS_END {
        KP_SEG* seg= LIST_Get(line->seg,-1);
        seg->end[0]= $2;        
        seg->end[1]= $3;        
        seg->end[2]= $4;        
    }
    | stmt EOL_POINTS_END {
        /*skip*/
    }
%%
