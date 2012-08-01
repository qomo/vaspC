%{
#include "potcar.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static int COUNT_POT=0;
%}

%name-prefix "potcar_"
%parse-param {POTCAR** pot_array}
%parse-param {int npot}

%union{
    int i;
    char* s; 
    double d;
    bool b;
}

%token <s> LABEL STR
%token <d> FLOAT
%token <b> BOOL
%token <i> INT
%token EOL COUNT END

%start stmt
%%
stmt:                   
    | stmt EOL                   {}
    | stmt LABEL '=' INT EOL   {
        void *p= POINTER_MALLOC(&($4), int, 1);
        POTCAR_Set(pot_array[COUNT_POT], $2, p);
        free($2);
      }
    | stmt LABEL '=' FLOAT EOL   {
        void *p= POINTER_MALLOC(&($4), double, 1);
        POTCAR_Set(pot_array[COUNT_POT], $2, p);
        free($2);
      }
    | stmt LABEL '=' BOOL  EOL   {
        void *p= POINTER_MALLOC(&($4), bool, 1);
        POTCAR_Set(pot_array[COUNT_POT], $2, p);
        free($2);
      }
    | stmt LABEL '=' STR STR STR EOL {
        const size_t size= 3*sizeof(char*)
                           +(strlen($4)+1)*sizeof(char)
                           +(strlen($5)+1)*sizeof(char)
                           +(strlen($6)+1)*sizeof(char);

        char **strs= malloc(size);
        if (strs==NULL)
        {
            potcar_error("Memory Allocate Error!");
        }
        else
        {
            void *p= strs;
            strs[0]= p+3*sizeof(char*);
            strs[1]= p+3*sizeof(char*)+(strlen($4)+1)*sizeof(char);
            strs[2]= p+3*sizeof(char*)+(strlen($4)+1)*sizeof(char)+(strlen($5)+1)*sizeof(char);
            strncpy(strs[0], $4, strlen($4));
            strncpy(strs[1], $5, strlen($5));
            strncpy(strs[2], $6, strlen($6));
            strs[0][strlen($4)]='\0';
            strs[1][strlen($5)]='\0';
            strs[2][strlen($6)]='\0';
        }
        POTCAR_Set(pot_array[COUNT_POT], $2, strs);
        free($2); free($4); free($5); free($6);
      }
    | stmt LABEL '=' STR STR EOL {
        const int size=  2*sizeof(char*)
                        +(strlen($4)+1)*sizeof(char)
                        +(strlen($5)+1)*sizeof(char);
        char **strs= malloc(size);
        if (strs==NULL)
        {
            potcar_error("Memory Allocate Error!");
        }
        else
        {
            void *p= strs;
            strs[0]= p+2*sizeof(char*);
            strs[1]= p+2*sizeof(char*)+(strlen($4)+1)*sizeof(char);
            strncpy(strs[0], $4, strlen($4));
            strncpy(strs[1], $5, strlen($5));
            strs[0][strlen($4)]='\0';
            strs[1][strlen($5)]='\0';
        }
        POTCAR_Set(pot_array[COUNT_POT], $2, strs);
        free($2); free($4); free($5);
      }
    
    | stmt LABEL '=' STR EOL {
        void *p= POINTER_MALLOC($4, char, sizeof($4)+1);
        POTCAR_Set(pot_array[COUNT_POT], $2, p);
        free($2); free($4);
      }
    | stmt COUNT EOL             {
        COUNT_POT++;
        if (COUNT_POT>npot)
        {
            potcar_error("Parsing Number of POTCAR out of range.");
        }
    }
    | stmt END {
            COUNT_POT=0;
            YYACCEPT;
    }
;
