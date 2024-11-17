#ifndef SOLUTIONOFDIFFERENTIALEQUATIONS_SYSTEMOFDIFFERENTIALEQUATIONS_H
#define SOLUTIONOFDIFFERENTIALEQUATIONS_SYSTEMOFDIFFERENTIALEQUATIONS_H

#include <functional>
#include "vector"

using namespace std;

vector<vector <double>> RUNGE4_1(double (*function)(double, double), double h, int n, double x_0, double y_0);

vector<vector<double>> RUNGE4_2(double (*function1)(double, double, double), double (*function2)(double, double, double),
                                double h, int n, double x_0, double u_0, double v_0);

vector<vector <double>> RUNGE2_1(double (*function)(double, double), double h, int n, double x_0, double y_0);

double accuracy1(vector<vector<double>> res, int n, double (*function)(double));

#include "SystemOfDifferentialEquations.cpp"

#endif 
