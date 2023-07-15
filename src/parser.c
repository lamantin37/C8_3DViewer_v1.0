#include <stdio.h>
#include "auxiliary_modules.h"
int parser_counter(FILE *fp, s21_object *object) {
  char line[256];
  int num_of_vert = 0;
  while (fgets(line, sizeof(line), fp)) {
    if (line[0] != '\n' && line[0] != '#') {
      char token[3];
      if (sscanf(line, "%2s", token) == 1) {
        if (strcmp(token, "f") == 0) {
          object->num_of_polygons += 1;
        } else if (strcmp(token, "v") == 0) {
          num_of_vert++;
        }
      }
    }
  }
  return num_of_vert;
  // for (int i = 0; i < object->num_of_polygons; i++) {
  // //   object->polygons[i].num_of_vertices = num_of_vert;
  // }
}

void object_parser(FILE *fp, s21_object *object, s21_vertex *vertex,
                   int num_of_vert) {
  vertex = malloc(num_of_vert * sizeof(s21_vertex));
  object->polygons = malloc(object->num_of_polygons * sizeof(s21_polygon));
  for (int i = 0; i < object->num_of_polygons; i++) {
    object->polygons[i].vertices = malloc(POLYGON_SIZE * sizeof(s21_vertex));
  }
  if (object->polygons == NULL) {
    printf("Memory error\n");
  } else {
    fseek(fp, 0, SEEK_SET);
    int polygon_index = 0;
    int polygon_count = 0;
    int vertex_index = 0;
    int vertex_count = 0;
    double x, y, z;
    int v1, v2, v3;
    int ch;
    while ((ch = fgetc(fp)) != EOF) {
      if (ch == 'v') {
        if (fscanf(fp, "%lf %lf %lf", &x, &y, &z) == 3) {
          vertex[vertex_index].x = x;
          vertex[vertex_index].y = y;
          vertex[vertex_index].z = z;
          vertex[vertex_index].vertex_number = vertex_count + 1;
          // printf("%d: %lf %lf %lf\n", vertex[vertex_index].vertex_number,
          // vertex[vertex_index].x, vertex[vertex_index].y,
          // vertex[vertex_index].z);
          vertex_index++;
        }
        vertex_count++;
      } else if (ch == 'f') {
        if (fscanf(fp, "%d %d %d", &v1, &v2, &v3) == 3) {
          object->polygons[polygon_index].vertices[0] = vertex[v1 - 1];
          object->polygons[polygon_index].vertices[1] = vertex[v2 - 1];
          object->polygons[polygon_index].vertices[2] = vertex[v3 - 1];
          polygon_index++;
        }
      }
    }
  }
  fclose(fp);
}

void printPolygon(s21_object* object) {
  for (int i = 0; i < object->num_of_polygons; i++) {
    for (int j = 0; j < POLYGON_SIZE; j++) {
      printf("polygon %d, v %d: %lf %lf %lf\n", i,
             object->polygons[i].vertices[j].vertex_number,
             object->polygons[i].vertices[j].x,
             object->polygons[i].vertices[j].y,
             object->polygons[i].vertices[j].z);
    }
    printf("\n");
  }
}

int start_parsing() {
  FILE *fp;
  int num_of_vert = 0;
  if ((fp = fopen("cube.obj", "r")) == NULL) {
    printf("Error opening file\n");
  } else {
    s21_object object;
    object.polygons = NULL;
    object.num_of_polygons = 0;

    s21_vertex vertex;

    num_of_vert = parser_counter(fp, &object);
    object_parser(fp, &object, &vertex, num_of_vert);
//    printPolygon(&object);
  }
  return num_of_vert;
}
