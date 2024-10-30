#ifndef SYSTEMSOFLINEAREQUATIONS_GAUSSMETHOD_CPP
#define SYSTEMSOFLINEAREQUATIONS_GAUSSMETHOD_CPP


#include "GaussMethod.h"
#include "limits"

enum
{
    MainElement = 1
};

template<typename T>
void sub_line(Matrix<T> *reduce, unsigned int reduce_row, Matrix<T> *subtrahend, unsigned int subtrahend_row) {
    unsigned cols = reduce->GetCols();
    for (unsigned i = 0; i < cols; i++)
        (*reduce)(reduce_row, i) -= (*subtrahend)(subtrahend_row, i);
}

template<typename T>
int to_upper(Matrix<T> *matrix) {
    unsigned rows = matrix->GetRows();
    unsigned cols = matrix->GetCols();
    int swap = 0;
    for (int i = 0; i < rows; i++) {
        unsigned non_zero = i;
        for (; non_zero < rows; non_zero++) {
            if ((*matrix)(non_zero, i) != 0) {
                break;
            }
        }
        if (non_zero == rows || (*matrix)(non_zero, i) == 0)
            continue;
        if (non_zero != i) {
            matrix->SwapRows(non_zero, i);\
            swap ^= 1;
        }
        for (int j = i + 1; j < rows; j++) {
            if ((*matrix)(j, i) != 0) {
                Matrix<T> line = matrix->GetLine(i);
                line.DivRow(0, (*matrix)(i, i));
                line.MulRow(0, (*matrix)(j, i));
                sub_line(matrix, j, &line, 0);
            }
        }
    }
    return swap;
}

template<typename T>
int to_upper_with_main_element(Matrix<T> *matrix) {
    unsigned rows = matrix->GetRows();
    unsigned cols = matrix->GetCols();
    int swap = 0;
    for (int i = 0; i < rows; i++) {
        unsigned main_element = i;
        for (unsigned j = i + 1; j < rows; j++) {
            if (abs((*matrix)(j, i)) > abs((*matrix)(main_element, i))) {
                main_element = j;
            }
        }
        if ((*matrix)(main_element, i) == 0)
            continue;
        if (main_element != i) {
            matrix->SwapRows(main_element, i);
            swap ^= 1;
        }
        for (int j = i + 1; j < rows; j++) {
            if ((*matrix)(j, i) != 0) {
                Matrix<T> line = matrix->GetLine(i);
                line.DivRow(0, (*matrix)(i, i));
                line.MulRow(0, (*matrix)(j, i));
                sub_line(matrix, j, &line, 0);
            }
        }
    }
    return swap;
}

template<typename T>
T determinant(Matrix<T> *matrix, mode_t upper_flag) {
    Matrix<T> tmp_matrix(matrix);
    int swap = 0;
    if (upper_flag & MainElement) {
        swap = to_upper_with_main_element(&tmp_matrix);
    } else {
        swap = to_upper(&tmp_matrix);
    }
    size_t rows = tmp_matrix.GetRows();
    T result = swap ? -1 : 1;
    for (size_t i = 0; i < rows; i++) {
        if (abs(tmp_matrix(i, i)) < std::numeric_limits<T>::epsilon()) {
            return 0;
        }
        result *= tmp_matrix(i, i);
    }
    return result;
}

template<typename T>
T to_identity(Matrix<T> *matrix) {
    unsigned rows = matrix->GetRows();
    unsigned cols = matrix->GetCols();
    for (int i = rows - 1; i >= 0; i--) {
        if ((*matrix)(i, i) == 0)
            continue;
        matrix->DivRow(i, (*matrix)(i, i));
        for (int j = i - 1; j >= 0; j--) {
            if ((*matrix)(j, i) != 0) {
                Matrix<T> line = matrix->GetLine(i);
                line.MulRow(0, (*matrix)(j, i));
                sub_line(matrix, j, &line, 0);
            }
        }
    }
}

template<typename T>
Matrix<T> solution_sys_lin_equ(Matrix<T> &matrix, mode_t upper_flag) {
    Matrix<T> tmp_matrix(matrix);
    if (upper_flag & MainElement) {
        to_upper_with_main_element(&tmp_matrix);
    } else {
        to_upper(&tmp_matrix);
    }
    to_identity(&tmp_matrix);
    size_t rows = tmp_matrix.GetRows();
    size_t cols = tmp_matrix.GetCols();
    Matrix<T> result(1, rows, tmp_matrix(0, 0));
    for (size_t i = 0; i < rows; i++) {
        result(0, i) = tmp_matrix(i, cols - 1);
    }
    return result;
}

template<typename T>
Matrix<T> inverse_matrix(Matrix<T> &matrix, mode_t upper_flag) {
    size_t rows = matrix.GetRows();
    Matrix<T> tmp_matrix(rows, rows * 2, 0);
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < rows; j++) {
            tmp_matrix(i, j) = matrix(i, j);
        }
    }
    for (size_t i = 0; i < rows; i++) {
        tmp_matrix(i, i + rows) = 1;
    }
    if (upper_flag & MainElement) {
        to_upper_with_main_element(&tmp_matrix);
    } else {
        to_upper(&tmp_matrix);
    }
    to_identity(&tmp_matrix);
    Matrix<T> result(rows, rows, 0);
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < rows; j++) {
            result(i, j) = tmp_matrix(i, j + rows);
        }
    }
    return result;
}

template<typename T>
T conditional_number(Matrix<T> &matrix, mode_t norm_flag, mode_t upper_flag) {
    Matrix<T> inv_matrix = inverse_matrix(matrix, upper_flag);
    return matrix.MatrixNorm(norm_flag) * inv_matrix.MatrixNorm(norm_flag);
}
#endif