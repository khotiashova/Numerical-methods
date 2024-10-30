#ifndef SYSTEMSOFLINEAREQUATIONS_RELAXATIONMETHOD_H
#define SYSTEMSOFLINEAREQUATIONS_RELAXATIONMETHOD_H

#include "Matrix.h"

template<typename T>
void next_iteration(Matrix<T> &x_pr, Matrix<T> &x_next, Matrix<T> &matrix, T om);

template<typename T>
Matrix<T> solution_relaxation_method(Matrix<T> matrix, T eps, T om);

template<typename T>
bool convergence(Matrix<T> x_pr, Matrix<T> x_rc, T eps);

template<typename T>
void non_zero_diag(Matrix<T> *matrix);

#include "RelaxationMethod.cpp"
#endif