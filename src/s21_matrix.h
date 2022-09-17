#ifndef S21_MATRIX_S21_MATRIX_H
#define S21_MATRIX_S21_MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0
#define EPS 1e-07

enum { OK, MATRIX_ERROR, CALC_ERROR };

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// main
int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);

int s21_eq_matrix(matrix_t *A, matrix_t *B);

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_transpose(matrix_t *A, matrix_t *result);

int s21_calc_complements(matrix_t *A, matrix_t *result);

int s21_determinant(matrix_t *A, double *result);

int s21_inverse_matrix(matrix_t *A, matrix_t *result);

// helpers
int s21_init_matrix(int rows, int columns, matrix_t *result);
// void s21_output_matrix(const matrix_t result);
int s21_minor_element(matrix_t *A, matrix_t *result, int rows, int columns);
int s21_minor_matrix(matrix_t *A, matrix_t *result);
int s21_chess_sign_matrix(matrix_t A, matrix_t *result);
int s21_determinant_simple2x2(matrix_t *A, double *result);
int s21_check_matrix(matrix_t *A);

#endif  // S21_MATRIX_S21_MATRIX_H
