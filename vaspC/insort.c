#include "swap.h"
#include <stdbool.h>

void insort(double* base, unsigned int n, unsigned int m, unsigned int col, bool inverse) 
{
    int i,j;
    double *p,*q;

    for (i=0; i<n; i++)
        for (j=i+1; j<n; j++)
        {
            p= base+(i*m);
            q= base+(j*m);
            
            if (!inverse)
            {
                if (*(p+col)>*(q+col))
                {
                    swap(p,q,sizeof(double)*m); 
                }
            }
            else
            {
                if (*(p+col)<*(q+col))
                {
                    swap(p,q,sizeof(double)*m); 
                }
            }
        }
}
