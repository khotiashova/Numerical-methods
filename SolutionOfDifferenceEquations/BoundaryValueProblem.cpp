#ifndef SOLUTIONOFDIFFERENTIALEQUATIONS_BOUNDARYVALUEPROBLEM_CPP
#define SOLUTIONOFDIFFERENTIALEQUATIONS_BOUNDARYVALUEPROBLEM_CPP


#include "BoundaryValueProblem.h"
#include "cstdlib"

using namespace std;

long double abs_d (long double x) {
    if (x < 0) return -x;
    return x;
}

matrix *new_matrix (unsigned m, unsigned n) { //создание матрицы
    matrix *res = (matrix *)malloc(sizeof(matrix));
    if (res == NULL) return res;
    res->m = m;
    res->n = n;
    long double **elem = (long double **)malloc(sizeof(long double *) * n);
    for (unsigned i = 0; i < n; ++i) {
        elem[i] = (long double *)calloc(m, sizeof(long double)); // память по столбцам для удобного выбора ведущего элемента
    }
    res->elem = elem;
    return res;
}

matrix *copy_matrix (matrix *matr) {
    unsigned m = matr->m;
    unsigned n = matr->n;
    matrix *new_m = new_matrix(matr->m, matr->n);
    for (unsigned i = 0; i < n; ++i) {
        for (unsigned j = 0; j < m; ++j) {
            (new_m->elem)[i][j] = (matr->elem)[i][j];
        }
    }
    return new_m;
}

void delete_matrix (matrix *matr) { //удаление матрицы
    unsigned n = matr->n;
    for (unsigned i = 0; i < n; ++i) {
        free((matr->elem)[i]);
    }
    free(matr->elem);
    free(matr);
}

void print_matrix (matrix *matr) { //вывод матрицы
    unsigned m = matr->m;
    unsigned n = matr->n;
    for (unsigned i = 0; i < m; ++i) {
        for (unsigned j = 0; j < n; ++j) {
            printf("%Lf\t", (matr->elem)[j][i]);
        }
        printf("\n");
    }
    printf("\n");
}

void print_matrix_ext (matrix *A, matrix *f) { //вывод матрицы
    unsigned m = A->m;
    unsigned n = A->n;
    for (unsigned i = 0; i < m; ++i) {
        for (unsigned j = 0; j < n; ++j) {
            printf("%Lf\t", (A->elem)[j][i]);
        }
        printf("%Lf\n", (f->elem)[0][i]);
    }
    printf("\n");
}

void read_matrix (FILE *input, matrix *matr) { //чтение матрицы из файла
    unsigned m = matr->m;
    unsigned n = matr->n;
    for (unsigned i = 0; i < m; ++i) {
        for (unsigned j = 0; j < n; ++j) {
            fscanf(input, "%Lf", &((matr->elem)[j][i]));
        }
    }
}

long double *thomas_algo (matrix *A, matrix *f) {
    // метод прогонки
    int n = A->n;
    long double *alpha = (long double *) calloc(sizeof(*alpha), n - 1);
    long double *beta = (long double *) calloc(sizeof(*beta), n - 1);
    // прямой ход
    alpha[0] = -(A->elem)[1][0] / (A->elem)[0][0];
    beta[0] = (f->elem)[0][0] / (A->elem)[0][0];
    for (int i = 1; i < n - 1; ++i) {
        long double y = alpha[i - 1] * (A->elem)[i - 1][i] + (A->elem)[i][i];
        alpha[i] = - (A->elem)[i + 1][i] / y;
        beta[i] = ((f->elem)[0][i] - beta[i - 1] * (A->elem)[i - 1][i]) / y;
    }
    // обратный ход
    long double *ans = (long double *) calloc(sizeof(*ans), n);
    ans[n - 1] = ((f->elem)[0][n - 1] - (A->elem)[n - 2][n - 1] * beta[n - 2]) /
                 ((A->elem)[n - 2][n - 1] * alpha[n - 2] + (A->elem)[n - 1][n - 1]);
    for (int i = n - 2; i >= 0; --i) {
        ans[i] = alpha[i] * ans[i + 1] + beta[i];
    }
    free(alpha);
    free(beta);
    return ans;
}

#endif
