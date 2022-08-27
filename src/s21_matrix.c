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

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
    if (A->rows != B->rows || A->columns != B->columns)
        return FAILURE;

    for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->columns; j++)
            if (A->matrix[i][j] != B->matrix[i][j])
                return FAILURE;


    return SUCCESS;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    if (A->rows != B->rows || A->columns != B->columns)
        return CALC_ERROR;

    s21_create_matrix(A->rows, A->columns, result);

    for (int i = 0; i < result->rows; i++)
        for (int j = 0; j < result->columns; j++)
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];

    return OK;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    if (A->rows != B->rows || A->columns != B->columns)
        return CALC_ERROR;

    s21_create_matrix(A->rows, A->columns, result);

    for (int i = 0; i < result->rows; i++)
        for (int j = 0; j < result->columns; j++)
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];

    return OK;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
    if (A->rows != result->rows || A->columns != result->columns)
        return CALC_ERROR;

    s21_create_matrix(A->rows, A->columns, result);

    for (int i = 0; i < result->rows; i++)
        for (int j = 0; j < result->columns; j++)
            result->matrix[i][j] = A->matrix[i][j] * number;

    return OK;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
    int max_row = B->rows;
    int max_col = B->columns;
    if (A->rows > B->rows)
        max_row = A->rows;
    if (A->columns > B->columns)
        max_col = A->columns;

    s21_create_matrix(max_row, max_col, result);

    for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < B->columns; j++)
            for (int k = 0; k < B->rows; k++)
                result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];

    return OK;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
    s21_create_matrix(A->columns, A->rows, result);
    
    for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->columns; j++) {
            result->matrix[i][j] = A->matrix[j][i];
        }
    }

    return OK;
}

