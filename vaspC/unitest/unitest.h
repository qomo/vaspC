
#ifndef _UNITEST_H_
#define _UT_ELEM_H_

/*vmath.c*/
void check_vmath_dot3D();
void check_vmath_cross3D();

/*line.c*/
void check_readline();
void check_nitems();
void check_lstrip();

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

/*potcar.c*/
void check_POTCAR_Read();
/*outcar.c*/
void check_OUTCAR_Read();
#endif
