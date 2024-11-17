#ifndef SOLUTIONOFDIFFERENTIALEQUATIONS_SYSTEMOFDIFFERENTIALEQUATIONS_CPP
#define SOLUTIONOFDIFFERENTIALEQUATIONS_SYSTEMOFDIFFERENTIALEQUATIONS_CPP

#include "SystemOfDifferentialEquations.h"
#include "cmath"
#include "iostream"

using namespace std;

vector<vector<double>> RUNGE4_1(double (*f)(double, double), double h, int n, double x_0, double y_0) {
    vector<double> mean;
    vector<double> x;
    mean.resize(n + 1);
    x.resize(n + 1);
    double x1 = x_0, y1 = y_0;
    for (int i = 0; i <= n; ++i) {
        mean[i] = y1;
        x[i] = x1;
        double k1 = f(x1, y1);
        double k2 = f(x1 + h / 2, y1 + (h * k1 / 2));
        double k3 = f(x1 + h / 2, y1 + (h * k2 / 2));
        double k4 = f(x1 + h, y1 + (h * k3));
        y1 = y1 + h * (k1 + 2 * (k2 + k3) + k4) / 6;
        x1 += h;
    }
    vector<vector<double>> result;
    result.push_back(x);
    result.push_back(mean);
    return result;
}

vector<vector<double>> RUNGE4_2(double (*function1)(double, double, double), double (*function2)(double, double, double),
                                double h, int n, double x_0, double u_0, double v_0) {
    vector<double> u;
    vector<double> v;
    vector<double> x;
    u.resize(n + 1);
    x.resize(n + 1);
    v.resize(n + 1);
    double x1 = x_0, u1 = u_0, v1 = v_0;
    for (long long i = 0; i <= n; ++i) {
        u[i] = u1;
        v[i] = v1;
        x[i] = x1;
        double k1 = function1(x1, u1, v1) * h;
        double m1 = function2(x1, u1, v1) * h;
        double k2 = function1(x1 + h / 2, u1 + k1 / 2, v1 + m1 / 2) * h;
        double m2 = function2(x1 + h / 2, u1 + k1 / 2, v1 + m1 / 2) * h;
        double k3 = function1(x1 + h / 2, u1 + k2 / 2, v1 + m2 / 2) * h;
        double m3 = function2(x1 + h / 2, u1 + k2 / 2, v1 + m2 / 2) * h;
        double k4 = function1(x1 + h, u1 + k3, v1 + m3) * h;
        double m4 = function2(x1 + h, u1 + k3, v1 + m3) * h;
        u1 = u1 + (k1 + 2 * (k2 + k3) + k4) / 6;
        v1 = v1 + (m1 + 2 * (m2 + m3) + m4) / 6;
        x1 += h;
    }
    vector<vector<double>> result;
    result.push_back(x);
    result.push_back(u);
    result.push_back(v);
    return result;
}

vector<vector<double>> RUNGE2_1(double (*function)(double, double), double h, int n, double x_0, double y_0) {
    vector<double> mean;
    vector<double> x;
    mean.resize(n + 1);
    x.resize(n + 1);
    double x1 = x_0, y1 = y_0;
    for (int i = 0; i <= n; ++i) {
        mean[i] = y1;
        x[i] = x1;
        double cur_f = function(x1, y1);
        double y_pred = y1 + cur_f * h;
        y1 = y1 + (cur_f + function(x1 + h, y_pred)) * h / 2;
        x1 += h;
    }
    vector<vector<double>> result;
    result.push_back(x);
    result.push_back(mean);
    return result;
}

double accuracy1(vector<vector<double>> res, int n, double (*function)(double)) {
    double err = 0;
    for (int i = 0; i <= n; ++i) {
        err += pow(abs(function(res[0][i]) - res[1][i]), 2);
    }
    err /= n;
    return sqrt(err);
}

#endif
