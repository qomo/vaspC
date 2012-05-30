#ifndef _VMATH_H_
#define _VMATH_H_
double dot3D(double lvec[3], double rvec[3])
{
    int i;
    double ret=0.0;

    for (i=0; i<3; i++)
    {
        ret+=lvec[i]*rvec[i];
    }
    return ret;
}

void cross3D(double vec1[3], double vec2[3], double vec[3])
{
    vec[0]= vec1[1]*vec2[2]-vec1[2]*vec2[1];
    vec[1]= vec1[2]*vec2[0]-vec1[0]*vec2[2];
    vec[2]= vec1[0]*vec2[1]-vec1[1]*vec2[0];
}

#endif
