#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int error_id = OK;

  result->rows = rows;
  result->columns = columns;

  if (rows < 1 || columns < 1) {
    error_id = MATRIX_ERROR;
  } else {
    result->matrix = (double **)malloc(rows * sizeof(double *));
    if (result->matrix != NULL) {
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = (double *)malloc(columns * sizeof(double));
        if (!result->matrix[i]) {
          for (int j = 0; j < i; j++) free(result->matrix[j]);
          free(result->matrix);
          error_id = MATRIX_ERROR;
          break;
        }
      }

      s21_init_matrix(rows, columns, result);
    } else {
      error_id = MATRIX_ERROR;
    }
  }

  return error_id;
}

void s21_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; i++) free(A->matrix[i]);

  free(A->matrix);

  A->columns = 0;
  A->rows = 0;
  A->matrix = NULL;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int error_id = SUCCESS;
  int check_matrix_1 = s21_check_matrix(A);
  int check_matrix_2 = s21_check_matrix(B);

  if (check_matrix_1 || check_matrix_2) {
    error_id = FAILURE;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    error_id = FAILURE;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) {
          error_id = FAILURE;
          break;
        }
      }
      if (!error_id) break;
    }
  }

  return error_id;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error_id = OK;
  int check_matrix_1 = s21_check_matrix(A);
  int check_matrix_2 = s21_check_matrix(B);
  if (check_matrix_1 || check_matrix_2) {
    error_id = MATRIX_ERROR;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    error_id = CALC_ERROR;
  } else {
    s21_create_matrix(A->rows, A->columns, result);

    for (int i = 0; i < result->rows; i++)
      for (int j = 0; j < result->columns; j++)
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
  }

  return error_id;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error_id = OK;
  int check_matrix_1 = s21_check_matrix(A);
  int check_matrix_2 = s21_check_matrix(B);
  if (check_matrix_1 || check_matrix_2) {
    error_id = MATRIX_ERROR;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    error_id = CALC_ERROR;
  } else {
    s21_create_matrix(A->rows, A->columns, result);

    for (int i = 0; i < result->rows; i++)
      for (int j = 0; j < result->columns; j++)
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
  }

  return error_id;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int error_id = OK;
  int check_matrix_1 = s21_check_matrix(A);
  if (check_matrix_1) {
    error_id = MATRIX_ERROR;
  } else {
    s21_create_matrix(A->rows, A->columns, result);

    for (int i = 0; i < result->rows; i++)
      for (int j = 0; j < result->columns; j++)
        result->matrix[i][j] = A->matrix[i][j] * number;
  }

  return error_id;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int error_id = OK;
  int check_matrix_1 = s21_check_matrix(A);
  int check_matrix_2 = s21_check_matrix(B);
  if (check_matrix_1 || check_matrix_2) {
    error_id = MATRIX_ERROR;
  } else if (A->columns != B->rows) {
    error_id = CALC_ERROR;
  } else {
    s21_create_matrix(A->rows, B->columns, result);

    for (int i = 0; i < A->rows; i++)
      for (int j = 0; j < B->columns; j++)
        for (int k = 0; k < B->rows; k++)
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
  }

  return error_id;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int error_id = OK;
  int check_matrix = s21_check_matrix(A);
  if (check_matrix) {
    error_id = MATRIX_ERROR;
  } else {
    s21_create_matrix(A->columns, A->rows, result);

    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  }

  return error_id;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error_id = OK;
  int check_matrix = s21_check_matrix(A);
  if (check_matrix) {
    error_id = MATRIX_ERROR;
  } else {
    s21_create_matrix(A->rows, A->columns, result);

    matrix_t buffer = {NULL, 0, 0};
    s21_minor_matrix(A, &buffer);
    s21_chess_sign_matrix(buffer, result);

    s21_remove_matrix(&buffer);
  }

  return error_id;
}

