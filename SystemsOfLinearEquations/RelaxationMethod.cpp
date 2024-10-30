#ifndef SYSTEMSOFLINEAREQUATIONS_RELAXATIONMETHOD_CPP
#define SYSTEMSOFLINEAREQUATIONS_RELAXATIONMETHOD_CPP

#include "RelaxationMethod.h"
#include "iostream"
using namespace std;

template<typename T>
void next_iteration(Matrix<T> &x_pr, Matrix<T> &x_next, Matrix<T> &matrix, T om){
    T s1,s2;
    size_t n = matrix.GetRows();
    for(size_t i = 0; i < n;i++) {
        s1=0;
        s2=0;
        for (size_t j=0; j < i; j++) {
            T c = -matrix(i,j)*om/matrix(i, i);
            s1 += c*x_next(0, j);
        }
        for (size_t j = i + 1 ; j < n; j++) {
            T c = -matrix(i, j)*om/matrix(i, i);
            s2 += c*x_pr(0, j);
        }
        T d=matrix(i, n)*om/matrix(i, i);
        x_next(0, i) = s1 + s2 + d - x_pr(0, i)*(om-1);
    }
}

template<typename T>
bool convergence(Matrix<T> x_pr, Matrix<T> x_rc, T eps) {
    size_t n = x_pr.GetCols();
    for (size_t i = 0; i < n; i++) {
        if (abs(x_pr(0, i) - x_rc(0, i)) >= eps) {
            return false;
        }
    }
    return true;
}

template<typename T>
void non_zero_diag(Matrix<T> *matrix) {
    size_t n = matrix->GetRows();
    for (int i = 0; i < n; i++) {
        if ((*matrix)(i, i) == 0) {
            for (int j = 0; j < n; j++) {
                if ((*matrix)(j, j) != 0 && (*matrix)(j, i) != 0) {
                    matrix->SwapRows(i, j);
                    break;
                }
            }
        }
    }
}

template<typename T>
Matrix<T> solution_relaxation_method(Matrix<T> matrix, T eps, T om) {
    size_t n = matrix.GetRows();
    non_zero_diag(&matrix);
    Matrix<T> x_pr(1, n, 0);
    Matrix<T> x_next(x_pr);
    unsigned max_step = 1000;
    do {
        max_step--;
        x_pr = x_next;
        next_iteration(x_pr, x_next, matrix, om);
    } while (!convergence(x_pr, x_next, eps) && max_step);
    cout << "\n step is " << 1000 - max_step << endl;
    return x_next;
}


#endif