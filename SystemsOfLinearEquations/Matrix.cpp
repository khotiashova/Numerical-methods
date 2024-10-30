#ifndef SYSTEMSOFLINEAREQUATIONS_MATRIX_CPP
#define SYSTEMSOFLINEAREQUATIONS_MATRIX_CPP

#include "Matrix.h"

template<typename T>
Matrix<T>::Matrix(unsigned _rows, unsigned _cols, T _initial)
{
    Mat.resize(_rows);
    for (unsigned i = 0; i < Mat.size(); i++) {
        Mat[i].resize(_cols, _initial);
    }
    Rows = _rows;
    Cols = _cols;
}

template<typename T>
Matrix<T>::Matrix(const Matrix<T> *matrix) {
    Mat = matrix->GetMat();
    Rows = matrix->GetRows();
    Cols = matrix->GetCols();
}

// Access the individual elements
template<typename T>
T& Matrix<T>::operator()(const unsigned& row, const unsigned& col) {
    return this->Mat[row][col];
}

// Access the individual elements (const)
template<typename T>
const T& Matrix<T>::operator()(const unsigned& row, const unsigned& col) const {
    return this->Mat[row][col];
}

// Get the number of rows of the matrix
template<typename T>
unsigned Matrix<T>::GetRows() const {
    return this->Rows;
}

// Get the number of columns of the matrix
template<typename T>
unsigned Matrix<T>::GetCols() const {
    return this->Cols;
}

template<typename T>
vector<vector<T>> Matrix<T>::GetMat() const {
    return this->Mat;
}

template<typename T>
void Matrix<T>::SwapRows(unsigned int first_row, unsigned int second_row) {
    for (unsigned i = 0; i < this->Cols; i++) {
        T tmp;
        tmp = this->Mat[first_row][i];
        this->Mat[first_row][i] = this->Mat[second_row][i];
        this->Mat[second_row][i] = tmp;
    }
}

template<typename T>
void Matrix<T>::MulRow(unsigned int row, T scalar) {
    for (unsigned i = 0; i < this->Cols; i++)
        this->Mat[row][i] *= scalar;
}

template<typename T>
void Matrix<T>::DivRow(unsigned int row, T scalar) {
    for (unsigned i = 0; i < this->Cols; i++)
        this->Mat[row][i] /= scalar;
}

template<typename T>
void Matrix<T>::SubRows(unsigned int reduce_row, unsigned int sub_row) {
    for (unsigned i = 0; i < this->Cols; i++)
        this->Mat[reduce_row][i] -= this->Mat[sub_row][i];
}

template<typename T>
void Matrix<T>::Print() {
    for (unsigned i = 0; i < this->Rows; i++) {
        for (unsigned j = 0; j < this->Cols; j++)
            cout << Mat[i][j] << ' ';
        cout << endl;
    }
}

template<typename T>
Matrix<T> Matrix<T>::GetLine(unsigned int row) {
    Matrix<T> line(1, this->Cols, 0);
    for (unsigned i = 0; i < this->Cols; i++)
        line.Mat[0][i] = Mat[row][i];
    return line;
}

template<typename T>
T Matrix<T>::InfinityNorm() {
    T max_row_sum = 0;
    for (size_t i = 0; i < this->Rows; i++) {
        T row_sum = 0;
        for (size_t j = 0; j < this->Cols; j++) {
            row_sum += abs(this->Mat[i][j]);
        }
        if (row_sum > max_row_sum) {
            max_row_sum = row_sum;
        }
    }
    return max_row_sum;
}

template<typename T>
T Matrix<T>::MatrixNorm(mode_t norm_flag) {
    if (norm_flag == Infinity) {
        return InfinityNorm();
    }
    return 0;
}
#endif