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

#include "incar.h"
#include "list.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

TYPELIST* TYPELIST_New()
{
    TYPELIST* tplist=NULL;

    tplist= malloc(sizeof(TYPELIST));
    if (!tplist)
    {
        yyerror("Out of memory!!");
        exit(0);
    }

    tplist->type= TYPE_NULL;
    tplist->list= NULL; 
    LIST_Init(tplist->list);
    return tplist;
}

TYPELIST* TYPELIST_Cat(TYPELIST* tplist, char* text, int type)
{
    if (tplist==NULL)
    {
        yyerror("Internal Error: tplist is a null pointer.");
        exit(0);
    }
    if (text == NULL)
    {
        yyerror("Internal Error: text is a null pointer.");
        exit(0);
    }

    tplist->type= type;
    LIST_Append(tplist->list, text, sizeof(char)*(strlen(text)+1));

    return tplist;
}

void _TYPELIST_Free(TYPELIST** ptplist)
{
    if ((*ptplist)==NULL)
    {
        yyerror("Internal Error: tplist is a null pointer.");
        exit(0);
    }
    
    LIST_Free((*ptplist)->list);
    (*ptplist)->list=NULL;
    free(*ptplist);
    (*ptplist)=NULL;
}

void yyerror(char *s, ...)
{
    va_list ap;
    va_start(ap, s);
    
    fprintf(stderr, "%d: error: ", yylineno);
    vfprintf(stderr, s, ap);
    fprintf(stderr, "\n");
}

static SYMBOL symtab[NHASH];

static unsigned symhash(char *sym)
{
    unsigned int hash = 0;
    unsigned c;
    while ((c= *sym++))
    {
        hash= hash *9 ^c;
    }
    return hash;
}

SYMBOL* Lookup(char* sym)
{
    SYMBOL *sp= &symtab[symhash(sym)%NHASH];
    int scount = NHASH; /*how many have we looked at*/

    while(--scount >=0){
        if (sp->name && !strcmp(sp->name, sym)) {return sp;}

        if (!sp->name){
            /*new entry*/
            sp->name= strdup(sym);
            sp->type= TYPE_NULL;
            sp->nargs=0;
            sp->data= NULL;
            return sp;
        }

        if (++sp>=symtab+NHASH) sp= symtab; /*try the next entry*/
    }
    yyerror("symbol table overflow\n");
    abort(); /*tried them all, table is full*/
}

void SYMBOL_Assignment(SYMBOL* sym, TYPELIST* tplist)
{
    int i;
    if (sym==NULL)
    {
        yyerror("Internal Error: sym is a null pointer.");
        exit(0);
    }
    if (tplist==NULL)
    {
        yyerror("Internal Error: tplist is a null pointer");
        exit(0);
    }

    sym->type= tplist->type;
    if (sym->type==TYPE_NULL)
    {
        yyerror("Internal Error: tplist->type is TYPE_NULL.");
        exit(0);
    }

    sym->nargs= LIST_NItem(tplist->list);
    switch (sym->type)
    {
        case TYPE_BOOL:
            sym->data= malloc(sizeof(bool)*sym->nargs); 
            bool* pbool= (bool*) sym->data;
            for (i=0; i<sym->nargs; i++)
            {
                char* text= LIST_Item(tplist->list, i)->val;
                if (strcmp(text, "T")==0||strcmp(text,"t")==0)
                {
                    pbool[i]=true;
                }
                else if(strcmp(text,"F")==0||strcmp(text,"f")==0)
                {
                    pbool[i]=false;
                }
                else
                {
                    yyerror("Internal Error: Parse Bool Value Failed. %s",text);
                    exit(0);
                }
            }
            break;
        case TYPE_INT:
            sym->data= malloc(sizeof(int)*sym->nargs);
            int* pint= (int*) sym->data;
            for (i=0; i<sym->nargs; i++)
            {
                char* text= LIST_Item(tplist->list, i)->val;
                if (sscanf(text, "%d", &pint[i])!=1)
                {
                    yyerror("Internal Error: Parse Int value Failed. %s",text);
                    exit(0);
                }
            }
            break;
        case TYPE_FLOAT:
            sym->data= malloc(sizeof(double)*sym->nargs);
            double* pdouble= (double*) sym->data;
            for (i=0; i<sym->nargs; i++)
            {
                char* text= LIST_Item(tplist->list, i)->val;
                if (sscanf(text, "%lf", &pdouble[i])!=1)
                {
                    yyerror("Internal Error: Parse Double value Failed. %s",text);
                    exit(0);
                }
            }
            break;

        case TYPE_STR:
            sym->data= malloc(sizeof(char*)*sym->nargs); 
            char** pch= (char**)sym->data;
            for (i=0; i<sym->nargs; i++) 
            {
                char* pdata= LIST_Item(tplist->list, i)->val;
                pch[i]= malloc(sizeof(char)*(strlen(pdata)+1));
                strcpy(pch[i], pdata);
            }
            break;
        default:
            yyerror("Internal Error: sym->type is not a valid value.");
            exit(0);
    }
}

