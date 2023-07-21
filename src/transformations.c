#include "auxiliary_modules.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int return_flag = CALC_ERROR;
  if (rows > 0 && columns > 0) {
    if ((result->matrix = (double **)malloc(rows * sizeof(double *)))) {
      result->rows = rows;
      result->columns = columns;
      for (int i = 0; i < rows; i++) {
        if (!(result->matrix[i] = (double *)malloc(columns * sizeof(double)))) {
          for (int k = 0; k < i; k++) free(result->matrix[k]);
          free(result->matrix);
          return_flag = MATRIX_ERROR;
        }
      }
    }
    if (return_flag == CALC_ERROR) {
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
          result->matrix[i][j] = 0;
        }
      }
      return_flag = OK;
    }
  } else {
    return_flag = MATRIX_ERROR;
  }
  return return_flag;
}

void s21_remove_matrix(matrix_t *A) {
  if (A) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->matrix = NULL;
    A->columns = 0;
    A->rows = 0;
  }
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int ret_flag = CALC_ERROR;
  int is_null = OK;
  if (A == NULL || B == NULL || A->matrix == NULL || B->matrix == NULL) {
    ret_flag = MATRIX_ERROR;
    is_null = 1;
  }
  if ((A->columns == B->rows) &&
      (s21_create_matrix(A->rows, B->columns, result) == OK) && !is_null) {
    ret_flag = OK;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        for (int k = 0; k < B->rows; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }
  return ret_flag;
}

void move(float x, float y, float z, matrix_t *cur_point, matrix_t *result) {
  matrix_t move_matrix = {0};
  s21_create_matrix(4, 4, &move_matrix);
  for (int i = 0, j = 0; i < move_matrix.rows; i++, j++) {
    move_matrix.matrix[i][j] = 1;
  }
  move_matrix.matrix[0][3] = x;
  move_matrix.matrix[1][3] = y;
  move_matrix.matrix[2][3] = z;
  s21_mult_matrix(&move_matrix, cur_point, result);
  s21_remove_matrix(&move_matrix);
}

void rotate(float x, float y, float z, matrix_t *cur_point, matrix_t *result) {
  matrix_t rotate_matrix = {0};
  s21_create_matrix(4, 4, &rotate_matrix);
  for (int i = 0, j = 0; i < rotate_matrix.rows; i++, j++) {
    rotate_matrix.matrix[i][j] = 1;
  }
  if (x != 0) {
    rotate_matrix.matrix[1][1] = cos(x);
    rotate_matrix.matrix[1][2] = -sin(x);
    rotate_matrix.matrix[2][1] = sin(x);
    rotate_matrix.matrix[2][2] = cos(x);
  } else if (y != 0) {
    rotate_matrix.matrix[0][0] = cos(y);
    rotate_matrix.matrix[0][2] = sin(y);
    rotate_matrix.matrix[2][0] = -sin(y);
    rotate_matrix.matrix[2][2] = cos(y);
  } else if (z != 0) {
    rotate_matrix.matrix[0][0] = cos(z);
    rotate_matrix.matrix[0][1] = -sin(z);
    rotate_matrix.matrix[1][0] = sin(z);
    rotate_matrix.matrix[1][1] = cos(z);
  }
  s21_mult_matrix(&rotate_matrix, cur_point, result);
  s21_remove_matrix(&rotate_matrix);
}

void scale(float x, float y, float z, matrix_t *cur_point, matrix_t *result) {
  matrix_t scale_matrix = {0};
  s21_create_matrix(4, 4, &scale_matrix);
  scale_matrix.matrix[0][0] = x;
  scale_matrix.matrix[1][1] = y;
  scale_matrix.matrix[2][2] = z;
  scale_matrix.matrix[3][3] = 1;
  s21_mult_matrix(&scale_matrix, cur_point, result);
  s21_remove_matrix(&scale_matrix);
}
