/**
 * Date: 2012-05-18
 * Author: Zhi-Quan Huang
 */

#ifndef _GRADIENT_H_
#define _GRADIENT_H_
void Threept3d(double* val, int ngx, int ngy, int ngz,
          double dx, double dy, double dz, 
          double (*vector)[3]);

void Five3d(double* val, int ngx, int ngy, int ngz,
          double dx, double dy, double dz, 
          double (*vector)[3]);
#endif
