#ifndef SOLUTIONOFDIFFERENTIALEQUATIONS_SYSTEM1_H
#define SOLUTIONOFDIFFERENTIALEQUATIONS_SYSTEM1_H

[[maybe_unused]] const double x_1_0 = 0, y_1_0 = 0, x_2_0 = 0, u_2_0 = 1, v_2_0 = 0.5;

double func1 (double x,double y);

double sol1 (double x);

double func2_1(double x, double u, double v);

double func2_2(double x, double u, double v);

double p(long double x);

double q(long double x);

double f(long double x);

#include "system1.h"

#endif