void _INCAR_Init(INCAR** incar)
{
    int i;
    if ((*incar)!=NULL) _INCAR_Free(incar); 
    (*incar)= malloc(sizeof(INCAR)); 
    if (!(*incar))
    {
        fprintf(stderr, "Allocate Memroy Error: INCAR\n");
        exit(0);
    }

    for (i=0; i<NHASH ;i++)
    {
        SYMBOL *sp= &((*incar)->symtab[i]);
        sp->name= NULL;
        sp->type= TYPE_NULL;
        sp->nargs= 0;
        sp->data= NULL; 
    }
}

void _INCAR_Free(INCAR** incar)
{
    int i;
    for (i=0; i<NHASH; i++)
    {
        SYMBOL* sp= &((*incar)->symtab[i]);
        if (sp->name!=NULL)
        {
            free(sp->name);
            sp->name=NULL;
        }

        if (sp->data!=NULL)
        { 
            free(sp->data);
            sp->data=NULL;
        }
    }
    free(*incar);
    *incar=NULL;
}

void INCAR_Read(INCAR* incar, FILE* pf)
{
    int i;

    for (i=0; i<NHASH; i++)
    {
        symtab[i].name=NULL;
        symtab[i].type= TYPE_NULL;
        symtab[i].nargs= 0;
        symtab[i].data= NULL;
    }

    if (pf==stdin)
    {
        yyparse();
    }
    else
    {
        yyin= pf;
        yyparse();
    }
    for (i=0; i<NHASH; i++)
    {
        if (symtab[i].name==NULL) continue;
        incar->symtab[i].name= symtab[i].name;
        incar->symtab[i].type= symtab[i].type;
        incar->symtab[i].nargs= symtab[i].nargs;
        incar->symtab[i].data= symtab[i].data;

        symtab[i].name=NULL;
        symtab[i].type=TYPE_NULL;
        symtab[i].nargs=0;
        symtab[i].data=NULL;
    }
}

void INCAR_RawWrite(INCAR* incar, FILE* fp)
{
    int i,n;
    for (i=0; i<NHASH; i++)
    {
        if (incar->symtab[i].name==NULL) continue;
        fprintf(fp,"%s", incar->symtab[i].name);
        fprintf(fp,"=");
        bool *pbool=NULL;
        int *pint=NULL;
        char** pstr=NULL;
        double* pfloat=NULL;
        switch (incar->symtab[i].type)
        {
            case TYPE_NULL:
                yyerror("Internal Error: incar->symtab.type is TYPE_NULL");
                exit(0);
                break;
            case TYPE_BOOL:
                pbool= incar->symtab[i].data;
                for (n=0; n<incar->symtab[i].nargs; n++)
                {
                    fprintf(fp, " %s", pbool[n]?"T":"F");
                }
                break;
            case TYPE_INT:
                pint= incar->symtab[i].data;
                for (n=0; n<incar->symtab[i].nargs; n++)
                {
                    fprintf(fp, " %d", pint[n]);
                }
                break;
            case TYPE_STR:
                pstr= incar->symtab[i].data;
                for (n=0; n<incar->symtab[i].nargs; n++)
                {
                    fprintf(fp, " %s", pstr[n]);
                }
                break;
            case TYPE_FLOAT:
                pfloat= incar->symtab[i].data;
                for (n=0; n<incar->symtab[i].nargs; n++)
                {
                    fprintf(fp, " %.4e", pfloat[n]);
                }
                break;
        }
        fprintf(fp,"\n");
    }
}

void INCAR_Get(INCAR* incar, char* name, int *type, int *nargs, void** data)
{
    SYMBOL *sp= &incar->symtab[symhash(name)%NHASH];
    int scount= NHASH;    

    while(--scount >=0)
    {
        if(sp->name && !strcmp(sp->name,name))
        {
            *type= sp->type;
            *nargs= sp->nargs;
            *data= sp->data;
            return;
        }
        if (++sp>=incar->symtab+NHASH) sp= incar->symtab;
    }
    *type= TYPE_NULL;
    *nargs= 0;
    *data= NULL;
    return;
}

void INCAR_Set(INCAR* incar, char* name, int type, int nargs, void* data)
{
    SYMBOL *sp= &incar->symtab[symhash(name)%NHASH];
    int scount= NHASH;    
    
    while (--scount>=0)  
    {
        if (sp->name && !strcmp(sp->name,name)) 
        {
            sp->type= type;
            sp->nargs= nargs;

            if (sp->data!=NULL)
            {
                free(sp->data);
                sp->data=NULL;
            }
            sp->data= data;
            return;
        }

        if (!sp->name)
        {
            sp->name= strdup(name);
            sp->type= type;
            sp->nargs=nargs;
            sp->data=data;
            return;
        }

        if (++sp>=incar->symtab+NHASH) sp= incar->symtab;
    }
    fprintf(stderr, "symbol table overflow\n");
    exit(1);
}

/**int main()
{
    INCAR* incar=NULL;
    INCAR_Init(incar);
    printf("INCAR_Read\n");
    INCAR_Read(incar, stdin);
    printf("INCAR_RawWrite\n");
    INCAR_RawWrite(incar, stdout);
    INCAR_Free(incar);
}
**/
