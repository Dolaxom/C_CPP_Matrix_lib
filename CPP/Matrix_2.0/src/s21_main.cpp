#include "s21_matrix.h"

int main() {
    S21Matrix matrix_a(2, 2);
    S21Matrix matrix_b(2, 2);
    matrix_a(0, 0) = 5;
    matrix_a(0, 1) = 2;
    matrix_a(1, 0) = 4;
    matrix_a(1, 1) = 3;

    matrix_b(0, 0) = 1;
    matrix_b(0, 1) = 4;
    matrix_b(1, 0) = 5;
    matrix_b(1, 1) = 2;

//    S21Matrix matrix_result = matrix_a * matrix_b;
    matrix_a *= matrix_b;

    matrix_a.S21OutputMatrix();

    S21Matrix matrix_transpose = matrix_a.transpose();
    matrix_transpose.S21OutputMatrix();
    return 0;
}