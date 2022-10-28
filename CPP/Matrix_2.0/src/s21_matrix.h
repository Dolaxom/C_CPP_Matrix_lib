#ifndef MATRIX_2_0_S21_MATRIX_H
#define MATRIX_2_0_S21_MATRIX_H

#include <math.h>
#include <iostream>
#include <cassert>

#define EPS 1e-7

class S21Matrix {
public:
    S21Matrix();
    S21Matrix(int rows, int columns);
    S21Matrix(const S21Matrix& other);
    S21Matrix(S21Matrix&& other) noexcept;
    ~S21Matrix();

    int S21GetRows() const { return _rows; }
    int S21GetColumns() const { return _columns;    }
    void S21SetRows(double new_value) { _rows = new_value; }
    void S21SetColumns(double new_value) { _columns = new_value; }
    double **S21GetMatrix() const { return _matrix; }

    double& operator ()(int i, int j);
    S21Matrix operator =(const S21Matrix &other);
    bool operator ==(const S21Matrix &other);
    S21Matrix operator +(const S21Matrix& other);

protected:
    bool EqMatrix(const S21Matrix& other) const;
    void sum_matrix(const S21Matrix& other);
    bool MemoryAllocation();
    void CopyMatrix(const S21Matrix &other);

private:
    int _rows = 0;
    int _columns = 0;
    double **_matrix;

    void free_matrix();
    void zeroed_matrix();
};


#endif //MATRIX_2_0_S21_MATRIX_H