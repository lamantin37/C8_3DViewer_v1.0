#ifndef AUXILIARY_MODULES_H
#define AUXILIARY_MODULES_H
#include <locale.h>
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
  int num_of_vertices;
} s21_object;

#endif // AUXILIARY_MODULES_H
