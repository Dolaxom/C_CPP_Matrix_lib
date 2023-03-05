#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() {
  rows_ = 0;
  cols_ = 0;
  matrix_ = nullptr;
}

S21Matrix::S21Matrix(int rows, int columns) {
  assert(rows > 0 && columns > 0 && "Values must be greater than zero.");

  this->rows_ = rows;
  this->cols_ = columns;
  S21MemoryAllocation();
}

S21Matrix::S21Matrix(const S21Matrix &other) { S21CopyMatrix(other); }

S21Matrix::S21Matrix(S21Matrix &&other) noexcept {
  assert(&other != this && "You must specify two different objects");
  this->cols_ = other.cols_;
  this->rows_ = other.rows_;
  this->matrix_ = other.matrix_;
  other.cols_ = 0;
  other.rows_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() { S21MemoryDeallocation(); }

double &S21Matrix::operator()(int i, int j) {
  assert(i < this->rows_ && j < this->cols_ && i >= 0 && j >= 0 &&
         "The values of arguments must be less than the size of the matrix");

  return this->matrix_[i][j];
}

const double &S21Matrix::operator()(int i, int j) const {
  assert(i < this->rows_ && j < this->cols_ && i >= 0 && j >= 0 &&
         "The values of arguments must be less than the size of the matrix");

  return this->matrix_[i][j];
}

// Copy from other to this
void S21Matrix::S21CopyMatrix(const S21Matrix &other) {
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;

  S21MemoryAllocation();

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this->matrix_ != nullptr) {
    S21MemoryDeallocation();
  }
  S21CopyMatrix(other);

  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) noexcept {
  assert(&other != this && "You must specify two different objects");
  if (this->matrix_ != nullptr) {
    S21MemoryDeallocation();
  }
  this->cols_ = other.cols_;
  this->rows_ = other.rows_;
  this->matrix_ = other.matrix_;
  other.cols_ = 0;
  other.rows_ = 0;
  other.matrix_ = nullptr;

  return *this;
}

bool S21Matrix::S21EqMatrix(const S21Matrix &other) const noexcept {
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      if (fabs(this->matrix_[i][j] - other.matrix_[i][j]) > EPS) {
        return false;
      }
    }
  }

  return true;
}

void S21Matrix::S21SumMatrix(const S21Matrix &other) {
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::S21SubMatrix(const S21Matrix &other) {
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::S21MulNumber(double other) {
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] *= other;
    }
  }
}

S21Matrix S21Matrix::S21MulMatrix(const S21Matrix &other) {
  S21Matrix result_matrix(this->rows_, other.cols_);

  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < other.rows_; k++) {
        result_matrix.matrix_[i][j] +=
            this->matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  return result_matrix;
}

bool S21Matrix::operator==(const S21Matrix &other) const noexcept {
  if (other.rows_ == this->rows_ && other.cols_ == this->cols_) {
    if (this->S21EqMatrix(other)) return true;
  }

  return false;
}

S21Matrix S21Matrix::operator+(const S21Matrix &other) const {
  assert(other.rows_ == this->rows_ && other.cols_ == this->cols_);

  S21Matrix matrix_tmp(*this);
  matrix_tmp.S21SumMatrix(other);

  return matrix_tmp;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) const {
  assert(other.rows_ == this->rows_ && other.cols_ == this->cols_);

  S21Matrix matrix_tmp(*this);
  matrix_tmp.S21SubMatrix(other);

  return matrix_tmp;
}

S21Matrix S21Matrix::operator*(double other) const {
  S21Matrix matrix_tmp(*this);
  matrix_tmp.S21MulNumber(other);

  return matrix_tmp;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) const {
  assert(this->cols_ == other.rows_);

  S21Matrix matrix_tmp(*this);
  return matrix_tmp.S21MulMatrix(other);
}

