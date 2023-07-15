#ifndef AUXILIARY_MODULES_H
#define AUXILIARY_MODULES_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define POLYGON_SIZE 3
typedef struct vertex {
  double x;
  double y;
  double z; // координаты вершины
  int vertex_number;
} s21_vertex;

typedef struct polygon {
  struct vertex *vertices;
} s21_polygon;

typedef struct object {
  struct polygon *polygons;
  int num_of_polygons;
} s21_object;

void object_parser(FILE*, s21_object *, s21_vertex*, int);
int start_parsing();
int parser_counter(FILE*, s21_object*);
//int sum();

#endif // AUXILIARY_MODULES_H
