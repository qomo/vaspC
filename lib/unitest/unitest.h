
#ifndef _UNITEST_H_
#define _UT_ELEM_H_

/*vmath.c*/
void check_vmath_dot3D();
void check_vmath_cross3D();

/*line.c*/
void check_readline();
void check_nitems();
void check_rstrip();

/*element.c*/
void check_element();

/*lattice.c*/
void check_LATTICE_A2B();
void check_LATTICE_C2D();
void check_LATTICE_D2C();

/*poscar.c*/
void check_POSCAR_A2B();
void check_POSCAR_D2C();
void check_POSCAR_C2D();
void check_POSCAR_Read_v5();
void check_POSCAR_Read_v4();
void check_POSCAR_Read_NDYN();
void check_POSCAR_LatXRec();
void check_POSCAR_Copy();
void check_POSCAR_Confined();

/*field.c*/
void check_SCALAR3D_ReadPOSCAR();
void check_SCALAR3D_ReadLat();
void check_SCALAR3D_ReadGrid();
void check_SCALAR3D_ReadVal();

/*gradient.c*/
void check_Threept3dX();
void check_Threept3dY();
void check_Threept3dZ();
void check_Fivept3dX();
void check_Fivept3dY();
void check_Fivept3dZ();

/*insort.c*/
void check_insort();

/*swap.c*/
void check_swap();

/*vacuum.c*/
void check_FindVacX();
void check_FindVacY();
void check_FindVacZ();
void check_FindVacXY();
void check_FindVacXYZ();
void check_InVac();

/*list.c*/
void check_LIST_Append();
void check_LIST_Item();
void check_LIST_NItem();
void check_LIST_Get();

/*potcar.c*/
void check_POTCAR_New_Free();
void check_POTCAR_Set_Get(); 
void check_File_Count_POTCAR();
void check_POTCAR_Array_New_Free();

/*outcar.c*/
void check_OUTCAR_New_Free();
void check_OUTCAR_Set_Get();
void check_OUTCAR_Read();

/*incar.c*/
void check_KEYWORD_New_Free();
void check_KEYWORD_Set_Get();
void check_KEYWORD_Read();
void check_INCAR_New_Free();
void check_INCAR_Set_Get();
void check_INCAR_Read();

/*hash.c*/
void check_base36();
void check_equal_str();
void check_fold();
void check_hash_new_free();
void check_hash_count();
void check_hash_lookup();
void check_hash_set_get();

/*kpoints.c*/
void check_KPOINTS_New_Free();
void check_KPOINTS_File_Type();
void check_KPOINTS_MESH_Read();
void check_KPOINTS_LINE_Read();
void check_KPOINTS_GRID_Read();

/*integral.c*/
void check_Simpson_int();
void check_Simpson38_int();
void check_Simpson_float();
void check_Simpson38_float();

#endif
