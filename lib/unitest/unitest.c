/**
 * @breif unittest
 * @author Zhi-Quan Huang
 * @date 2012-04-16
 */

#include "glib.h"
#include "vaspC.h"
#include "unitest.h"

int main(int argc, char** argv)
{
    g_test_init(&argc, &argv, NULL);
    g_test_add_func ("/line/readline",     check_readline);
    g_test_add_func ("/line/nitems",       check_nitems);
    g_test_add_func ("/line/rstrip",       check_rstrip);
    g_test_add_func ("/element",           check_element);
    g_test_add_func ("/vmath/dot3D",       check_vmath_dot3D);
    g_test_add_func ("/vmath/cross3D",     check_vmath_cross3D);
    g_test_add_func ("/lattice/A2B",       check_LATTICE_A2B);
    g_test_add_func ("/lattice/D2C",       check_LATTICE_D2C);
    g_test_add_func ("/lattice/C2D",       check_LATTICE_C2D);
    g_test_add_func ("/poscar/lat2rec",    check_POSCAR_A2B);
    g_test_add_func ("/poscar/read/v5",    check_POSCAR_Read_v5);
    g_test_add_func ("/poscar/read/v4",    check_POSCAR_Read_v4);
    g_test_add_func ("/poscar/read/Ndyn",  check_POSCAR_Read_NDYN);
    g_test_add_func ("/poscar/D2C",        check_POSCAR_D2C);
    g_test_add_func ("/poscar/C2D",        check_POSCAR_C2D);
    g_test_add_func ("/poscar/LatXRec"   , check_POSCAR_LatXRec);
    g_test_add_func ("/poscar/Copy"      , check_POSCAR_Copy);
    g_test_add_func ("/poscar/Confined"  , check_POSCAR_Confined);
    g_test_add_func ("/field/read/POSCAR", check_SCALAR3D_ReadPOSCAR);
    g_test_add_func ("/field/read/Lat"   , check_SCALAR3D_ReadLat);
    g_test_add_func ("/field/read/Grid"  , check_SCALAR3D_ReadGrid);
    g_test_add_func ("/field/read/Val"  ,  check_SCALAR3D_ReadVal);
    /*gradient.c*/
    g_test_add_func ("/gradient/Threept3d/X",     check_Threept3dX);
    g_test_add_func ("/gradient/Threept3d/Y",     check_Threept3dY);
    g_test_add_func ("/gradient/Threept3d/Z",     check_Threept3dZ);
    g_test_add_func ("/gradient/Fivept3d/X",        check_Fivept3dX);
    g_test_add_func ("/gradient/Fivept3d/Y",        check_Fivept3dY);
    g_test_add_func ("/gradient/Fivept3d/Z",        check_Fivept3dZ);
    /*sort*/
    g_test_add_func ("/sortcol/swap"  ,      check_swap);
    g_test_add_func ("/sortcol/insort" ,     check_insort);
    /*vacuum.c*/
    g_test_add_func ("/vacuum/Find/X"  ,     check_FindVacX);
    g_test_add_func ("/vacuum/Find/Y"  ,     check_FindVacY);
    g_test_add_func ("/vacuum/Find/Z"  ,     check_FindVacZ);
    g_test_add_func ("/vacuum/Find/XY"  ,    check_FindVacXY);
    g_test_add_func ("/vacuum/Find/XYZ"  ,   check_FindVacXYZ);
    g_test_add_func ("/vacuum/In"  ,         check_InVac);
    g_test_add_func ("/list/Append"  ,       check_LIST_Append);
    g_test_add_func ("/list/Item"  ,         check_LIST_Item);
    g_test_add_func ("/list/Get"  ,          check_LIST_Get);
    g_test_add_func ("/list/NItem"  ,        check_LIST_NItem);
    g_test_add_func ("/HASH/base36"  ,       check_base36);
    g_test_add_func ("/HASH/equal_str",      check_equal_str);
    g_test_add_func ("/HASH/fold"  ,         check_fold);
    g_test_add_func ("/HASH/New_Free"  ,     check_hash_new_free);
    g_test_add_func ("/HASH/Lookup"  ,       check_hash_lookup);
    g_test_add_func ("/HASH/Set_Get"  ,    check_hash_set_get);
    g_test_add_func ("/POTCAR/New_Free",     check_POTCAR_New_Free);
    g_test_add_func ("/POTCAR/Set_Get",      check_POTCAR_Set_Get);
    g_test_add_func ("/POTCAR/File_Count",   check_File_Count_POTCAR);
    g_test_add_func ("/POTCAR/Array_New_Free",check_POTCAR_Array_New_Free);
    g_test_add_func ("/OUTCAR/New_Free"  ,   check_OUTCAR_New_Free);
    g_test_add_func ("/OUTCAR/Set_Get"  ,    check_OUTCAR_Set_Get);
    g_test_add_func ("/OUTCAR/Read"  ,       check_OUTCAR_Read);
    g_test_add_func ("/KEYWORD/New_Free",    check_KEYWORD_New_Free);
    g_test_add_func ("/KEYWORD/Set_Get",    check_KEYWORD_Set_Get);
    g_test_add_func ("/KEYWORD/Read",    check_KEYWORD_Read);
    g_test_add_func ("/INCAR/New_Free"  ,    check_INCAR_New_Free);
    g_test_add_func ("/INCAR/Set_Get"  ,     check_INCAR_Set_Get);
    g_test_add_func ("/INCAR/Read"  ,        check_INCAR_Read);
    g_test_add_func ("/KPOINTS/New_Free"  ,  check_KPOINTS_New_Free);
    g_test_add_func ("/KPOINTS/File_Type" ,  check_KPOINTS_File_Type);
    return g_test_run();
 }
