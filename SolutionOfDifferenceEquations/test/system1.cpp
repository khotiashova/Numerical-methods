#ifndef SOLUTIONOFDIFFERENTIALEQUATIONS_SYSTEM1_CPP
#define SOLUTIONOFDIFFERENTIALEQUATIONS_SYSTEM1_CPP

#include "system1.h"
#include <cmath>

double func1 (double x,double y) {
    return - y - x*x;
}

double sol1 (double x) {
    return -x*x + 2*x - 2 + 12*exp(-x);
}

double func2_1(double x, double u, double v) {
    return sin(1.4 * u * u) - x + v;
}

double func2_2(double x, double u, double v) {
    return x + u - 2.2*v*v + 1;
}

double p(long double x) {
    return 2;
}

double q(long double x) {
    return -x;
}

double f(long double x) {
    return x * x;
}

#endif
