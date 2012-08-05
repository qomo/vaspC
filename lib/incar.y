%{
#include "incar.h"
#include "list.h"
#include "keyword.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define YYLEX_PARAM keyword
%}

%name-prefix "incar_"
%parse-param {INCAR* incar}
%parse-param {KEYWORD* keyword}

%union{
    bool b;
    double d;
    int i;
    char* s; 
    LIST* list;
}

%token <s> LABEL LABEL_LIST
%token <b> BOOL
%token <i> INT
%token <d> FLOAT
%token <s> STR
%type <list> BOOL_LIST INT_LIST FLOAT_LIST
%token EOL

%start stmt
%%
stmt:                   
    | stmt EOL               {}
    | stmt LABEL BOOL EOL {
        INCAR_Set(incar,$2, POINTER_MALLOC(&($3), bool, 1));
        free($2);
    }
    | stmt LABEL INT EOL {
        INCAR_Set(incar,$2, POINTER_MALLOC(&($3), int, 1));
        free($2);
    }
    | stmt LABEL FLOAT EOL {
        INCAR_Set(incar,$2, POINTER_MALLOC(&($3), double, 1));
        free($2);
    }
    | stmt LABEL_LIST BOOL_LIST EOL{
        INCAR_Set(incar,$2, $3);
        free($2);
    }
    | stmt LABEL_LIST INT_LIST EOL{
        INCAR_Set(incar,$2, $3);
        free($2);
    }
    | stmt LABEL_LIST FLOAT_LIST EOL{
        INCAR_Set(incar,$2, $3);
        free($2);
    }
    | stmt LABEL STR EOL {
        INCAR_Set(incar,$2, $3);
        free($2);
    }
    | stmt error EOL {
        fprintf(stderr, "Parsing INCAR failed. At line %d\n",incar_lineno);
        yyerrok;
    }
;

BOOL_LIST: BOOL {
            LIST* list= NULL;
            LIST_Init(list);
            bool b= $1;
            LIST_Append(list, POINTER_MALLOC(&b, bool , 1));
            $$= list;
          }
          |BOOL_LIST BOOL {
            bool b= $2;
            LIST_Append($1, POINTER_MALLOC(&b, bool , 1));
            $$= $1;
          }
;

INT_LIST: INT {
            LIST* list= NULL;
            LIST_Init(list);
            int i= $1;
            LIST_Append(list, POINTER_MALLOC(&i, int , 1));
            $$= list;
          }
          |INT_LIST INT {
            int i= $2;
            LIST_Append($1, POINTER_MALLOC(&i, int , 1));
            $$= $1;
          }
;
FLOAT_LIST: FLOAT {
            LIST* list= NULL;
            LIST_Init(list);
            double d= $1;
            LIST_Append(list, POINTER_MALLOC(&d, double , 1));
            $$= list;
          }
          |FLOAT_LIST FLOAT {
            double d= $2;
            LIST_Append($1, POINTER_MALLOC(&d, double , 1));
            $$= $1;
          }
;
