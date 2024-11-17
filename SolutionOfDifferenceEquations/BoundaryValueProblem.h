#ifndef SOLUTIONOFDIFFERENTIALEQUATIONS_BOUNDARYVALUEPROBLEM_H
#define SOLUTIONOFDIFFERENTIALEQUATIONS_BOUNDARYVALUEPROBLEM_H

#include "cstdio"

typedef struct Matrix {
    unsigned m, n;
    long double **elem;
} matrix;

long double abs_d (long double x);

matrix *new_matrix (unsigned m, unsigned n);
matrix *copy_matrix (matrix *matr);
void delete_matrix (matrix *matr);
void print_matrix (matrix *matr);
void print_matrix_ext (matrix *A, matrix *f);
void read_matrix (FILE *input, matrix *matr);

long double *thomas_algo (matrix *A, matrix *f);
#endif
