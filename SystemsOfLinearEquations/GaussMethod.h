#ifndef SYSTEMSOFLINEAREQUATIONS_GAUSSMETHOD_H
#define SYSTEMSOFLINEAREQUATIONS_GAUSSMETHOD_H

#include "Matrix.h"

template<typename T>
int to_upper(Matrix<T> *mat);

template<typename T>
int to_upper_with_main_element(Matrix<T> *mat);

template<typename T>
void sub_line(Matrix<T> *reduce, unsigned reduce_row, Matrix<T> *subtrahend, unsigned subtrahend_row);

template<typename T>
T determinant(Matrix<T> *matrix, mode_t upper_flag);

template<typename T>
T to_identity(Matrix<T> *matrix);

template<typename T>
Matrix<T> solution_sys_lin_equ(Matrix<T> &matrix, mode_t upper_flag);

template<typename T>
Matrix<T> inverse_matrix(Matrix<T> &matrix, mode_t upper_flag);

template<typename T>
T conditional_number(Matrix<T> &matrix, mode_t norm_flag, mode_t upper_flag);

#include "GaussMethod.cpp"

#endif