int s21_determinant(matrix_t *A, double *result) {
  int error_id = OK;
  int check_matrix_1 = s21_check_matrix(A);
  if (check_matrix_1 || !result) {
    error_id = MATRIX_ERROR;
  } else if (A->rows != A->columns) {
    error_id = CALC_ERROR;
  } else {
    matrix_t buffer = {NULL, 0, 0};
    *result = 0.0;
    if (A->rows == 1) {
      *result = A->matrix[0][0];
    } else if (A->rows == 2) {
      s21_determinant_simple2x2(A, result);
    } else if (A->rows == 3) {
      s21_calc_complements(A, &buffer);
      for (int j = 0; j < A->rows; j++)
        *result += A->matrix[0][j] * buffer.matrix[0][j];
      s21_remove_matrix(&buffer);
    } else {
      double det = 0;
      for (int j = 0; j < A->rows; j++) {
        s21_minor_element(A, &buffer, 0, j);
        s21_determinant(&buffer, &det);
        det *= A->matrix[0][j];
        if (j % 2) {
          *result -= det;
        } else {
          *result += det;
        }
        s21_remove_matrix(&buffer);
      }
    }
  }

  return error_id;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error_id = OK;
  int check_matrix_1 = s21_check_matrix(A);
  if (check_matrix_1) {
    error_id = MATRIX_ERROR;
  } else if (A->rows != A->columns) {
    error_id = CALC_ERROR;
  } else {
    double det = 0.0;
    s21_determinant(A, &det);

    if (det != 0.0) {
      matrix_t buffer_1 = {NULL, 0, 0};
      matrix_t buffer_2 = {NULL, 0, 0};

      s21_calc_complements(A, &buffer_1);
      s21_transpose(&buffer_1, &buffer_2);
      s21_mult_number(&buffer_2, 1.0 / det, result);

      s21_remove_matrix(&buffer_1);
      s21_remove_matrix(&buffer_2);
    } else {
      error_id = CALC_ERROR;
    }
  }

  return error_id;
}

/*
 * HELPERS
 */

int s21_init_matrix(int rows, int columns, matrix_t *result) {
  for (int i = 0; i < rows; i++)
    for (int j = 0; j < columns; j++) result->matrix[i][j] = 0.0;

  return 0;
}

// void s21_output_matrix(const matrix_t result) {
//   for (int i = 0; i < result.rows; i++) {
//     for (int j = 0; j < result.columns; j++) printf("%f ",
//     result.matrix[i][j]); printf("\n");
//   }
// }

int s21_minor_element(matrix_t *A, matrix_t *result, int rows, int columns) {
  int result_rows = A->rows - 1;
  int result_columns = A->columns - 1;
  s21_create_matrix(result_rows, result_columns, result);
  result_rows = 0;
  result_columns = 0;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (i == rows || j == columns) continue;

      result->matrix[result_rows][result_columns] = A->matrix[i][j];
      result_columns++;
    }
    // Если строчка не была пустой, то мы идем на следующую
    if (i != rows) result_rows++;
    result_columns = 0;
  }

  return OK;
}

int s21_minor_matrix(matrix_t *A, matrix_t *result) {
  s21_create_matrix(A->rows, A->columns, result);
  matrix_t buffer = {NULL, 0, 0};
  double det = 0.0;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      s21_minor_element(A, &buffer, i, j);
      s21_determinant(&buffer, &det);
      result->matrix[i][j] = det;
      s21_remove_matrix(&buffer);
    }
  }

  return OK;
}

// Выставление знаков для последнего этапа s21_calc_complements
int s21_chess_sign_matrix(matrix_t A, matrix_t *result) {
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      result->matrix[i][j] = A.matrix[i][j] * pow(-1, (i + j));
    }
  }

  return OK;
}

int s21_determinant_simple2x2(matrix_t *A, double *result) {
  return *result = A->matrix[0][0] * A->matrix[1][1] -
                   A->matrix[0][1] * A->matrix[1][0];
}

int s21_check_matrix(matrix_t *A) {
  int error_id = OK;
  if (A == NULL) {
    error_id = MATRIX_ERROR;
  } else if (A->rows < 1 || A->columns < 1) {
    error_id = MATRIX_ERROR;
  } else {
    error_id = OK;
  }

  return error_id;
}
