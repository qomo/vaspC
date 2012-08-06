%{
#include "outcar.h"
#include "list.h"
#include "util.h"
%}

%name-prefix "outcar_"
%parse-param {OUTCAR* outcar}

%union {
    char* s;
    double d;
    LIST* list;
}

%token<s> LABEL_LIST LABEL
%token<s> STR
%token<d> FLOAT
%type<list> STR_LIST
%token    EOL

%start stmt

%%

stmt:
    | stmt EOL       {}
    | stmt LABEL FLOAT EOL {
        LIST* list_float= OUTCAR_Get(outcar, $2);
        if (list_float==NULL)
        {
            LIST* new_list_float= NULL;
            LIST_Init(new_list_float);
            OUTCAR_Set(outcar, $2, new_list_float);
        }
        double d= $3;
        list_float= OUTCAR_Get(outcar, $2);
        LIST_Append(list_float, POINTER_MALLOC(&d,double,1));
        free($2);
    }
    | stmt LABEL_LIST STR_LIST EOL  {
        LIST* list_str_list= OUTCAR_Get(outcar, $2); 
        if (list_str_list==NULL)
        {
            LIST* new_str_list=NULL;
            LIST_Init(new_str_list);
            OUTCAR_Set(outcar, $2, new_str_list);
        } 
        list_str_list= OUTCAR_Get(outcar, $2);
        LIST_Append(list_str_list, $3);
        free($2);
    } 
;

STR_LIST: STR {
            LIST* new_list=NULL;
            LIST_Init(new_list);
            LIST_Append(new_list, $1); 
            $$= new_list;
        }
        |  STR_LIST STR {
            LIST_Append($1, $2);
            $$=$1; 
        }
;
%%