S21Matrix S21Matrix::operator+=(const S21Matrix &other) {
  assert(other.rows_ == this->rows_ && other.cols_ == this->cols_);

  S21SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix &other) {
  assert(other.rows_ == this->rows_ && other.cols_ == this->cols_);

  S21SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(double other) {
  S21MulNumber(other);

  return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix &other) {
  assert(this->cols_ == other.rows_);
  S21Matrix matrix_tmp(*this);
  this->S21MemoryDeallocation();
  *this = matrix_tmp.S21MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::S21Transpose() {
  S21Matrix result_matrix(this->cols_, this->rows_);
  for (int i = 0; i < result_matrix.rows_; i++) {
    for (int j = 0; j < result_matrix.cols_; j++) {
      result_matrix.matrix_[i][j] = this->matrix_[j][i];
    }
  }

  return result_matrix;
}

S21Matrix S21Matrix::S21CalcComplements() {
  assert(this->cols_ >= 0 && this->rows_ >= 0);

  S21Matrix result_matrix;
  S21Matrix buffer;
  buffer = S21MinorMatrix();
  result_matrix = buffer.S21ChessSignMatrix();

  return result_matrix;
}

double S21Matrix::S21Determinant() {
  assert(rows_ == cols_);
  S21Matrix Buffer;
  double result = 0.0;

  if (rows_ == 1) {
    result = matrix_[0][0];
  } else if (rows_ == 2) {
    result = S21DeterminantSimple2X2();
  } else if (rows_ == 3) {
    Buffer = S21CalcComplements();
    for (int j = 0; j < rows_; j++) {
      result += matrix_[0][j] * Buffer.matrix_[0][j];
    }
  } else {
    double Det = 0.0f;
    for (int j = 0; j < rows_; j++) {
      Buffer = S21MinorElement(0, j);
      Det = Buffer.S21Determinant();
      Det *= matrix_[0][j];
      if (j % 2) {
        result -= Det;
      } else {
        result += Det;
      }
    }
  }

  return result;
}

S21Matrix S21Matrix::S21InverseMatrix() {
  S21Matrix result_matrix;
  double det = 0.0f;
  det = S21Determinant();
  if (det != 0.0) {
    S21Matrix buffer1;
    S21Matrix buffer2;
    buffer1 = S21CalcComplements();
    buffer2 = buffer1.S21Transpose();
    result_matrix = buffer2 * (1.0 / det);
  }

  return result_matrix;
}

void S21Matrix::S21SetRows(int new_size) {
  S21Matrix temp(*this);
  this->S21MemoryDeallocation();
  this->rows_ = new_size;
  this->cols_ = temp.cols_;
  this->S21MemoryAllocation();
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] = temp.matrix_[i][j];
    }
  }
}

void S21Matrix::S21SetCols(int new_size) {
  S21Matrix temp(*this);
  this->S21MemoryDeallocation();
  this->rows_ = temp.rows_;
  this->cols_ = new_size;
  this->S21MemoryAllocation();
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix_[i][j] = temp.matrix_[i][j];
    }
  }
}

/*
 * HELPERS
 */

bool S21Matrix::S21MemoryAllocation() {
  if (rows_ < 1 || cols_ < 1) {
    return kMatrixError;
  }

  matrix_ = new double *[rows_];
  if (matrix_ == nullptr) {
    return kAllocationError;
  }
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_];
    if (matrix_[i] == nullptr) {
      return kAllocationError;
    }
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] = 0.0;
    }
  }

  return kSuccess;
}

void S21Matrix::S21MemoryDeallocation() {
  if (this->matrix_ == nullptr) {
    return;
  }

  for (int i = 0; i < this->rows_; i++) {
    delete[] this->matrix_[i];
  }

  delete[] this->matrix_;

  this->cols_ = 0;
  this->rows_ = 0;
  this->matrix_ = nullptr;
}

S21Matrix S21Matrix::S21MinorElement(int row, int column) {
  int result_rows = this->rows_ - 1;
  int result_columns = this->cols_ - 1;
  S21Matrix result_matrix(result_rows, result_columns);
  result_rows = 0;
  result_columns = 0;

  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      if (i == row || j == column) continue;
      result_matrix.matrix_[result_rows][result_columns] = this->matrix_[i][j];
      result_columns++;
    }
    if (i != row) result_rows++;
    result_columns = 0;
  }

  return result_matrix;
}

S21Matrix S21Matrix::S21MinorMatrix() {
  S21Matrix result_matrix(this->cols_, this->cols_);
  S21Matrix buffer;
  for (int i = 0; i < this->cols_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      buffer = S21MinorElement(i, j);
      double det = buffer.S21Determinant();
      result_matrix.matrix_[i][j] = det;
    }
  }

  return result_matrix;
}

S21Matrix S21Matrix::S21ChessSignMatrix() noexcept {
  S21Matrix result_matrix(this->rows_, this->cols_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      result_matrix.matrix_[i][j] = this->matrix_[i][j] * pow(-1, (i + j));
    }
  }

  return result_matrix;
}

double S21Matrix::S21DeterminantSimple2X2() {
  return matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
}

//
void S21Matrix::S21OutputMatrix() const {
  std::cout << "Output matrix(" << rows_ << ", " << cols_ << ")\n";
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      std::cout << matrix_[i][j] << " ";
    }
    std::cout << "\n";
  }
  std::cout << "\n";
}

S21Matrix operator*(const double number, const S21Matrix &other) {
  S21Matrix result_matrix(other);
  result_matrix *= number;
  return result_matrix;
}