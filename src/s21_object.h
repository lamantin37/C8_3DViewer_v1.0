#ifndef S21_OBJECT_H_
#define S21_OBJECT_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct vertex {
  double x;
  double y;
  double z;
} s21_vertex;

typedef struct polygon {
  struct vertex *vertices;
  int num_of_vertices;
} s21_polygon;

typedef struct object {
  struct polygon *polygons;
  int num_of_polygons;
} s21_object;

void object_parser(FILE*, s21_object *, s21_polygon*);
void polygon_parser(FILE*, s21_polygon*, int);
void parser_counter(FILE*, s21_polygon*, s21_object*);

#endif //  S21_OBJECT_H_