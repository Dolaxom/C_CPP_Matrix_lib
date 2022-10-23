#include "s21_matrix.h"

S21Matrix::S21Matrix()
{
    MemoryAllocation();
}

S21Matrix::S21Matrix(int rows, int columns)
{
    this->_rows = rows;
    this->_columns = columns;

    MemoryAllocation();
}

S21Matrix::S21Matrix(const S21Matrix &other)
{

}

S21Matrix::S21Matrix(S21Matrix &&other) noexcept
{

}

S21Matrix::~S21Matrix()
{
    for (int i = 0; i < _rows; i++)
    {
        delete []_matrix[i];
    }
    delete []_matrix;

    _columns = 0;
    _rows = 0;
    _matrix = nullptr;
}

bool S21Matrix::MemoryAllocation()
{
    if (_rows < 1 || _columns < 1)
    {
        return false;
    }

    _matrix = new double *[_rows];
    for (int i = 0; i < _rows; i++)
    {
        _matrix[i] = new double[_columns];
    }

    return true;
}

bool S21Matrix::EqMatrix(const S21Matrix &other) const {
    for (int i = 0; i < _rows; i++)
    {
        for (int j = 0; j < _columns; j++)
        {
            if (fabs(_matrix[i][j] - other._matrix[i][j]) > EPS)
            {
                return false;
            }
        }
    }

    return true;
}

bool S21Matrix::operator==(const S21Matrix &other) {
    if (other._rows != _rows && other._columns != _columns)
    {
        return false;
    }

    if (this->EqMatrix(other)) return true;

    return false;
}

double S21Matrix::operator()(int i, int j) {
    assert(i <= _rows && j <= _columns);
    return _matrix[i][j];
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
    assert(other._rows != _rows && other._columns != _columns);
    
    this->sum_matrix(other);
}

void S21Matrix::sum_matrix(const S21Matrix &other) {
    for (int i = 0; i < _rows; i++)
    {
        for (int j = 0; j < _columns; j++)
        {
            _matrix[i][j] += other._matrix[i][j];
        }
    }
}


