%{
#include "util.h"
#include "keyword.h"
%}

%name-prefix "keyword_"
%parse-param {KEYWORD* keyword}

%union{
    char* s;
}

%token <s> KEY
%token BOOL INT FLOAT STR
%token BOOL_LIST INT_LIST FLOAT_LIST
%token EOL 

%start stmt
%%
stmt:                   
    | stmt EOL              {}
    | stmt KEY '=' BOOL EOL {
        enum KEYWORD_TYPE type= TYPE_BOOL;
        KEYWORD_Set(keyword, $2, POINTER_MALLOC(&type, enum KEYWORD_TYPE, 1));
        free($2);
    }
    | stmt KEY '=' BOOL_LIST EOL {
        enum KEYWORD_TYPE type= TYPE_BOOL_LIST;
        KEYWORD_Set(keyword, $2, POINTER_MALLOC(&type, enum KEYWORD_TYPE, 1));
        free($2);
    }
    | stmt KEY '=' INT EOL {
        enum KEYWORD_TYPE type= TYPE_INT;
        KEYWORD_Set(keyword, $2, POINTER_MALLOC(&type, enum KEYWORD_TYPE, 1));
        free($2);
    }
    | stmt KEY '=' INT_LIST EOL {
        enum KEYWORD_TYPE type= TYPE_INT_LIST;
        KEYWORD_Set(keyword, $2, POINTER_MALLOC(&type, enum KEYWORD_TYPE, 1));
        free($2);
    }
    | stmt KEY '=' FLOAT EOL {
        enum KEYWORD_TYPE type= TYPE_FLOAT;
        KEYWORD_Set(keyword, $2, POINTER_MALLOC(&type, enum KEYWORD_TYPE, 1));
        free($2);
    }
    | stmt KEY '=' FLOAT_LIST EOL {
        enum KEYWORD_TYPE type= TYPE_FLOAT_LIST;
        KEYWORD_Set(keyword, $2, POINTER_MALLOC(&type, enum KEYWORD_TYPE, 1));
        free($2);
    }
    | stmt KEY '=' STR EOL {
        enum KEYWORD_TYPE type= TYPE_STR;
        KEYWORD_Set(keyword, $2, POINTER_MALLOC(&type, enum KEYWORD_TYPE, 1));
        free($2);
    }
;
