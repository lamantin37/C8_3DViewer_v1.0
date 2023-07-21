#ifndef AUXILIARY_MODULES_H
#define AUXILIARY_MODULES_H
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define POLYGON_SIZE 3
#define OK 0
#define MATRIX_ERROR 1
#define CALC_ERROR 2
typedef struct vertex {
  double x;
  double y;
  double z;  // координаты вершины
  int vertex_number;
} s21_vertex;

typedef struct polygon {
  struct vertex *vertices;
} s21_polygon;

typedef struct object {
  struct polygon *polygons;
  int num_of_polygons;
  int num_of_vertices;
} s21_object;

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int, int, matrix_t *);

void s21_remove_matrix(matrix_t *);

int s21_mult_matrix(matrix_t *, matrix_t *, matrix_t *);

void move(float, float, float, matrix_t *, matrix_t *);

void rotate(float, float, float, matrix_t *, matrix_t *);

void scale(float, float, float, matrix_t *, matrix_t *);

#endif  // AUXILIARY_MODULES_H
