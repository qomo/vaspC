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

%option prefix="incar_"
%option outfile="incar.lex.c"
%option noyywrap nodefault yylineno
%x ARG

%{
#include "incar.h"
#include "incar.tab.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
%}

 /* float exponent */
EXP ([Ee][-+]?[0-9]+)

%%
<INITIAL,ARG>";"|\n {BEGIN INITIAL; return EOL;}
<INITIAL,ARG>[ \t]  {}
<INITIAL,ARG>#.*\n  {BEGIN INITIAL; return EOL;}

<INITIAL>[a-zA-Z0-9][a-zA-Z0-9]* {
        unsigned int i;
        incar_lval.s = malloc(sizeof(char)*(strlen(incar_text)+1));
        strncpy(incar_lval.s, incar_text,strlen(incar_text));
        incar_lval.s[strlen(incar_text)]='\0';
        for (i=0; i<strlen(incar_text)+1; i++)
        {
            incar_lval.s[i]= toupper(incar_lval.s[i]);
        }
        return LABEL;
    }
<INITIAL>"=" {BEGIN ARG; return incar_text[0];}

<ARG>[Tt]{1}|"."(?i:TRUE)"."    {incar_lval.s= "T"; return BOOL;}
<ARG>[Ff]{1}|"."(?i:FALSE)"."   {incar_lval.s= "F"; return BOOL;}
<ARG>[-+]?[0-9]+{EXP}|[-+]?[0-9]+"."[0-9]*{EXP}?|[-+]?"."[0-9]+{EXP}? { incar_lval.s=incar_text; return FLOAT;}
<ARG>[-+]?[0-9]+ { 
        incar_lval.s = malloc(sizeof(char)*(strlen(incar_text)+1));
        strncpy(incar_lval.s, incar_text,strlen(incar_text));
        incar_lval.s[strlen(incar_text)]='\0';
        return INT;
    }
<ARG>[a-zA-Z0-9]+ { incar_lval.s= incar_text; return STR;}

<INITIAL,ARG>.      {incar_error("Mystery character %c\n", *incar_text);}
%%
