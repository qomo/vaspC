/**
 * @Author Zhi-Quan Huang
 * @Date 2012-04-18
 */
#ifndef _BETA_H_
#define _BETA_H

double beta(SCALAR3D* loc, SCALAR3D* locE, double applyE, int directionE,
            double allow[3][2], 
            double max_pos[3], double max_vec[3],
            int algo_flag);

#endif
