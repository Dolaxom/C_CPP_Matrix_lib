#pragma once

#include <cassert>
#include <cmath>
#include <iostream>

enum Error { kSuccess = true, kAllocationError = false, kMatrixError = false };

class S21Matrix {
 public:
  S21Matrix();
  S21Matrix(int rows_, int columns_);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other) noexcept;
  ~S21Matrix();

  int S21GetRows() const noexcept { return rows_; }
  int S21GetCols() const noexcept { return cols_; }
  double** S21GetMatrix() const { return matrix_; }
  void S21SetRows(int new_size);
  void S21SetCols(int new_size);

  double& operator()(int i, int j);
  const double& operator()(int i, int j) const;
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator=(S21Matrix&& other) noexcept;
  bool operator==(const S21Matrix& other) const noexcept;
  S21Matrix operator+(const S21Matrix& other) const;
  S21Matrix operator-(const S21Matrix& other) const;
  S21Matrix operator*(const double other) const;
  S21Matrix operator*(const S21Matrix& other) const;
  S21Matrix operator+=(const S21Matrix& other);
  S21Matrix operator-=(const S21Matrix& other);
  S21Matrix operator*=(double other);
  S21Matrix operator*=(const S21Matrix& other);

  S21Matrix S21Transpose();
  S21Matrix S21CalcComplements();
  double S21Determinant();
  S21Matrix S21InverseMatrix();
  void S21OutputMatrix() const;

 protected:
  bool S21EqMatrix(const S21Matrix& other) const noexcept;
  void S21SumMatrix(const S21Matrix& other);
  void S21SubMatrix(const S21Matrix& other);
  void S21MulNumber(double other);
  S21Matrix S21MulMatrix(const S21Matrix& other);

 private:
  int rows_;
  int cols_;
  double** matrix_;
  double EPS = 1e-7;

  bool S21MemoryAllocation();
  void S21MemoryDeallocation();
  void S21CopyMatrix(const S21Matrix& other);  // Copy in new memory area!
  S21Matrix S21MinorElement(int row, int column);
  S21Matrix S21MinorMatrix();
  S21Matrix S21ChessSignMatrix() noexcept;
  double S21DeterminantSimple2X2();
};

S21Matrix operator*(const double number, const S21Matrix& other);
