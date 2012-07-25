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

#ifndef _INCAR_H_
#define _INCAR_H_
#define NHASH 3000

#include "list.h"
#include <stdio.h>

extern int incar_lineno; /* from lexer */
extern FILE *incar_in;
extern int incar_parse();
extern int incar_lex();

enum
{
    TYPE_NULL,
    TYPE_BOOL,
    TYPE_INT,
    TYPE_STR,
    TYPE_FLOAT
};

typedef struct
{
    int type;
    LIST* list; 
} TYPELIST;

typedef struct
{
    char *name;
    int type;
    int nargs;
    void* data;
} SYMBOL;

typedef struct
{
    SYMBOL symtab[NHASH];
} INCAR;

/*TYPELIST*/
TYPELIST* TYPELIST_New();
TYPELIST* TYPELIST_Cat(TYPELIST* tplist, char* text, int type);
TYPELIST* TYPELIST_Assignment(TYPELIST* tplist, char* text, int type);
void _TYPELIST_Free(TYPELIST** ptplist);
#define TYPELIST_Free(x) (&(x))

/*SYMBOL*/
SYMBOL *Lookup(char*);
void SYMBOL_Assignment(SYMBOL* sym, TYPELIST* tplist);

/*INCAR*/
void _INCAR_Init(INCAR** incar);
#define INCAR_Init(x) _INCAR_Init(&(x))
void _INCAR_Free(INCAR** incar);
#define INCAR_Free(x) _INCAR_Free(&(x))
void INCAR_Read(INCAR* incar, FILE* pf);
void INCAR_RawWrite(INCAR* incar, FILE* pf);
void INCAR_Get(INCAR* incar, char* name, int *type, int *nargs, void** data);
void INCAR_Set(INCAR* incar, char* name, int type, int nargs, void* data);

void incar_error(char *s, ...);

#endif
