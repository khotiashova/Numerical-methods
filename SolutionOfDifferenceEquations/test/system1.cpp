#ifndef SOLUTIONOFDIFFERENTIALEQUATIONS_SYSTEM1_CPP
#define SOLUTIONOFDIFFERENTIALEQUATIONS_SYSTEM1_CPP

#include "system1.h"
#include <cmath>

double func1 (double x,double y) {
    return 3 - y - x;
}

double sol1 (double x) {
    return 4 - x - 4 * exp(-x);
}

double func2_1(double x, double u, double v) {
    return sin(2 * u * u) + x + v;
}

double func2_2(double x, double u, double v) {
    x + u - 2 * v * v + 1;
}

double p(long double x) {
    return -0.5;
}

double q(long double x) {
    return 1;
}

double f(long double x) {
    return 2;
}

#endif
