#ifndef SYSTEMSOFLINEAREQUATIONS_MATRIX_H
#define SYSTEMSOFLINEAREQUATIONS_MATRIX_H

#include "vector"
#include "iostream"

using namespace std;

enum
{
    Infinity = UINT32_MAX
};

template <typename  T> class Matrix {
private:
    vector<vector<T>> Mat;
    unsigned Rows{};
    unsigned Cols{};
public:
    Matrix(unsigned rows, unsigned cols, T initial);
    explicit Matrix(const Matrix<T> *matrix);
    T& operator()(const unsigned& row, const unsigned& col);
    const T& operator()(const unsigned& row, const unsigned& col) const;
    [[nodiscard]] unsigned GetRows() const;
    [[nodiscard]] unsigned GetCols() const;
    vector<vector<T>> GetMat() const;
    void SwapRows(unsigned first_row, unsigned second_row);
    void MulRow(unsigned row, T scalar);
    void DivRow(unsigned row, T scalar);
    void SubRows(unsigned reduce_row, unsigned sub_row);
    void Print();
    Matrix<T> GetLine(unsigned row);
    T InfinityNorm();
    T MatrixNorm(mode_t norm_flag);

};

#include "Matrix.cpp"

#endif