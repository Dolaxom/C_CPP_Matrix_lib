#include "s21_matrix.h"

int main() {
    matrix_t matrix_1 = {NULL, 0, 0};
    s21_create_matrix(3, 4, &matrix_1);

    matrix_t matrix_2 = {NULL, 0, 0};
    s21_create_matrix(3, 4, &matrix_2);

    matrix_2.matrix[1][1] = 0.0;

    printf("%d", s21_eq_matrix(&matrix_1, &matrix_2));

    s21_remove_matrix(&matrix_1);
    return 0;
}
