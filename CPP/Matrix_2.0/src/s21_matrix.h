#ifndef MATRIX_2_0_S21_MATRIX_H
#define MATRIX_2_0_S21_MATRIX_H

#include <math.h>

#include <cassert>
#include <iostream>

#define EPS 1e-7

class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(int rows, int columns);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

  int S21GetRows() const { return _rows; }
  int S21GetColumns() const { return _columns; }
  void S21SetRows(double new_value);
  void S21SetColumns(double new_value);
  double** S21GetMatrix() const { return _matrix; }

  void S21OutputMatrix() const;

  double& operator()(int i, int j);
  S21Matrix operator=(const S21Matrix& other);
  bool operator==(const S21Matrix& other);
  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(double other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator+=(const S21Matrix& other);
  S21Matrix operator-=(const S21Matrix& other);
  S21Matrix operator*=(double other);
  S21Matrix operator*=(const S21Matrix& other);

  S21Matrix S21Transpose();
  S21Matrix S21CalcComplements();
  double S21Determinant();
  S21Matrix S21InverseMatrix();

 protected:
  bool S21EqMatrix(const S21Matrix& other) const;
  void S21SumMatrix(const S21Matrix& other);
  void S21SubMatrix(const S21Matrix& other);
  void S21MulNumber(double other);
  S21Matrix S21MulMatrix(const S21Matrix& other);

  /*
   * HELPERS
   */
  bool S21MemoryAllocation();
  void S21CopyMatrix(const S21Matrix& other);

 private:
  int _rows = 0;
  int _columns = 0;
  double** _matrix;

  void S21FreeMatrix();
  void S21ZeroedMatrix();

  S21Matrix S21MinorElement(int row, int column);
  S21Matrix S21MinorMatrix();
  S21Matrix S21ChessSignMatrix();
  double S21DeterminantSimple2X2();
};

#endif  // MATRIX_2_0_S21_MATRIX_H
