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

#include "glib.h"
#include "vaspC.h"
#include <stdlib.h>
#include <stdbool.h>

void check_INCAR_Read()
{
    FILE *pf= NULL;
    INCAR* incar= NULL;
    int type, nargs; 
    int* idata;
    double* ddata;
    bool* bdata;
    

    if ((pf=fopen("data/incar/INCAR","r"))==NULL)
    {
        g_assert(false);
    }

    INCAR_Init(incar);
    INCAR_Read(incar, pf);
    fclose(pf);

    INCAR_Get(incar,"ISTART", &type, &nargs, (void**)&idata);
    g_assert_cmpint(type,==,TYPE_INT);
    g_assert_cmpint(nargs,==,1);
    g_assert_cmpint(idata[0],==,0);

    INCAR_Get(incar,"ISPIN", &type, &nargs, (void**)&idata);
    g_assert_cmpint(type,==,TYPE_INT);
    g_assert_cmpint(nargs,==,1);
    g_assert_cmpint(idata[0],==,1);

    INCAR_Get(incar,"NSW", &type, &nargs, (void**)&idata);
    g_assert_cmpint(type,==,TYPE_INT);
    g_assert_cmpint(nargs,==,1);
    g_assert_cmpint(idata[0],==,0);

    INCAR_Get(incar,"ISIF", &type, &nargs, (void**)&idata);
    g_assert_cmpint(type,==,TYPE_INT);
    g_assert_cmpint(nargs,==,1);
    g_assert_cmpint(idata[0],==,2);

    INCAR_Get(incar,"IBRION", &type, &nargs, (void**)&idata);
    g_assert_cmpint(type,==,TYPE_INT);
    g_assert_cmpint(nargs,==,1);
    g_assert_cmpint(idata[0],==,2);

    INCAR_Get(incar,"EDIFF", &type, &nargs, (void**)&ddata);
    g_assert_cmpint(type,==,TYPE_FLOAT);
    g_assert_cmpint(nargs,==,1);
    g_assert_cmpfloat(ddata[0],==,1E-4);

    INCAR_Get(incar,"EDIFFG", &type, &nargs, (void**)&ddata);
    g_assert_cmpint(type,==,TYPE_FLOAT);
    g_assert_cmpint(nargs,==,1);
    g_assert_cmpfloat(ddata[0],==,-0.001);

    INCAR_Get(incar,"ISMEAR", &type, &nargs, (void**)&idata);
    g_assert_cmpint(type,==,TYPE_INT);
    g_assert_cmpint(nargs,==,1);
    g_assert_cmpint(idata[0],==,0);

    INCAR_Get(incar,"SIGMA", &type, &nargs, (void**)&ddata);
    g_assert_cmpint(type,==,TYPE_FLOAT);
    g_assert_cmpint(nargs,==,1);
    g_assert_cmpint(ddata[0],==,0.001);

    INCAR_Get(incar,"LVTOT", &type, &nargs, (void**)&bdata);
    g_assert_cmpint(type,==,TYPE_BOOL);
    g_assert_cmpint(nargs,==,1);
    g_assert(bdata[0]==false);

    INCAR_Get(incar,"LDIPOL", &type, &nargs, (void**)&bdata);
    g_assert_cmpint(type,==,TYPE_BOOL);
    g_assert_cmpint(nargs,==,1);
    g_assert(bdata[0]==false);

    INCAR_Get(incar,"LCHARG", &type, &nargs, (void**)&bdata);
    g_assert_cmpint(type,==,TYPE_BOOL);
    g_assert_cmpint(nargs,==,1);
    g_assert(bdata[0]==false);

    INCAR_Get(incar,"LAECHG", &type, &nargs, (void**)&bdata);
    g_assert_cmpint(type,==,TYPE_BOOL);
    g_assert_cmpint(nargs,==,1);
    g_assert(bdata[0]==false);

    INCAR_Get(incar,"LWAVE", &type, &nargs, (void**)&bdata);
    g_assert_cmpint(type,==,TYPE_BOOL);
    g_assert_cmpint(nargs,==,1);
    g_assert(bdata[0]==false);

    INCAR_Get(incar,"LPLANE", &type, &nargs, (void**)&bdata);
    g_assert_cmpint(type,==,TYPE_BOOL);
    g_assert_cmpint(nargs,==,1);
    g_assert(bdata[0]==true);

    INCAR_Get(incar,"LSCALU", &type, &nargs, (void**)&bdata);
    g_assert_cmpint(type,==,TYPE_BOOL);
    g_assert_cmpint(nargs,==,1);
    g_assert(bdata[0]==false);

    INCAR_Get(incar,"NSIM", &type, &nargs, (void**)&idata);
    g_assert_cmpint(type,==,TYPE_INT);
    g_assert_cmpint(nargs,==,1);
    g_assert_cmpint(idata[0],==,4);

    INCAR_Get(incar,"NPAR", &type, &nargs, (void**)&idata);
    g_assert_cmpint(type,==,TYPE_INT);
    g_assert_cmpint(nargs,==,1);
    g_assert_cmpint(idata[0],==,1);

    INCAR_Free(incar);
}

void check_INCAR_Set()
{
    int type, nargs;
    int*    idata=NULL;
    bool*   bdata=NULL;
    double* ddata=NULL;
    INCAR* incar= NULL;

    INCAR_Init(incar);

    INCAR_Get(incar, "A", &type, &nargs, (void**) &idata);
    g_assert_cmpint(type,==,TYPE_NULL);
    g_assert_cmpint(nargs,==,0);
    g_assert(idata==NULL);

    idata= malloc(sizeof(int));
    idata[0]=1;
    INCAR_Set(incar, "A", TYPE_INT, 1, (void*) idata);
    idata=NULL;
    INCAR_Get(incar, "A", &type, &nargs, (void**) &idata);
    g_assert_cmpint(type,==,TYPE_INT);
    g_assert_cmpint(nargs,==,1);
    g_assert_cmpint(idata[0],==,1);

    bdata= malloc(sizeof(bool)*2);
    bdata[0]= true; 
    bdata[1]= false; 
    INCAR_Set(incar, "A", TYPE_BOOL, 2, (void*) bdata);
  
    bdata=NULL;
    INCAR_Get(incar, "A", &type, &nargs, (void**) &bdata);
    g_assert_cmpint(type,==,TYPE_BOOL);
    g_assert_cmpint(nargs,==,2);
    g_assert(bdata[0]==true);
    g_assert(bdata[1]==false);

    ddata= malloc(sizeof(double)*3);
    ddata[0]= 1.;
    ddata[1]= 2.;
    ddata[2]= 3.;
    INCAR_Set(incar, "A", TYPE_FLOAT, 3, (void*) ddata);
    ddata=NULL;
    INCAR_Get(incar, "A", &type, &nargs, (void**) &ddata);
    g_assert_cmpint(type,==,TYPE_FLOAT);
    g_assert_cmpint(nargs,==,3);
    g_assert_cmpfloat(ddata[0],==,1.);
    g_assert_cmpfloat(ddata[1],==,2.);
    g_assert_cmpfloat(ddata[2],==,3.);

    INCAR_Free(incar);
}
