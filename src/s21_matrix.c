#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
    result->rows = rows;
    result->columns = columns;

    result->matrix = (double **) malloc(rows * sizeof(double*));
    for (int i = 0; i < rows; i++) {
        result->matrix[i] = (double *) malloc(columns * sizeof(double));
    }

    s21_init_matrix(rows, columns, result);

    return 0;
}

const int s21_output_matrix(const matrix_t *result) {
    for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++)
            printf("%f ", result->matrix[i][j]);
        printf("\n");
    }

    return 0;
}

int s21_init_matrix(int rows, int columns, matrix_t *result) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            result->matrix[i][j] = 0.0;

    return 0;
}

void s21_remove_matrix(matrix_t *A) {
    for (int i = 0; i < A->rows; i++)
        free(A->matrix[i]);

    free(A->matrix);
}
