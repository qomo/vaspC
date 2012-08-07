%{
#include "kpoints.h"
#include "kp_mesh.h"
%}


%name-prefix "kp_mesh_"
%parse-param {KPOINTS_MESH* mesh}

%union{
    int i;
    bool b;
    char* s;
    double d;
}

%token <b> BOOL
%token <s> STR
%token <i> INT
%token <d> FLOAT
%token EOL_COMMENT
%token EOL_NGRID
%token EOL_M_G
%token EOL_MESH
%token EOL_SHIFT
%token EOL

%start stmt

%%
stmt:
    | stmt STR EOL_COMMENT {
        mesh->comment= $2;        
    }
    | stmt INT EOL_NGRID {
    }
    | stmt BOOL EOL_M_G {
        mesh->isGamma= $2; 
    }
    | stmt INT INT INT EOL_MESH {
        mesh->nmesh[0]= $2;
        mesh->nmesh[1]= $3;
        mesh->nmesh[2]= $4;
    }
    | stmt FLOAT FLOAT FLOAT EOL_SHIFT {
        mesh->shift[0]= $2;
        mesh->shift[1]= $3;
        mesh->shift[2]= $4;
        YYACCEPT;
    }
%%
