#include "glib.h"
#include "vaspC.h"
#include <stdio.h>

void check_KPOINTS_New_Free()
{
    KPOINTS_MESH* mesh= NULL;
    mesh= KPOINTS_MESH_New();
    KPOINTS_MESH_Free(mesh);

    KPOINTS_GRID* grid= NULL;
    grid= KPOINTS_GRID_New();
    KPOINTS_GRID_Free(grid);

    KPOINTS_LINE* line= NULL;
    line= KPOINTS_LINE_New();
    KPOINTS_LINE_Free(line);

    KPOINTS* kp= NULL;
    kp= KPOINTS_New(TYPE_MESH);      
    KPOINTS_Free(kp);

    kp=NULL;
    kp= KPOINTS_New(TYPE_GRID);      
    KPOINTS_Free(kp);

    kp=NULL;
    kp= KPOINTS_New(TYPE_LINE);      
    KPOINTS_Free(kp);
}

void check_KPOINTS_File_Type()
{
    FILE* pf;
   
    pf=fopen("data/kpoints/KPOINTS_MESH","r");
    g_assert(pf);
    g_assert(KPOINTS_File_Type(pf)==TYPE_MESH);
    fclose(pf);

    pf=fopen("data/kpoints/KPOINTS_GRID","r");
    g_assert(pf);
    g_assert(KPOINTS_File_Type(pf)==TYPE_GRID);
    fclose(pf);

    pf=fopen("data/kpoints/KPOINTS_LINE","r");
    g_assert(pf);
    g_assert(KPOINTS_File_Type(pf)==TYPE_LINE);
    fclose(pf);

}

void check_KPOINTS_MESH_Read()
{
    FILE* pf;
   
    pf=fopen("data/kpoints/KPOINTS_MESH","r");
    g_assert(pf);

    KPOINTS_MESH* mesh= NULL;
    mesh= KPOINTS_MESH_New();

    KPOINTS_MESH_Read(mesh, pf);

    g_assert_cmpstr(mesh->comment,==,"KMesh");
    g_assert(mesh->isGamma);
    g_assert_cmpint(mesh->nmesh[0],==,11);
    g_assert_cmpint(mesh->nmesh[1],==,12);
    g_assert_cmpint(mesh->nmesh[2],==,13);
    g_assert_cmpfloat(mesh->shift[0],==,0);
    g_assert_cmpfloat(mesh->shift[1],==,1);
    g_assert_cmpfloat(mesh->shift[2],==,2);

    fclose(pf);
    KPOINTS_MESH_Free(mesh);
}
