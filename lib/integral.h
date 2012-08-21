#ifndef INTEGRAL_H_
#define INTEGRAL_H_

double Simpson_int(double h, double* y, int size);
double Simpson38_int(double h, double* y, int size);
double Simpson_float(const double h, const double y0, const double y1, const double y2, const double size);
double Simpson38_float(const double h, const double y0, const double y1, const double y2, const double y3, const double size);
#endif
