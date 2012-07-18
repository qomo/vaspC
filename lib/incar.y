/**********************************************************************
  Copyright (c) 2012 Zhi-Quan Huang 
 
  Permission is hereby granted, free of charge, to any person obtaining 
  a copy of this software and associated documentation files (the 
  "Software"), to deal in the Software without restriction, including 
  without limitation the rights to use, copy, modify, merge, publish, 
  distribute, sublicense, and/or sell copies of the Software, and to 
  permit persons to whom the Software is furnished to do so, subject to 
  the following conditions:
 
  The above copyright notice and this permission notice shall be included 
  in all copies or substantial portions of the Software.
 
  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**********************************************************************/

%{
#include "incar.h"
#include <stdio.h>
#include <stdlib.h>
%}

%union{
    char* s; 
    TYPELIST* tp_list;
}

%token <s> LABEL
%token <s> STR INT BOOL FLOAT
%type <tp_list> strlist intlist boollist floatlist
%token EOL

%start stmt
%%
stmt:                   
    | stmt EOL            {}
    | stmt LABEL '=' strlist EOL {
        SYMBOL* sym= Lookup($2); 
        SYMBOL_Assignment(sym, $4);
        TYPELIST_Free($4);
    }
    | stmt LABEL '=' intlist EOL  {
        SYMBOL* sym= Lookup($2); 
        SYMBOL_Assignment(sym, $4);
        TYPELIST_Free($4);
    }
    | stmt LABEL '=' floatlist EOL {
        SYMBOL* sym= Lookup($2); 
        SYMBOL_Assignment(sym, $4);
        TYPELIST_Free($4);
    }
    | stmt LABEL '=' boollist EOL {
        SYMBOL* sym= Lookup($2); 
        SYMBOL_Assignment(sym, $4);
        TYPELIST_Free($4);
    }
;

strlist: STR          {
            $$= TYPELIST_New();
            TYPELIST_Cat($$, $1, TYPE_STR); 
        }
       | strlist STR  {
            $$= TYPELIST_Cat($1, $2, TYPE_STR); 
        }
;


intlist: INT          {
            $$= TYPELIST_New();
            TYPELIST_Cat($$, $1, TYPE_INT); 
        }
       | intlist INT  {
            $$= TYPELIST_Cat($1, $2, TYPE_INT); 
        }
;

floatlist: FLOAT          {
            $$= TYPELIST_New();
            TYPELIST_Cat($$, $1, TYPE_FLOAT); 
        }
       | floatlist FLOAT  {
            $$= TYPELIST_Cat($1, $2, TYPE_FLOAT); 
        }
;

boollist: BOOL          {
            $$= TYPELIST_New();
            TYPELIST_Cat($$, $1, TYPE_BOOL); 
        }
       | boollist BOOL  {
            $$= TYPELIST_Cat($1, $2, TYPE_BOOL); 
        }
;
