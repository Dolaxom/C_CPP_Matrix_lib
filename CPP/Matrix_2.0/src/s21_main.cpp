#include "s21_matrix.h"

int main() {
    S21Matrix matrix_a(3, 3);
//    S21Matrix matrix_b(2, 2);
    matrix_a(0, 0) = 1;
    matrix_a(0, 1) = 2;
    matrix_a(0, 2) = 3;
    matrix_a(1, 0) = 0;
    matrix_a(1, 1) = 4;
    matrix_a(1, 2) = 2;
    matrix_a(2, 0) = 5;
    matrix_a(2, 1) = 2;
    matrix_a(2, 2) = 1;

//    matrix_b(0, 0) = 1;
//    matrix_b(0, 1) = 4;
//    matrix_b(1, 0) = 5;
//    matrix_b(1, 1) = 2;

//    S21Matrix matrix_result = matrix_a * matrix_b;
//    matrix_a *= matrix_b;

    matrix_a.S21OutputMatrix();

//    double res = matrix_a.S21Determinant();
//    std::cout << res;
    S21Matrix res = matrix_a.S21CalcComplements();
    res.S21OutputMatrix();
    return 0;
}