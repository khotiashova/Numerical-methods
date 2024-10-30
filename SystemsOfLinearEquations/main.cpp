#include "iostream"
#include "Matrix.h"
#include "GaussMethod.h"
#include <fstream>
#include <unistd.h>
#include <cstdlib>
#include "Fraction.h"
#include "RelaxationMethod.h"
#include <fcntl.h>
#include <unistd.h>

using namespace std;


void review_matrix(Matrix<double>& matrix, mode_t out_flag){
    if (out_flag)
        matrix.Print();
    double det, det_main;
    det = determinant(&matrix, 0);
    det_main = determinant(&matrix, MainElement);
    cout << "Определитель матрицы -> " << det << ", " << det_main << "(с выбором главного элемента)\n";
    if (abs(det) >= std::numeric_limits<double>::epsilon()) {
        Matrix<double> solution = solution_sys_lin_equ(matrix, 0);
        Matrix<double> solution_with_main_elem = solution_sys_lin_equ(matrix, MainElement);
        Matrix<double> solution_relaxation = solution_relaxation_method(matrix, 0.001, (double)1);
        cout << "Решение СЛАУ\n";
        solution.Print();
        cout << "Решение СЛАУ с выделением главного элемента\n";
        solution_with_main_elem.Print();
        cout << "Решение СЛАУ методом Зейделя\n";
        solution_relaxation.Print();
        Matrix<double> inv_matrix = inverse_matrix(matrix, 0);
        Matrix<double> inv_matrix_with_main = inverse_matrix(matrix, MainElement);
        if (out_flag) {
            cout << "Обратная матрица\n";
            inv_matrix.Print();
            cout << "Обратная матрица  с выбором главного элемента\n";
            inv_matrix_with_main.Print();
        }
    }
    cout << "Норма матрицы -> " << matrix.MatrixNorm(Infinity) << endl;
    cout << "Число обусловленности матрицы -> "
         << conditional_number(matrix, Infinity, 0) << endl;
    cout << "Число обусловленности матрицы c выбором главного элемента -> "
         << conditional_number(matrix, Infinity, MainElement) << endl;
    cout << "-------------------------------------------------------------" <<  endl;
}

int main(int argc, char*argv[]) {
    ifstream in_file("../test/matrix_in");
    int fd = open("out", O_RDWR | O_CREAT, 0666);
    dup2(fd, 1);
    int n_matrix;
    in_file >> n_matrix;
    for (int k = 0; k < n_matrix; k++) {
        size_t matrix_rows, matrix_cols;
        in_file >> matrix_rows >> matrix_cols;
        Matrix<double> matrix(matrix_rows, matrix_cols, 0);
        for (unsigned i = 0; i < matrix_rows; i++)
            for (unsigned j = 0; j < matrix_cols; j++) {
                in_file >> matrix(i, j);
            }
        cout << "Матрица №" << k + 1 << endl;
        review_matrix(matrix, 1);
    }
    in_file.close();
    int rows = 30, m = 20;
    Matrix<double> matrix(rows, rows + 1, 0);
    for (size_t i = 0; i < rows; i++) {
        for (size_t j = 0; j < rows; j++) {
            if (i != j) {
                matrix(i, j) = ((double)i + (double)j) / (m + rows);
            } else {
                matrix(i, j) = (double)rows + m * m + (double)j / m + (double)i / rows;
            }
        }
    }
    for (size_t i = 0; i < rows; i++) {
        matrix(i, rows) = (double)m * (double)i + rows;
    }
    cout << "Матрица №" << n_matrix + 1 << endl;
    review_matrix(matrix, 1);
    return 0;
}