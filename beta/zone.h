#ifndef _ZONE_H_
#define _ZONE_H_

#include <stdbool.h>
bool InZone(double vac[3][2], double pos[3]);
void FindAllowed(POSCAR* pos, double vac[3][2], double allow[3][2], int flag);
#endif
