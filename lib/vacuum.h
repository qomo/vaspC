/**
 * @Author Zhi-Quan Huang
 * @Date 2012-04-18
 */
#ifndef _VACUUM_H_
#define _VACUUM_H_
void FindVac( POSCAR* pos, double vac[3][2]);
bool InVac(double vac[3][2], double pos[3]);
#endif
